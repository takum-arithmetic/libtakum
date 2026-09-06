/* See LICENSE file for copyright and license details. */
#include <stdint.h> /* before mpfr.h, so mpfr_pow_sj is declared */
#include <gmp.h>
#include <mpfr.h>

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
	int64_t n;
	uint64_t i, failures_takum = 0, failures_log = 0;

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);
	mpfr_inits2(TEST128_REFERENCE_PREC, a, expected, (mpfr_ptr)0);

	for (i = 0; i < TEST128_TRIALS; i++) {
		bits = test128_random_bits(rng);
		/* keep exponents small enough that the reference power
		 * doesn't itself overflow mpfr's (huge but finite) range */
		n = (int64_t)(gmp_urandomm_ui(rng, 41) - 20);

		ta = (takum128)bits;
		if (ta == TAKUM128_NAR || (ta == 0 && n <= 0)) {
			failures_takum +=
				(takum128_integer_power(ta, n) != TAKUM128_NAR);
		} else {
			test128_decode(a, ta, 0);
			mpfr_pow_sj(expected, a, (intmax_t)n, MPFR_RNDN);
			tres = takum128_integer_power(ta, n);
			failures_takum += test128_compare_saturating(
				"takum128_integer_power", (int)i, expected,
				tres, 0);
		}

		la = (takum_log128)bits;
		if (la == 0 && n <= 0) {
			failures_log += (takum_log128_integer_power(la, n) !=
			                 TAKUM_LOG128_NAR);
		} else {
			test128_decode(a, la, 1);
			mpfr_pow_sj(expected, a, (intmax_t)n, MPFR_RNDN);
			lres = takum_log128_integer_power(la, n);
			failures_log += test128_compare_saturating(
				"takum_log128_integer_power", (int)i, expected,
				lres, 1);
		}
	}

	mpfr_clears(a, expected, (mpfr_ptr)0);

	return test128_report("takum128_integer_power", TEST128_TRIALS,
	                      failures_takum) |
	       test128_report("takum_log128_integer_power", TEST128_TRIALS,
	                      failures_log);
}
