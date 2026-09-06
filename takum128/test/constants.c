/* See LICENSE file for copyright and license details. */
#include <mpfr.h>
#include <stdio.h>

#include "../../takum128.h"

#include "util128.h"

struct constant_case {
	const char *name;
	takum128 t128;
	takum_log128 tlog128;
	void (*ref)(mpfr_t);
};

static void
ref_pi(mpfr_t out)
{
	mpfr_const_pi(out, MPFR_RNDN);
}

static void
ref_pi_over_2(mpfr_t out)
{
	mpfr_const_pi(out, MPFR_RNDN);
	mpfr_div_ui(out, out, 2, MPFR_RNDN);
}

static void
ref_2_pi(mpfr_t out)
{
	mpfr_const_pi(out, MPFR_RNDN);
	mpfr_mul_ui(out, out, 2, MPFR_RNDN);
}

static void
ref_gamma(mpfr_t out)
{
	mpfr_const_euler(out, MPFR_RNDN);
}

static void
ref_ln_2(mpfr_t out)
{
	mpfr_const_log2(out, MPFR_RNDN);
}

static void
ref_ln_10(mpfr_t out)
{
	mpfr_set_ui(out, 10, MPFR_RNDN);
	mpfr_log(out, out, MPFR_RNDN);
}

static void
ref_lb_10(mpfr_t out)
{
	mpfr_set_ui(out, 10, MPFR_RNDN);
	mpfr_log2(out, out, MPFR_RNDN);
}

static void
ref_lg_2(mpfr_t out)
{
	mpfr_set_ui(out, 2, MPFR_RNDN);
	mpfr_log10(out, out, MPFR_RNDN);
}

static void
ref_phi(mpfr_t out)
{
	mpfr_sqrt_ui(out, 5, MPFR_RNDN);
	mpfr_add_ui(out, out, 1, MPFR_RNDN);
	mpfr_div_ui(out, out, 2, MPFR_RNDN);
}

static void
ref_sqrt_2(mpfr_t out)
{
	mpfr_sqrt_ui(out, 2, MPFR_RNDN);
}

static void
ref_sqrt_3(mpfr_t out)
{
	mpfr_sqrt_ui(out, 3, MPFR_RNDN);
}

static void
ref_sqrt_5(mpfr_t out)
{
	mpfr_sqrt_ui(out, 5, MPFR_RNDN);
}

static void
ref_sqrt_6(mpfr_t out)
{
	mpfr_sqrt_ui(out, 6, MPFR_RNDN);
}

/*
 * A representative subset (one per distinct MPFR-computed quantity;
 * the pi multiples/fractions all derive from the same mpfr_const_pi
 * call in ../tools/gen_constants.c, so re-checking every one of them
 * would just be re-testing integer multiplication).
 */
static const struct constant_case CASES[] = {
	{ "PI", TAKUM128_PI, TAKUM_LOG128_PI, ref_pi },
	{ "PI_OVER_2", TAKUM128_PI_OVER_2, TAKUM_LOG128_PI_OVER_2,
	  ref_pi_over_2 },
	{ "2_PI", TAKUM128_2_PI, TAKUM_LOG128_2_PI, ref_2_pi },
	{ "GAMMA", TAKUM128_GAMMA, TAKUM_LOG128_GAMMA, ref_gamma },
	{ "LN_2", TAKUM128_LN_2, TAKUM_LOG128_LN_2, ref_ln_2 },
	{ "LN_10", TAKUM128_LN_10, TAKUM_LOG128_LN_10, ref_ln_10 },
	{ "LB_10", TAKUM128_LB_10, TAKUM_LOG128_LB_10, ref_lb_10 },
	{ "LG_2", TAKUM128_LG_2, TAKUM_LOG128_LG_2, ref_lg_2 },
	{ "PHI", TAKUM128_PHI, TAKUM_LOG128_PHI, ref_phi },
	{ "SQUARE_ROOT_2", TAKUM128_SQUARE_ROOT_2, TAKUM_LOG128_SQUARE_ROOT_2,
	  ref_sqrt_2 },
	{ "SQUARE_ROOT_3", TAKUM128_SQUARE_ROOT_3, TAKUM_LOG128_SQUARE_ROOT_3,
	  ref_sqrt_3 },
	{ "SQUARE_ROOT_5", TAKUM128_SQUARE_ROOT_5, TAKUM_LOG128_SQUARE_ROOT_5,
	  ref_sqrt_5 },
	{ "SQUARE_ROOT_6", TAKUM128_SQUARE_ROOT_6, TAKUM_LOG128_SQUARE_ROOT_6,
	  ref_sqrt_6 },
};

int
main(int argc, char *argv[])
{
	mpfr_t expected, actual;
	size_t i;
	uint64_t failures = 0;
	char namebuf[64];

	(void)argc;
	argv0 = argv[0];

	mpfr_inits2(TEST128_REFERENCE_PREC, expected, actual, (mpfr_ptr)0);

	for (i = 0; i < sizeof(CASES) / sizeof(CASES[0]); i++) {
		CASES[i].ref(expected);

		test128_decode(actual, CASES[i].t128, 0);
		snprintf(namebuf, sizeof(namebuf), "TAKUM128_%s",
		         CASES[i].name);
		failures += test128_compare(namebuf, 0, expected, actual);

		test128_decode(actual, CASES[i].tlog128, 1);
		snprintf(namebuf, sizeof(namebuf), "TAKUM_LOG128_%s",
		         CASES[i].name);
		failures += test128_compare(namebuf, 0, expected, actual);
	}

	mpfr_clears(expected, actual, (mpfr_ptr)0);

	return test128_report("constants",
	                      2 * (sizeof(CASES) / sizeof(CASES[0])), failures);
}
