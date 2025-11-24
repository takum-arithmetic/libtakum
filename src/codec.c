/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

/*
 * This 32 byte LUT maps (D R2 R1 R0) interpreted as a 4-bit
 * unsigned integer to the characteristic bias
 */
static const int16_t c_bias_lut[] = {
	[0] = -255, /* 0 000 → D=0, r=7, -2^(r+1)+1 */
	[1] = -127, /* 0 001 → D=0, r=6, -2^(r+1)+1 */
	[2] = -63,  /* 0 010 → D=0, r=5, -2^(r+1)+1 */
	[3] = -31,  /* 0 011 → D=0, r=4, -2^(r+1)+1 */
	[4] = -15,  /* 0 100 → D=0, r=3, -2^(r+1)+1 */
	[5] = -7,   /* 0 101 → D=0, r=2, -2^(r+1)+1 */
	[6] = -3,   /* 0 110 → D=0, r=1, -2^(r+1)+1 */
	[7] = -1,   /* 0 111 → D=0, r=0, -2^(r+1)+1 */
	[8] = 0,    /* 1 000 → D=1, r=0, 2^r-1 */
	[9] = 1,    /* 1 001 → D=1, r=1, 2^r-1 */
	[10] = 3,   /* 1 010 → D=1, r=2, 2^r-1 */
	[11] = 7,   /* 1 011 → D=1, r=3, 2^r-1 */
	[12] = 15,  /* 1 100 → D=1, r=4, 2^r-1 */
	[13] = 31,  /* 1 101 → D=1, r=5, 2^r-1 */
	[14] = 63,  /* 1 110 → D=1, r=6, 2^r-1 */
	[15] = 127, /* 1 111 → D=1, r=7, 2^r-1 */
};

/*
 * This 16 byte LUT maps (D R2 R1 R0) interpreted as a 4-bit
 * unsigned integer to the mantissa bit count p = 16 - r - 5 = 11 - r
 * of the first 16 bit fragment
 */
static const uint8_t p_lut[] = {
	[0] = 4,  /* 0 000 → D=0, r=7 */
	[1] = 5,  /* 0 001 → D=0, r=6 */
	[2] = 6,  /* 0 010 → D=0, r=5 */
	[3] = 7,  /* 0 011 → D=0, r=4 */
	[4] = 8,  /* 0 100 → D=0, r=3 */
	[5] = 9,  /* 0 101 → D=0, r=2 */
	[6] = 10, /* 0 110 → D=0, r=1 */
	[7] = 11, /* 0 111 → D=0, r=0 */
	[8] = 11, /* 1 000 → D=1, r=0 */
	[9] = 10, /* 1 001 → D=1, r=1 */
	[10] = 9, /* 1 010 → D=1, r=2 */
	[11] = 8, /* 1 011 → D=1, r=3 */
	[12] = 7, /* 1 100 → D=1, r=4 */
	[13] = 6, /* 1 101 → D=1, r=5 */
	[14] = 5, /* 1 110 → D=1, r=6 */
	[15] = 4, /* 1 111 → D=1, r=7 */
};

static inline uint_fast8_t
get_c_and_return_shift(uint16_t in, int_fast16_t *c)
{
	uint_fast8_t DR, p;

	/* Extract (D R2 R1 R0) */
	DR = (in & UINT16_C(0x7800)) >> 11;
	p = p_lut[DR];

	/*
	 * Compute c by adding the bias and characteristic bits.
	 * The latter are obtained by masking out everything
	 * before the characteristic bits and shifting right
	 * by the number of mantissa bits p
	 */
	*c = c_bias_lut[DR] + ((in & UINT16_C(0x07ff)) >> p);

	/*
	 * Return 16-p, i.e. how much we have to shift left
	 * to let the bit string begin with the first mantissa bit
	 */
	return 16 - p;
}

float
codec_takum_log8_to_l(takum_log8 t)
{
	const union util_takum8_union in = {
		.value = t,
	};
	int_fast16_t c;
	uint8_t M;

	/* Catch special cases */
	if (t == 0) {
		return -INFINITY;
	} else if (t == TAKUM_LOG8_NAR) {
		return NAN;
	}

	/*
	 * Get mantissa bits by shifting so far
	 *
	 */
	M = in.bits << get_c_and_return_shift(((uint16_t)in.bits) << 8, &c);

	/*
	 * Convert c and M to floats and add them. The
	 * conversions and the addition are lossless as
	 * |c| is at most 8 bits, M is at most 3 bits,
	 * which easily fits in the 23 bits provided by
	 * float32.
	 */
	return (1 - 2 * (t < 0)) * ((float)c + ldexpf((float)M, -8));
}

float
codec_takum_log16_to_l(takum_log16 t)
{
	const union util_takum16_union in = {
		.value = t,
	};
	int_fast16_t c;
	uint16_t M;

	/* Catch special cases */
	if (t == 0) {
		return -INFINITY;
	} else if (t == TAKUM_LOG16_NAR) {
		return NAN;
	}

	/*
	 * Get mantissa bits by shifting so far
	 *
	 */
	M = in.bits << get_c_and_return_shift(in.bits, &c);

	/*
	 * Convert c and M to floats and add them. The
	 * conversions and the addition are lossless as
	 * |c| is at most 8 bits, M is at most 11 bits,
	 * which easily fits in the 23 bits provided by
	 * float32.
	 */
	return (1 - 2 * (t < 0)) * ((float)c + ldexpf((float)M, -16));
}

double
codec_takum_log32_to_l(takum_log32 t)
{
	const union util_takum32_union in = {
		.value = t,
	};
	int_fast16_t c;
	uint32_t M;

	/* Catch special cases */
	if (t == 0) {
		return -INFINITY;
	} else if (t == TAKUM_LOG32_NAR) {
		return NAN;
	}

	/*
	 * Get mantissa bits by shifting so far
	 */
	M = in.bits << get_c_and_return_shift((uint16_t)(in.bits >> 16), &c);

	/*
	 * Convert c and M to floats and add them. The
	 * conversions and the addition are lossless as
	 * |c| is at most 8 bits, M is at most 27 bits,
	 * which easily fits in the 52 bits provided by
	 * float64.
	 */
	return (1 - 2 * (t < 0)) * ((double)c + ldexp((double)M, -32));
}

long double
codec_takum_log64_to_l(takum_log64 t)
{
#if LDBL_MANT_DIG >= 64
	const union util_takum64_union in = {
		.value = t,
	};
	int_fast16_t c;
	uint64_t M;

	/* Catch special cases */
	if (t == 0) {
		return -INFINITY;
	} else if (t == TAKUM_LOG64_NAR) {
		return NAN;
	}

	/*
	 * Get mantissa bits by shifting so far
	 */
	M = in.bits << get_c_and_return_shift((uint16_t)(in.bits >> 48), &c);

	/*
	 * Convert c and M to floats and add them. The
	 * conversions and the addition are lossless as
	 * |c| is at most 8 bits, M is at most 59 bits,
	 * which easily fits in the 64 bits provided by
	 * extended float.
	 */
	return (1 - 2 * (t < 0)) *
	       ((long double)c + ldexpl((long double)M, -64));
#else
#pragma message                                                                \
	"Extended float format is too small to hold what takum_log64 offers, takum_log64 decoding is stubbed"
	(void)t;

	return NAN;
#endif
}

/*
 * For linear takums, instead of duplicating all the machinery,
 * we simply treat a linear takum as a logarithmic one: We obtain c and
 * m from the logarithmic value l and compute f and e, which are then
 * converted to g and h as in Algorithm 5 from the takum paper, yielding
 * the final floating point.
 */
double
codec_s_and_linear_l_to_float64(bool s, long double l)
{
	long double cpm, m, f, g;
	int16_t c, e, h;

	/* catch special cases */
	if (isnan(l) || (isinf(l) && l > 0.0L)) {
		return NAN;
	} else if (isinf(l) && l < 0.0L) {
		return 0.0;
	}

	/* obtain c and m from l */
	cpm = (s == 0) ? l : -l;
	c = floorl(cpm);
	m = cpm - c;

	/* m could have overflowed to 1.0 */
	if (m == 1.0L) {
		c += 1;
		m = 0.0L;
	}

	/* convert c and m to f and e */
	f = m;
	e = (1 - 2 * s) * (c + s);

	/* convert f and e to g and h as in Algorithm 5 */
	if (s == 0) {
		h = e;
		g = f;
	} else {
		if (f == 0.0) {
			h = e + 1;
			g = 0.0L;
		} else {
			h = e;
			g = 1.0L - f;
		}
	}

	/* (-1)^s (1 + g) 2^h is our final floating-point number */
	return (double)((1 - 2 * s) * ldexpl(1.0L + g, h));
}

long double
codec_s_and_linear_l_to_extended_float(bool s, long double l)
{
	long double cpm, m, f, g;
	int16_t c, e, h;

	/* catch special cases */
	if (isnan(l) || (isinf(l) && l > 0.0l)) {
		return NAN;
	} else if (isinf(l) && l < 0.0l) {
		return 0.0;
	}

	/* obtain c and m from l */
	cpm = (s == 0) ? l : -l;
	c = floorl(cpm);
	m = cpm - c;

	/* m could have overflowed to 1.0 */
	if (m == 1.0l) {
		c += 1;
		m = 0.0l;
	}

	/* convert c and m to f and e */
	f = m;
	e = (1 - 2 * s) * (c + s);

	/* convert f and e to g and h as in Algorithm 5 */
	if (s == 0) {
		h = e;
		g = f;
	} else {
		if (f == 0.0l) {
			h = e + 1;
			g = 0.0l;
		} else {
			h = e;
			g = 1.0l - f;
		}
	}

	/* (-1)^s (1 + g) 2^h is our final floating-point number */
	return (1 - 2 * s) * ldexpl(1.0l + g, h);
}

static uint_fast8_t
get_DR_from_c(int_fast16_t c)
{
	uint_fast8_t DR = 0;

	/* TODO: binary search */

	/*
	 * Determine (D R2 R1 R0) with c_bias_lut,
	 * skipping the first half when c is positive
	 */
	for (DR += (c >= 0) * 8; DR + 1 < (uint_fast8_t)LEN(c_bias_lut); DR++) {
		if (c < c_bias_lut[DR + 1]) {
			break;
		}
	}

	return DR;
}

static inline uint32_t
float32_fraction_to_rounded_bits(float f, uint_fast8_t num_bits)
{
	uint32_t F;

	/*
	 * This function converts f in [0,1) to a num_bit fixed
	 * point representation, returning the correctly rounded
	 * num_bit LSB's
	 */
	if (f == 0 || num_bits == 0) {
		F = 0;
	} else {
		union {
			float val;
			uint32_t bits;
		} fu = {
			.val = f,
		};

		int q;

		/*
		 * We know that f has the form (1+x)*2^q with q <= 0.
		 * First mask out the fraction bits and add the
		 * implicit 1 bit
		 */
		F = (fu.bits & ((UINT32_C(1) << 23) - 1)) | (UINT32_C(1) << 23);

		/* shift to the left until the 1 bit is the MSB */
		F <<= 9 - 1;

		/*
		 * If q = 0 we would be done here (because then the
		 * implicit 1 bit would be the first 'decimal' bit,
		 * which matches our normalised form). However q is
		 * generally <= 0, so we shift the bits by -q to the
		 * right which 'normalises' it, as desired.
		 */
		frexpf(f, &q);
		F = (-q < 32) ? (F >> -q) : UINT32_C(0);

		/*
		 * Round F to num_bit bits, possibly rounding up when the
		 * num_bit+1'th bit is set, but resolving a tie to even.
		 * The result will never be zero (under- or overflow) as we
		 * ensured this before with clamping
		 */
		F = util_round_uint32_to_number_of_bits(F, num_bits);
	}

	return F;
}

static inline uint64_t
float64_fraction_to_rounded_bits(double f, uint_fast8_t num_bits)
{
	uint64_t F;

	/*
	 * This function converts f in [0,1) to a num_bit fixed
	 * point representation, returning the correctly rounded
	 * num_bit LSB's
	 */
	if (f == 0 || num_bits == 0) {
		F = 0;
	} else {
		union {
			double val;
			uint64_t bits;
		} fu = {
			.val = f,
		};

		int q;

		/*
		 * We know that f has the form (1+x)*2^q with q < 0.
		 * First mask out the fraction bits and add the
		 * implicit 1 bit
		 */
		F = (fu.bits & ((UINT64_C(1) << 52) - 1)) | (UINT64_C(1) << 52);

		/* shift to the left until the 1 bit is the MSB */
		F <<= 12 - 1;

		/*
		 * If q = 0 we would be done here (because then the
		 * implicit 1 bit would be the first 'decimal' bit,
		 * which matches our normalised form). However q is
		 * generally <= 0, so we shift the bits by -q to the
		 * right which 'normalises' it, as desired.
		 */
		frexp(f, &q);
		F = (-q < 64) ? (F >> -q) : UINT64_C(0);

		/*
		 * Round F to num_bit bits, possibly rounding up when the
		 * num_bit+1'th bit is set, but resolving a tie to even.
		 * The result will never be zero (under- or overflow) as we
		 * ensured this before with clamping
		 */
		F = util_round_uint64_to_number_of_bits(F, num_bits);
	}

	return F;
}

static inline uint64_t
extended_float_fraction_to_rounded_bits(long double f, uint_fast8_t num_bits)
{
	uint64_t F;

	/*
	 * This function converts f in [0,1) to a num_bit fixed
	 * point representation, returning the correctly rounded
	 * num_bit LSB's
	 */
	if (f == 0 || num_bits == 0) {
		F = 0;
	} else {
		union {
			long double val;

			struct __attribute__((__packed__)) {
#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
				/* 64-bit long double, i.e. double is equal to
				 * long double */
				uint64_t sign_exp_fraction;
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384
/* 80-bit long double */
#if __BYTE_ORDER == __BIG_ENDIAN
				uint64_t fraction;
				uint16_t sign_exp;
#else
				uint16_t sign_exp;
				uint64_t fraction;
#endif
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384
/* 128-bit long double */
#if __BYTE_ORDER == __BIG_ENDIAN
				uint16_t fraction_reallydontcare;
				uint32_t fraction_dontcare;
				uint64_t fraction;
				uint16_t sign_exp;
#else
				uint16_t sign_exp;
				uint64_t fraction;
				uint32_t fraction_dontcare;
				uint16_t fraction_reallydontcare;
#endif
#else
				char junk;
#endif
			} bits;
		} fu = {
			.val = f,
		};

		int q;

		/*
		 * We know that f has the form (1+x)*2^q with q < 0.
		 * The fraction bits are in fu.bits.fraction.
		 */
		frexpl(f, &q);

#if LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024
		/* 64-bit double, lower 52 bits are fractions, implicit 1 */
		F = ((UINT64_C(0x000fffffffffffff) & fu.bits.sign_exp_fraction)
		     << 11) |
		    (UINT64_C(1) << 63);

		/*
		 * We correct q to reflect our shift from 1.xxx... to
		 * 0.1xxx...
		 */
		q++;
#elif LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384
		/* 80-bit long double, has explicit 1 */
		F = fu.bits.fraction;
#elif LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384
		/*
		 * 128-bit long double, has implicit 1
		 *
		 * We shift one to the right (we don't care about
		 * rounding because we don't need that kind of
		 * precision) and add the implicit 1 bit. The 1 bit
		 * is automatically the MSB.
		 */
		F = (fu.bits.fraction >> 1) | (UINT64_C(1) << 63);

		/*
		 * We correct q to reflect our shift from 1.xxx... to
		 * 0.1xxx...
		 */
		q++;
#else
		(void)fu;
		F = 0;
#endif

		/*
		 * If q = 0 we would be done here (because then the
		 * implicit 1 bit would be the first 'decimal' bit,
		 * which matches our normalised form). However q is
		 * generally <= 0, so we shift the bits by -q (given
		 * we did one right-shift earlier) to the right which
		 * 'normalises' it, as desired.
		 */
		F = (-q < 64) ? (F >> -q) : UINT64_C(0);

		/*
		 * Round F to num_bit bits, possibly rounding up when the
		 * num_bit+1'th bit is set, but resolving a tie to even.
		 * The result will never be zero (under- or overflow) as we
		 * ensured this before with clamping
		 */
		F = util_round_uint64_to_number_of_bits(F, num_bits);
	}

	return F;
}

/*
 * For the linear takums we abuse the encoder a bit by creating a
 * 'fake' linear l. In the end l is just (-1)^s (c+m), so if we just
 * get c and m from f and e, which in turn are derived from g and h
 * via Algorithm 4 in the takum paper.
 */
double
codec_linear_l_from_float32(float f)
{
	bool s;
	double g, m;
	int h;
	int16_t c;

	/* catch special cases */
	if (isnan(f) || isinf(f)) {
		return NAN;
	} else if (f == 0.0f) {
		return -INFINITY;
	}

	/* first extract sign and absolutise f */
	if (f < 0.0f) {
		s = 1;
		f = -f;
	} else {
		s = 0;
	}

	/* convert f to fractional and integral components */
	g = frexpf(f, &h);

	/*
	 * g is in range [0.5,1), so we multiply it by 2 and likewise
	 * decrement h to obtain g in the range [1,2). Then we subtract
	 * 1.0 to obtain the final g in the range [0,1)
	 */
	g = 2 * g - 1.0;
	h--;

	/*
	 * the number has the form (-1)^s (1+g) 2^h. Use Algorithm 4
	 * in the takum paper to obtain c and m (which is equal to f)
	 */
	if (s == 0) {
		c = h;
		m = g;
	} else {
		if (g == 0.0f) {
			c = -h;
			m = 0.0;
		} else {
			c = -h - 1;
			m = 1.0 - g;
		}
	}

	/* l is (-1)^s (c+m) */
	return (1 - 2 * s) * (c + m);
}

long double
codec_linear_l_from_float64(double f)
{
	bool s;
	long double g, m;
	int h;
	int16_t c;

	/* catch special cases */
	if (isnan(f) || isinf(f)) {
		return NAN;
	} else if (f == 0.0) {
		return -INFINITY;
	}

	/* first extract sign and absolutise f */
	if (f < 0.0) {
		s = 1;
		f = -f;
	} else {
		s = 0;
	}

	/* convert f to fractional and integral components */
	g = frexp(f, &h);

	/*
	 * g is in range [0.5,1), so we multiply it by 2 and likewise
	 * decrement h to obtain g in the range [1,2). Then we subtract
	 * 1.0 to obtain the final g in the range [0,1)
	 */
	g = 2 * g - 1.0;
	h--;

	/*
	 * the number has the form (-1)^s (1+g) 2^h. Use Algorithm 4
	 * in the takum paper to obtain c and m (which is equal to f)
	 */
	if (s == 0) {
		c = h;
		m = g;
	} else {
		if (g == 0.0) {
			c = -h;
			m = 0.0;
		} else {
			c = -h - 1;
			m = 1.0 - g;
		}
	}

	/* l is (-1)^s (c+m) */
	return (1 - 2 * s) * (c + m);
}

long double
codec_linear_l_from_extended_float(long double f)
{
	bool s;
	long double g, m;
	int h;
	int16_t c;

	/* catch special cases */
	if (isnan(f) || isinf(f)) {
		return NAN;
	} else if (f == 0.0l) {
		return -INFINITY;
	}

	/* first extract sign and absolutise f */
	if (f < 0.0l) {
		s = 1;
		f = -f;
	} else {
		s = 0;
	}

	/* convert f to fractional and integral components */
	g = frexpl(f, &h);

	/*
	 * g is in range [0.5,1), so we multiply it by 2 and likewise
	 * decrement h to obtain g in the range [1,2). Then we subtract
	 * 1.0 to obtain the final g in the range [0,1)
	 */
	g = 2 * g - 1.0l;
	h--;

	/*
	 * the number has the form (-1)^s (1+g) 2^h. Use Algorithm 4
	 * in the takum paper to obtain c and m (which is equal to f)
	 */
	if (s == 0) {
		c = h;
		m = g;
	} else {
		if (g == 0.0l) {
			c = -h;
			m = 0.0l;
		} else {
			c = -h - 1;
			m = 1.0l - g;
		}
	}

	/* l is (-1)^s (c+m) */
	return (1 - 2 * s) * (c + m);
}

takum_log8
codec_takum_log8_from_s_and_l(bool s, float l)
{
	return takum_log8_from_takum_log32(
		codec_takum_log32_from_s_and_l(s, l));
}

takum_log16
codec_takum_log16_from_s_and_l(bool s, double l)
{
	uint_fast8_t DR;
	uint8_t p;
	uint64_t M;
	int_fast16_t c;
	double cpm, m;
	const double bound = 254.9375;

	if (isnan(l) || (isinf(l) && l > 0)) {
		return TAKUM_LOG16_NAR;
	} else if (isinf(l) && l < 0) {
		return 0;
	}

	/*
	 * Clamp l to representable exponents,
	 * the maximum 0111111111111111 has l=254.9375
	 */
	l = (l < -bound) ? -bound : (l > bound) ? bound : l;

	/* Apply sign to l to obtain c + m (cpm) */
	cpm = (1 - 2 * s) * l;

	/* Obtain c and m from cpm */
	c = floor(cpm);
	m = cpm - c;

	/* m could have overflowed to 1.0 */
	if (m == 1.0) {
		c += 1;
		m = 0.0;
	}

	/* Determine DR */
	DR = get_DR_from_c(c);

	/*
	 * Determine p, which is simple as p_lut is for a 16-bit
	 * takum.
	 */
	p = p_lut[DR];

	/* Determine mantissa bits */
	M = float64_fraction_to_rounded_bits(m, p);

	/*
	 * Assemble, optionally apply the carry to SDR which is guaranteed
	 * not to yield NaR as we bounded l earlier and return
	 */
	return ((((uint16_t)s) << (16 - 1)) | (((uint16_t)DR) << (16 - 5)) |
	        (((uint16_t)(c - c_bias_lut[DR])) << p)) +
	       (uint16_t)M;
}

takum_log32
codec_takum_log32_from_s_and_l(bool s, long double l)
{
	uint_fast8_t DR;
	uint8_t p;
	uint64_t M;
	int_fast16_t c;
	long double cpm, m;
	const long double bound = 254.99999904632568359375L;

	if (isnan(l) || (isinf(l) && l > 0)) {
		return TAKUM_LOG32_NAR;
	} else if (isinf(l) && l < 0) {
		return 0;
	}

	/*
	 * Clamp l to representable exponents,
	 * the maximum 0111111111111111... has l=254.99999904632568359375
	 */
	l = (l < -bound) ? -bound : (l > bound) ? bound : l;

	/* Apply sign to l to obtain c + m (cpm) */
	cpm = (1 - 2 * s) * l;

	/* Obtain c and m from cpm */
	c = floorl(cpm);
	m = cpm - c;

	/* m could have overflowed to 1.0 */
	if (m == 1.0L) {
		c += 1;
		m = 0.0L;
	}

	/* Determine DR */
	DR = get_DR_from_c(c);

	/*
	 * Determine p, which is simple as p_lut is for a 16-bit
	 * takum, so we just add 16 to that.
	 */
	p = p_lut[DR] + 16;

	/* Determine mantissa bits */
	M = extended_float_fraction_to_rounded_bits(m, p);

	/* Assemble and return */
	return ((((uint32_t)s) << (32 - 1)) | (((uint32_t)DR) << (32 - 5)) |
	        (((uint32_t)(c - c_bias_lut[DR])) << p)) +
	       (uint32_t)M;
}

takum_log64
codec_takum_log64_from_s_and_l(bool s, long double l)
{
#if (LDBL_MANT_DIG == 53 && LDBL_MAX_EXP == 1024) ||                           \
	(LDBL_MANT_DIG == 64 && LDBL_MAX_EXP == 16384) ||                      \
	(LDBL_MANT_DIG == 113 && LDBL_MAX_EXP == 16384)
	uint_fast8_t DR;
	uint8_t p;
	uint64_t M;
	int_fast16_t c;
	long double cpm, m;
	const long double bound =
		254.999999999999999777955395074968691915273666381835938L;

	if (isnan(l) || (isinf(l) && l > 0)) {
		return TAKUM_LOG64_NAR;
	} else if (isinf(l) && l < 0) {
		return 0;
	}

	/*
	 * Clamp l to representable exponents,
	 * the maximum 0111111111111111... has l=254.999999... as above
	 */
	l = (l < -bound) ? -bound : (l > bound) ? bound : l;

	/* Apply sign to l to obtain c + m (cpm) */
	cpm = (1 - 2 * s) * l;

	/* Obtain c and m from cpm */
	c = floorl(cpm);
	m = cpm - c;

	/* m could have overflowed to 1.0 */
	if (m == 1.0) {
		c += 1;
		m = 0.0;
	}

	/* Determine DR */
	DR = get_DR_from_c(c);

	/*
	 * Determine p, which is simple as p_lut is for a 16-bit
	 * takum, so we just add 48 to that.
	 */
	p = p_lut[DR] + 48;

	/* Determine mantissa bits */
	M = extended_float_fraction_to_rounded_bits(m, p);

	/* Assemble and return */
	return ((((uint64_t)s) << (64 - 1)) | (((uint64_t)DR) << (64 - 5)) |
	        (((uint64_t)(c - c_bias_lut[DR])) << p)) +
	       (uint64_t)M;
#else
#pragma message                                                                \
	"Unimplemented extended float format, takum_log64 encoding is stubbed"
	(void)s;
	(void)l;

	return TAKUM_LOG64_NAR;
#endif
}
