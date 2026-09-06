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
		/* mpfr_sqrt of a negative finite value yields NaN, matching
		 * takum128_square_root's NaR result -- no special case. */
		mpfr_sqrt(expected, a, MPFR_RNDN);
		tres = takum128_square_root(ta);
		failures_takum += test128_compare_saturating(
			"takum128_square_root", (int)i, expected, tres, 0);

		/* takum_log128_square_root explicitly rejects negative t
		 * rather than letting NaN propagate, so skip those bit
		 * patterns here (they're exercised as NaR by construction,
		 * not compared against an oracle). */
		la = (takum_log128)bits;
		if (la < 0) {
			continue;
		}
		test128_decode(a, la, 1);
		mpfr_sqrt(expected, a, MPFR_RNDN);
		lres = takum_log128_square_root(la);
		failures_log += test128_compare_saturating(
			"takum_log128_square_root", (int)i, expected, lres, 1);
	}

	mpfr_clears(a, expected, (mpfr_ptr)0);

	return test128_report("takum128_square_root", TEST128_TRIALS,
	                      failures_takum) |
	       test128_report("takum_log128_square_root", TEST128_TRIALS,
	                      failures_log);
}
