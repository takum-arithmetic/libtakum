/* See LICENSE file for copyright and license details. */
#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>

#include "../../takum128.h"

#include "util128.h"

int
main(int argc, char *argv[])
{
	gmp_randstate_t rng;
	mpfr_t a, expected;
	takum128 ta, tres;
	takum_log128 la, lres;
	unsigned __int128 bits;
	uint64_t i, failures_takum = 0, failures_log = 0;

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);
	mpfr_inits2(TEST128_REFERENCE_PREC, a, expected, (mpfr_ptr)0);

	for (i = 0; i < TEST128_TRIALS; i++) {
		bits = test128_random_bits(rng);

		ta = (takum128)bits;
		test128_decode(a, ta, 0);
		/* 1/0 = inf, which test128_decode's NaN-for-NaR convention
		 * (via linear_l_from_value treating inf as NaN) makes an
		 * inf expected mismatch a NaN actual -- so compare via NaR
		 * bit pattern directly for the zero case instead. */
		if (ta == 0) {
			failures_takum +=
				(takum128_inversion(ta) != TAKUM128_NAR);
		} else {
			mpfr_ui_div(expected, 1, a, MPFR_RNDN);
			tres = takum128_inversion(ta);
			failures_takum += test128_compare_saturating(
				"takum128_inversion", (int)i, expected, tres,
				0);
		}

		la = (takum_log128)bits;
		if (la == TAKUM_LOG128_NAR) {
			continue;
		}
		test128_decode(a, la, 1);
		if (mpfr_zero_p(a)) {
			failures_log += (takum_log128_inversion(la) !=
			                 TAKUM_LOG128_NAR);
		} else {
			mpfr_ui_div(expected, 1, a, MPFR_RNDN);
			lres = takum_log128_inversion(la);
			failures_log += test128_compare_saturating(
				"takum_log128_inversion", (int)i, expected,
				lres, 1);
		}
	}

	mpfr_clears(a, expected, (mpfr_ptr)0);

	return test128_report("takum128_inversion", TEST128_TRIALS,
	                      failures_takum) |
	       test128_report("takum_log128_inversion", TEST128_TRIALS,
	                      failures_log);
}
