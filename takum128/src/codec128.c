/* See LICENSE file for copyright and license details. */
#include <gmp.h>
#include <mpfr.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/*
 * The (D R2 R1 R0) -> characteristic-bias and mantissa-fragment-width
 * LUTs are width-independent: the takum format always determines the
 * regime/characteristic from the top 16 bits of the encoding, no matter
 * the total bit width. These are byte-for-byte copies of the tables in
 * ../../src/codec.c (which are file-local `static`, hence the
 * duplication rather than a shared header).
 */
static const int16_t c_bias_lut[] = {
	[0] = -255, [1] = -127, [2] = -63, [3] = -31,  [4] = -15, [5] = -7,
	[6] = -3,   [7] = -1,   [8] = 0,   [9] = 1,    [10] = 3,  [11] = 7,
	[12] = 15,  [13] = 31,  [14] = 63, [15] = 127,
};

static const uint8_t p_lut[] = {
	[0] = 4,  [1] = 5,  [2] = 6,  [3] = 7,  [4] = 8,  [5] = 9,
	[6] = 10, [7] = 11, [8] = 11, [9] = 10, [10] = 9, [11] = 8,
	[12] = 7, [13] = 6, [14] = 5, [15] = 4,
};

/* See get_c_and_return_shift in ../../src/codec.c for the full derivation. */
static uint_fast8_t
get_c_and_return_shift(uint16_t in, int_fast16_t *c)
{
	uint_fast8_t DR, p;

	DR = (in & UINT16_C(0x7800)) >> 11;
	p = p_lut[DR];
	*c = c_bias_lut[DR] + ((in & UINT16_C(0x07ff)) >> p);

	return 16 - p;
}

/* See get_DR_from_c in ../../src/codec.c. */
static uint_fast8_t
get_DR_from_c(int_fast16_t c)
{
	uint_fast8_t DR = 0;

	for (DR += (c >= 0) * 8; DR + 1 < (uint_fast8_t)LEN(c_bias_lut); DR++) {
		if (c < c_bias_lut[DR + 1]) {
			break;
		}
	}

	return DR;
}

/* Load an unsigned __int128 exactly into an mpfr_t via a GMP mpz_t bridge. */
static void
mpfr_set_uint128(mpfr_t out, unsigned __int128 v)
{
	mpz_t z;

	mpz_init(z);
	mpz_set_ui(z, (unsigned long)(v >> 64));
	mpz_mul_2exp(z, z, 64);
	mpz_add_ui(z, z, (unsigned long)v);
	mpfr_set_z(out, z, MPFR_RNDN);
	mpz_clear(z);
}

/*
 * Round m (assumed in [0,1)) to exactly num_bits fractional bits,
 * ties-to-even, and return the result as an unsigned __int128 (the
 * mpfr_t working precision guarantees num_bits <= 123 always fits).
 */
static unsigned __int128
mpfr_frac_to_rounded_uint128(mpfr_t m, uint_fast8_t num_bits)
{
	mpfr_t tmp;
	mpz_t z, rem;
	unsigned long lo, hi;
	unsigned __int128 result;

	if (num_bits == 0 || mpfr_zero_p(m)) {
		return 0;
	}

	mpfr_init2(tmp, TAKUM128_MPFR_PREC);
	mpfr_mul_2ui(tmp, m, num_bits, MPFR_RNDN);

	mpz_init(z);
	mpz_init(rem);
	mpfr_get_z(z, tmp, MPFR_RNDN); /* ties-to-even, matches MPFR_RNDN */

	mpz_tdiv_r_2exp(rem, z, 64);
	lo = mpz_get_ui(rem);
	mpz_tdiv_q_2exp(rem, z, 64);
	hi = mpz_get_ui(rem);
	result = (((unsigned __int128)hi) << 64) | lo;

	mpz_clear(rem);
	mpz_clear(z);
	mpfr_clear(tmp);

	return result;
}

void
codec128_log_to_l(mpfr_t out_l, takum_log128 t)
{
	const union util_takum128_union in = {
		.value = t,
	};
	int_fast16_t c;
	unsigned __int128 M;
	uint_fast8_t shift;

	if (t == 0) {
		mpfr_set_inf(out_l, -1);
		return;
	} else if (t == TAKUM_LOG128_NAR) {
		mpfr_set_nan(out_l);
		return;
	}

	shift = get_c_and_return_shift((uint16_t)(in.bits >> 112), &c);
	M = in.bits << shift;

	/* out_l = M / 2^128 (exact) */
	mpfr_set_uint128(out_l, M);
	mpfr_div_2ui(out_l, out_l, 128, MPFR_RNDN);

	/* out_l += c (exact, c is tiny) */
	mpfr_add_si(out_l, out_l, c, MPFR_RNDN);

	if (t < 0) {
		mpfr_neg(out_l, out_l, MPFR_RNDN);
	}
}

takum_log128
codec128_log_from_s_and_l(bool s, mpfr_t l)
{
	uint_fast8_t DR;
	uint8_t p;
	unsigned __int128 M;
	int_fast16_t c;
	mpfr_t cpm, m, bound;
	union util_takum128_union out;

	if (mpfr_nan_p(l) || (mpfr_inf_p(l) && mpfr_sgn(l) > 0)) {
		return TAKUM_LOG128_NAR;
	} else if (mpfr_inf_p(l) && mpfr_sgn(l) < 0) {
		return 0;
	}

	mpfr_inits2(TAKUM128_MPFR_PREC, cpm, m, bound, (mpfr_ptr)0);

	/*
	 * Clamp l to representable exponents. The maximum representable
	 * l is 254 + (1 - 2^-(p_lut[15]+112)) = 255 - 2^-(p_lut[15]+112),
	 * directly analogous to the bounds hardcoded per width in
	 * ../../src/codec.c (e.g. 254.9375 for 16 bits).
	 */
	mpfr_set_ui(bound, 255, MPFR_RNDN);
	mpfr_set_ui_2exp(m, 1, -(long)(p_lut[15] + TAKUM128_WIDTH_EXTRA),
	                 MPFR_RNDN);
	mpfr_sub(bound, bound, m, MPFR_RNDN);

	if (mpfr_cmp(l, bound) > 0) {
		mpfr_set(cpm, bound, MPFR_RNDN);
	} else {
		mpfr_neg(m, bound, MPFR_RNDN);
		if (mpfr_cmp(l, m) < 0) {
			mpfr_set(cpm, m, MPFR_RNDN);
		} else {
			mpfr_set(cpm, l, MPFR_RNDN);
		}
	}

	/* Apply sign to l to obtain c + m (cpm) */
	if (s) {
		mpfr_neg(cpm, cpm, MPFR_RNDN);
	}

	/* Obtain c and m from cpm */
	mpfr_floor(m, cpm);
	c = (int_fast16_t)mpfr_get_si(m, MPFR_RNDN);
	mpfr_sub(m, cpm, m, MPFR_RNDN);

	/* m could have overflowed to 1.0 */
	if (mpfr_cmp_ui(m, 1) == 0) {
		c += 1;
		mpfr_set_ui(m, 0, MPFR_RNDN);
	}

	/* Determine DR and the mantissa bit count p */
	DR = get_DR_from_c(c);
	p = p_lut[DR] + TAKUM128_WIDTH_EXTRA;

	/* Determine mantissa bits */
	M = mpfr_frac_to_rounded_uint128(m, p);

	/*
	 * Assemble, adding (not OR-ing) M so that a mantissa that rounded
	 * up to 2^p carries cleanly into the characteristic/regime field,
	 * exactly as the 16/32/64-bit encoders in ../../src/codec.c do.
	 */
	out.bits = (((unsigned __int128)s) << 127) |
	           (((unsigned __int128)DR) << 123) |
	           (((unsigned __int128)(uint32_t)(c - c_bias_lut[DR])) << p);
	out.bits += M;

	mpfr_clears(cpm, m, bound, (mpfr_ptr)0);

	return out.value;
}

void
codec128_linear_value_from_s_and_l(mpfr_t out, bool s, mpfr_t l)
{
	mpfr_t cpm, m, g;
	long c, e, h;

	if (mpfr_nan_p(l) || (mpfr_inf_p(l) && mpfr_sgn(l) > 0)) {
		mpfr_set_nan(out);
		return;
	} else if (mpfr_inf_p(l) && mpfr_sgn(l) < 0) {
		mpfr_set_zero(out, 1);
		return;
	}

	mpfr_inits2(TAKUM128_MPFR_PREC, cpm, m, g, (mpfr_ptr)0);

	/* obtain c and m from l */
	if (s) {
		mpfr_neg(cpm, l, MPFR_RNDN);
	} else {
		mpfr_set(cpm, l, MPFR_RNDN);
	}
	mpfr_floor(m, cpm);
	c = mpfr_get_si(m, MPFR_RNDN);
	mpfr_sub(m, cpm, m, MPFR_RNDN);

	/* m could have overflowed to 1.0 */
	if (mpfr_cmp_ui(m, 1) == 0) {
		c += 1;
		mpfr_set_ui(m, 0, MPFR_RNDN);
	}

	/* convert c and m to f (=m) and e */
	e = (1 - 2 * s) * (c + s);

	/* convert f and e to g and h as in Algorithm 5 */
	if (!s) {
		h = e;
		mpfr_set(g, m, MPFR_RNDN);
	} else {
		if (mpfr_zero_p(m)) {
			h = e + 1;
			mpfr_set_ui(g, 0, MPFR_RNDN);
		} else {
			h = e;
			mpfr_ui_sub(g, 1, m, MPFR_RNDN);
		}
	}

	/* (-1)^s (1 + g) 2^h is our final linear value */
	mpfr_add_ui(out, g, 1, MPFR_RNDN);
	mpfr_mul_2si(out, out, h, MPFR_RNDN);
	if (s) {
		mpfr_neg(out, out, MPFR_RNDN);
	}

	mpfr_clears(cpm, m, g, (mpfr_ptr)0);
}

void
codec128_linear_l_from_value(mpfr_t out_l, mpfr_t value)
{
	mpfr_t f, g, m;
	mpfr_exp_t h;
	long c;
	bool s;

	if (mpfr_nan_p(value) || mpfr_inf_p(value)) {
		mpfr_set_nan(out_l);
		return;
	} else if (mpfr_zero_p(value)) {
		mpfr_set_inf(out_l, -1);
		return;
	}

	mpfr_inits2(TAKUM128_MPFR_PREC, f, g, m, (mpfr_ptr)0);

	if (mpfr_sgn(value) < 0) {
		s = true;
		mpfr_neg(f, value, MPFR_RNDN);
	} else {
		s = false;
		mpfr_set(f, value, MPFR_RNDN);
	}

	/* convert f to fractional and integral components, g in [0.5,1) */
	mpfr_frexp(&h, g, f, MPFR_RNDN);

	/* g in [1,2), then subtract 1.0 to obtain g in [0,1) */
	mpfr_mul_2ui(g, g, 1, MPFR_RNDN);
	mpfr_sub_ui(g, g, 1, MPFR_RNDN);
	h--;

	/* the number has the form (-1)^s (1+g) 2^h; use Algorithm 4 */
	if (!s) {
		c = (long)h;
		mpfr_set(m, g, MPFR_RNDN);
	} else {
		if (mpfr_zero_p(g)) {
			c = -(long)h;
			mpfr_set_ui(m, 0, MPFR_RNDN);
		} else {
			c = -(long)h - 1;
			mpfr_ui_sub(m, 1, g, MPFR_RNDN);
		}
	}

	/* l is (-1)^s (c+m) */
	mpfr_add_si(out_l, m, c, MPFR_RNDN);
	if (s) {
		mpfr_neg(out_l, out_l, MPFR_RNDN);
	}

	mpfr_clears(f, g, m, (mpfr_ptr)0);
}

void
codec128_log_value_from_t(mpfr_t out, takum_log128 t)
{
	mpfr_t l;

	if (t == 0) {
		mpfr_set_zero(out, 1);
		return;
	}

	mpfr_init2(l, TAKUM128_MPFR_PREC);
	codec128_log_to_l(l, t);

	/* value = sign * exp(l/2); NaR's NaN propagates through mpfr_exp */
	mpfr_mul_2si(l, l, -1, MPFR_RNDN);
	mpfr_exp(out, l, MPFR_RNDN);
	if (t < 0) {
		mpfr_neg(out, out, MPFR_RNDN);
	}

	mpfr_clear(l);
}

takum_log128
codec128_log_from_value(mpfr_t value)
{
	mpfr_t l, absval;
	bool s;
	takum_log128 result;

	if (mpfr_zero_p(value)) {
		return 0;
	} else if (mpfr_nan_p(value) || mpfr_inf_p(value)) {
		return TAKUM_LOG128_NAR;
	}

	s = mpfr_sgn(value) < 0;

	mpfr_inits2(TAKUM128_MPFR_PREC, l, absval, (mpfr_ptr)0);
	mpfr_abs(absval, value, MPFR_RNDN);
	mpfr_log(l, absval, MPFR_RNDN);
	mpfr_mul_2si(l, l, 1, MPFR_RNDN);

	result = codec128_log_from_s_and_l(s, l);

	mpfr_clears(l, absval, (mpfr_ptr)0);

	return result;
}
