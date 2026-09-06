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
	mpfr_t a, b, expected;
	takum128 ta, tb, tres;
	takum_log128 la, lb, lres;
	unsigned __int128 bits_a, bits_b;
	uint64_t i, failures_takum = 0, failures_log = 0;

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);
	mpfr_inits2(TEST128_REFERENCE_PREC, a, b, expected, (mpfr_ptr)0);

	for (i = 0; i < TEST128_TRIALS; i++) {
		bits_a = test128_random_bits(rng);
		bits_b = test128_random_bits(rng);

		ta = (takum128)bits_a;
		tb = (takum128)bits_b;
		test128_decode(a, ta, 0);
		test128_decode(b, tb, 0);
		mpfr_mul(expected, a, b, MPFR_RNDN);
		tres = takum128_multiplication(ta, tb);
		failures_takum += test128_compare_saturating(
			"takum128_multiplication", (int)i, expected, tres, 0);

		la = (takum_log128)bits_a;
		lb = (takum_log128)bits_b;
		test128_decode(a, la, 1);
		test128_decode(b, lb, 1);
		mpfr_mul(expected, a, b, MPFR_RNDN);
		lres = takum_log128_multiplication(la, lb);
		failures_log += test128_compare_saturating(
			"takum_log128_multiplication", (int)i, expected, lres,
			1);
	}

	mpfr_clears(a, b, expected, (mpfr_ptr)0);

	return test128_report("takum128_multiplication", TEST128_TRIALS,
	                      failures_takum) |
	       test128_report("takum_log128_multiplication", TEST128_TRIALS,
	                      failures_log);
}
