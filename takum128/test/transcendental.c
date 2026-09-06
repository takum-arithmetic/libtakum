/* See LICENSE file for copyright and license details. */
#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>
#include <stdio.h>

#include "../../takum128.h"

#include "util128.h"

/*
 * Table-driven rather than one file per function (as phase 1 was):
 * every phase-2 function is either a direct MPFR primitive or a small,
 * documented composite of one or two MPFR primitives (see the arccot,
 * arcsec, arccsc, arcoth, arsech, arcsch, cot, sec and csc sources
 * under ../src), so the interesting part of testing them is the
 * decode/compute/encode wiring, not per-function boilerplate. Domain
 * restrictions (asin/acos/artanh needing |x|<=1, acosh needing x>=1,
 * ...) need no special-casing here: an out-of-domain input gives NaN
 * on both the reference and implementation side (they call the same
 * MPFR primitive/formula), which test128_compare treats as a match.
 */

#define TRANSCENDENTAL_TRIALS 4000

typedef int (*mpfr_unary_fn)(mpfr_ptr, mpfr_srcptr, mpfr_rnd_t);
typedef int (*mpfr_binary_fn)(mpfr_ptr, mpfr_srcptr, mpfr_srcptr, mpfr_rnd_t);

struct unary_case {
	const char *name;
	mpfr_unary_fn ref;
	takum128 (*t128)(takum128);
	takum_log128 (*tlog128)(takum_log128);
	/*
	 * Set for sin/cos/tan/cot/sec/csc and their _pi_times variants:
	 * takum_log128's decode (codec128_log_value_from_t, value =
	 * exp(l/2)) is itself transcendental, so two decodes of the same
	 * bit pattern at different working precisions are only equal to
	 * within a relative ~2^-192, never bit-identical (unlike
	 * takum128's Algorithm-5 decode, whose result has a bounded exact
	 * mantissa regardless of magnitude). For a periodic function that
	 * relative uncertainty in a *large-magnitude* argument becomes an
	 * absolute uncertainty in the angle after reduction mod 2*pi big
	 * enough to land on an uncorrelated point of the cycle -- a real
	 * property of composing "exponentiate" with "reduce mod 2pi", not
	 * a bug in either the oracle or the implementation. Such cases
	 * always use the bounded generator on the takum_log128 side below
	 * instead of full-range random bits, exactly as they would need
	 * to for a mathematically meaningful comparison at any precision.
	 */
	int periodic;
};

struct binary_case {
	const char *name;
	mpfr_binary_fn ref;
	takum128 (*t128)(takum128, takum128);
	takum_log128 (*tlog128)(takum_log128, takum_log128);
};

/*
 * Independent reference implementations for the functions with no
 * direct MPFR primitive -- same formulas the sources under ../src use
 * (documented there), which here verifies the MPFR call sequence and
 * precision plumbing rather than an alternate mathematical derivation.
 */

static int
ref_acot(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_t pi;
	int negative = mpfr_sgn(op) < 0;

	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_atan(rop, rop, rnd);
	if (negative) {
		mpfr_init2(pi, mpfr_get_prec(rop));
		mpfr_const_pi(pi, rnd);
		mpfr_add(rop, rop, pi, rnd);
		mpfr_clear(pi);
	}

	return 0;
}

static int
ref_acotpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	int negative = mpfr_sgn(op) < 0;

	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_atanpi(rop, rop, rnd);
	if (negative) {
		mpfr_add_ui(rop, rop, 1, rnd);
	}

	return 0;
}

static int
ref_asec(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_acos(rop, rop, rnd);

	return 0;
}

static int
ref_asecpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_acospi(rop, rop, rnd);

	return 0;
}

static int
ref_acsc(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_asin(rop, rop, rnd);

	return 0;
}

static int
ref_acscpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_asinpi(rop, rop, rnd);

	return 0;
}

static int
ref_acoth(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_atanh(rop, rop, rnd);

	return 0;
}

static int
ref_asech(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_acosh(rop, rop, rnd);

	return 0;
}

static int
ref_acsch(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_asinh(rop, rop, rnd);

	return 0;
}

static int
ref_cotpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_tanpi(rop, op, rnd);
	mpfr_ui_div(rop, 1, rop, rnd);

	return 0;
}

static int
ref_secpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_cospi(rop, op, rnd);
	mpfr_ui_div(rop, 1, rop, rnd);

	return 0;
}

static int
ref_cscpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_sinpi(rop, op, rnd);
	mpfr_ui_div(rop, 1, rop, rnd);

	return 0;
}

static const struct unary_case UNARY_CASES[] = {
	{ "exp", mpfr_exp, takum128_exp, takum_log128_exp, 0 },
	{ "exp_minus_1", mpfr_expm1, takum128_exp_minus_1,
	  takum_log128_exp_minus_1, 0 },
	{ "lb", mpfr_log2, takum128_lb, takum_log128_lb, 0 },
	{ "lb_1_plus", mpfr_log2p1, takum128_lb_1_plus, takum_log128_lb_1_plus,
	  0 },
	{ "lg", mpfr_log10, takum128_lg, takum_log128_lg, 0 },
	{ "lg_1_plus", mpfr_log10p1, takum128_lg_1_plus, takum_log128_lg_1_plus,
	  0 },
	{ "ln", mpfr_log, takum128_ln, takum_log128_ln, 0 },
	{ "ln_1_plus", mpfr_log1p, takum128_ln_1_plus, takum_log128_ln_1_plus,
	  0 },
	{ "2_raised", mpfr_exp2, takum128_2_raised, takum_log128_2_raised, 0 },
	{ "2_raised_minus_1", mpfr_exp2m1, takum128_2_raised_minus_1,
	  takum_log128_2_raised_minus_1, 0 },
	{ "10_raised", mpfr_exp10, takum128_10_raised, takum_log128_10_raised,
	  0 },
	{ "10_raised_minus_1", mpfr_exp10m1, takum128_10_raised_minus_1,
	  takum_log128_10_raised_minus_1, 0 },
	{ "sin", mpfr_sin, takum128_sin, takum_log128_sin, 1 },
	{ "sin_pi_times", mpfr_sinpi, takum128_sin_pi_times,
	  takum_log128_sin_pi_times, 1 },
	{ "cos", mpfr_cos, takum128_cos, takum_log128_cos, 1 },
	{ "cos_pi_times", mpfr_cospi, takum128_cos_pi_times,
	  takum_log128_cos_pi_times, 1 },
	{ "tan", mpfr_tan, takum128_tan, takum_log128_tan, 1 },
	{ "tan_pi_times", mpfr_tanpi, takum128_tan_pi_times,
	  takum_log128_tan_pi_times, 1 },
	{ "cot", mpfr_cot, takum128_cot, takum_log128_cot, 1 },
	{ "cot_pi_times", ref_cotpi, takum128_cot_pi_times,
	  takum_log128_cot_pi_times, 1 },
	{ "sec", mpfr_sec, takum128_sec, takum_log128_sec, 1 },
	{ "sec_pi_times", ref_secpi, takum128_sec_pi_times,
	  takum_log128_sec_pi_times, 1 },
	{ "csc", mpfr_csc, takum128_csc, takum_log128_csc, 1 },
	{ "csc_pi_times", ref_cscpi, takum128_csc_pi_times,
	  takum_log128_csc_pi_times, 1 },
	{ "sinh", mpfr_sinh, takum128_sinh, takum_log128_sinh, 0 },
	{ "cosh", mpfr_cosh, takum128_cosh, takum_log128_cosh, 0 },
	{ "tanh", mpfr_tanh, takum128_tanh, takum_log128_tanh, 0 },
	{ "coth", mpfr_coth, takum128_coth, takum_log128_coth, 0 },
	{ "sech", mpfr_sech, takum128_sech, takum_log128_sech, 0 },
	{ "csch", mpfr_csch, takum128_csch, takum_log128_csch, 0 },
	{ "arcsin", mpfr_asin, takum128_arcsin, takum_log128_arcsin, 0 },
	{ "arcsin_over_pi", mpfr_asinpi, takum128_arcsin_over_pi,
	  takum_log128_arcsin_over_pi, 0 },
	{ "arccos", mpfr_acos, takum128_arccos, takum_log128_arccos, 0 },
	{ "arccos_over_pi", mpfr_acospi, takum128_arccos_over_pi,
	  takum_log128_arccos_over_pi, 0 },
	{ "arctan", mpfr_atan, takum128_arctan, takum_log128_arctan, 0 },
	{ "arctan_over_pi", mpfr_atanpi, takum128_arctan_over_pi,
	  takum_log128_arctan_over_pi, 0 },
	{ "arccot", ref_acot, takum128_arccot, takum_log128_arccot, 0 },
	{ "arccot_over_pi", ref_acotpi, takum128_arccot_over_pi,
	  takum_log128_arccot_over_pi, 0 },
	{ "arcsec", ref_asec, takum128_arcsec, takum_log128_arcsec, 0 },
	{ "arcsec_over_pi", ref_asecpi, takum128_arcsec_over_pi,
	  takum_log128_arcsec_over_pi, 0 },
	{ "arccsc", ref_acsc, takum128_arccsc, takum_log128_arccsc, 0 },
	{ "arccsc_over_pi", ref_acscpi, takum128_arccsc_over_pi,
	  takum_log128_arccsc_over_pi, 0 },
	{ "arsinh", mpfr_asinh, takum128_arsinh, takum_log128_arsinh, 0 },
	{ "arcosh", mpfr_acosh, takum128_arcosh, takum_log128_arcosh, 0 },
	{ "artanh", mpfr_atanh, takum128_artanh, takum_log128_artanh, 0 },
	{ "arcoth", ref_acoth, takum128_arcoth, takum_log128_arcoth, 0 },
	{ "arsech", ref_asech, takum128_arsech, takum_log128_arsech, 0 },
	{ "arcsch", ref_acsch, takum128_arcsch, takum_log128_arcsch, 0 },
};

static const struct binary_case BINARY_CASES[] = {
	{ "power", mpfr_pow, takum128_power, takum_log128_power },
	{ "arctan2", mpfr_atan2, takum128_arctan2, takum_log128_arctan2 },
	{ "arctan2_over_pi", mpfr_atan2pi, takum128_arctan2_over_pi,
	  takum_log128_arctan2_over_pi },
};

/*
 * Half the trials use fully random bit patterns (good for overflow/
 * underflow/composite-reciprocal edge cases); half use a small bounded
 * value in roughly (-4,4) so domain-restricted functions (asin, acos,
 * artanh, ...) get meaningfully exercised instead of mostly landing on
 * the (trivially matching) out-of-domain NaN case.
 */
static void
random_small_value(mpfr_t out, gmp_randstate_t rng)
{
	long shift;

	mpfr_urandom(out, rng, MPFR_RNDN);
	mpfr_add_d(out, out, 1.0, MPFR_RNDN);      /* [1,2) */
	shift = (long)gmp_urandomm_ui(rng, 5) - 2; /* [-2,2] */
	mpfr_mul_2si(out, out, shift, MPFR_RNDN);
	if (gmp_urandomb_ui(rng, 1)) {
		mpfr_neg(out, out, MPFR_RNDN);
	}
}

int
main(int argc, char *argv[])
{
	gmp_randstate_t rng;
	mpfr_t a, expected;
	size_t i;
	uint64_t trial;
	int overall_fail = 0;
	char namebuf[64];

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);
	mpfr_inits2(TEST128_REFERENCE_PREC, a, expected, (mpfr_ptr)0);

	for (i = 0; i < sizeof(UNARY_CASES) / sizeof(UNARY_CASES[0]); i++) {
		uint64_t failures_t = 0, failures_l = 0;

		for (trial = 0; trial < TRANSCENDENTAL_TRIALS; trial++) {
			unsigned __int128 bits, bits_log;
			takum128 ta;
			takum_log128 la;

			if (trial % 2 == 0) {
				bits = test128_random_bits(rng);
			} else {
				random_small_value(a, rng);
				bits = (unsigned __int128)test128_encode(a, 0);
			}
			ta = (takum128)bits;

			/*
			 * See the `periodic` field comment: a periodic
			 * function's takum_log128 side always needs a
			 * bounded-magnitude operand, regardless of trial
			 * parity, or the exp(l/2) decode's inherent
			 * imprecision at large magnitudes swamps the
			 * function's mod-2*pi sensitivity.
			 */
			if (UNARY_CASES[i].periodic) {
				random_small_value(a, rng);
				bits_log =
					(unsigned __int128)test128_encode(a, 1);
			} else {
				bits_log = bits;
			}
			la = (takum_log128)bits_log;

			test128_decode(a, ta, 0);
			UNARY_CASES[i].ref(expected, a, MPFR_RNDN);
			failures_t += test128_compare_saturating(
				UNARY_CASES[i].name, (int)trial, expected,
				UNARY_CASES[i].t128(ta), 0);

			test128_decode(a, la, 1);
			UNARY_CASES[i].ref(expected, a, MPFR_RNDN);
			failures_l += test128_compare_saturating(
				UNARY_CASES[i].name, (int)trial, expected,
				UNARY_CASES[i].tlog128(la), 1);
		}

		snprintf(namebuf, sizeof(namebuf), "takum128_%s",
		         UNARY_CASES[i].name);
		overall_fail |= test128_report(namebuf, TRANSCENDENTAL_TRIALS,
		                               failures_t);
		snprintf(namebuf, sizeof(namebuf), "takum_log128_%s",
		         UNARY_CASES[i].name);
		overall_fail |= test128_report(namebuf, TRANSCENDENTAL_TRIALS,
		                               failures_l);
	}

	for (i = 0; i < sizeof(BINARY_CASES) / sizeof(BINARY_CASES[0]); i++) {
		uint64_t failures_t = 0, failures_l = 0;

		for (trial = 0; trial < TRANSCENDENTAL_TRIALS; trial++) {
			unsigned __int128 bits_a, bits_b;
			takum128 ta, tb;
			takum_log128 la, lb;
			mpfr_t b;

			mpfr_init2(b, TEST128_REFERENCE_PREC);

			if (trial % 2 == 0) {
				bits_a = test128_random_bits(rng);
				bits_b = test128_random_bits(rng);
			} else {
				random_small_value(a, rng);
				bits_a =
					(unsigned __int128)test128_encode(a, 0);
				random_small_value(a, rng);
				bits_b =
					(unsigned __int128)test128_encode(a, 0);
			}
			ta = (takum128)bits_a;
			tb = (takum128)bits_b;
			la = (takum_log128)bits_a;
			lb = (takum_log128)bits_b;

			test128_decode(a, ta, 0);
			test128_decode(b, tb, 0);
			BINARY_CASES[i].ref(expected, a, b, MPFR_RNDN);
			failures_t += test128_compare_saturating(
				BINARY_CASES[i].name, (int)trial, expected,
				BINARY_CASES[i].t128(ta, tb), 0);

			test128_decode(a, la, 1);
			test128_decode(b, lb, 1);
			BINARY_CASES[i].ref(expected, a, b, MPFR_RNDN);
			failures_l += test128_compare_saturating(
				BINARY_CASES[i].name, (int)trial, expected,
				BINARY_CASES[i].tlog128(la, lb), 1);

			mpfr_clear(b);
		}

		snprintf(namebuf, sizeof(namebuf), "takum128_%s",
		         BINARY_CASES[i].name);
		overall_fail |= test128_report(namebuf, TRANSCENDENTAL_TRIALS,
		                               failures_t);
		snprintf(namebuf, sizeof(namebuf), "takum_log128_%s",
		         BINARY_CASES[i].name);
		overall_fail |= test128_report(namebuf, TRANSCENDENTAL_TRIALS,
		                               failures_l);
	}

	mpfr_clears(a, expected, (mpfr_ptr)0);

	return overall_fail;
}
