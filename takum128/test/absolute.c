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
	mpfr_t a, expected, actual;
	takum128 ta, tres;
	takum_log128 la, lres;
	unsigned __int128 bits;
	uint64_t i, failures_takum = 0, failures_log = 0;

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);
	mpfr_inits2(TEST128_REFERENCE_PREC, a, expected, actual, (mpfr_ptr)0);

	for (i = 0; i < TEST128_TRIALS; i++) {
		bits = test128_random_bits(rng);

		ta = (takum128)bits;
		test128_decode(a, ta, 0);
		mpfr_abs(expected, a, MPFR_RNDN);
		tres = takum128_absolute(ta);
		test128_decode(actual, tres, 0);
		failures_takum += test128_compare("takum128_absolute", (int)i,
		                                  expected, actual);

		la = (takum_log128)bits;
		test128_decode(a, la, 1);
		mpfr_abs(expected, a, MPFR_RNDN);
		lres = takum_log128_absolute(la);
		test128_decode(actual, lres, 1);
		failures_log += test128_compare("takum_log128_absolute", (int)i,
		                                expected, actual);
	}

	mpfr_clears(a, expected, actual, (mpfr_ptr)0);

	return test128_report("takum128_absolute", TEST128_TRIALS,
	                      failures_takum) |
	       test128_report("takum_log128_absolute", TEST128_TRIALS,
	                      failures_log);
}
