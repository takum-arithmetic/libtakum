/* See LICENSE file for copyright and license details. */
#include <stdint.h> /* before mpfr.h, so mpfr_set_sj is declared */
#include <gmp.h>
#include <mpfr.h>

#include "../../takum128.h"

#include "util128.h"

int
main(int argc, char *argv[])
{
	gmp_randstate_t rng;
	mpfr_t a, nf, expected;
	takum128 ta, tres;
	takum_log128 la, lres;
	unsigned __int128 bits;
	int64_t n;
	uint64_t i, failures_takum = 0, failures_log = 0;

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);
	mpfr_inits2(TEST128_REFERENCE_PREC, a, nf, expected, (mpfr_ptr)0);

	for (i = 0; i < TEST128_TRIALS; i++) {
		bits = test128_random_bits(rng);
		/* nonzero, keep small so 1/n stays well-conditioned */
		n = (int64_t)(gmp_urandomm_ui(rng, 20) + 1);
		if (i % 2 == 0) {
			n = -n;
		}

		ta = (takum128)bits;
		if (n == 0 || (ta < 0 && n % 2 == 0) || (ta == 0 && n < 0)) {
			/*
			 * 0^negative is +inf in MPFR/IEEE convention, which
			 * takum128_root's value round-trip (see root.c)
			 * turns into NaR since takum has no infinity --
			 * covered here explicitly rather than via the
			 * general mpfr comparison below, which has no
			 * "infinity" case of its own to match against.
			 */
			failures_takum +=
				(takum128_root(ta, n) != TAKUM128_NAR);
		} else {
			test128_decode(a, ta, 0);
			mpfr_set_sj(nf, (intmax_t)n, MPFR_RNDN);
			mpfr_ui_div(nf, 1, nf, MPFR_RNDN);
			mpfr_pow(expected, a, nf, MPFR_RNDN);
			tres = takum128_root(ta, n);
			failures_takum += test128_compare_saturating(
				"takum128_root", (int)i, expected, tres, 0);
		}

		la = (takum_log128)bits;
		if (n == 0 || (la < 0 && n % 2 == 0) || (la == 0 && n < 0)) {
			failures_log +=
				(takum_log128_root(la, n) != TAKUM_LOG128_NAR);
		} else {
			/*
			 * Unlike takum128_root (which computes pow(a, 1/n)
			 * on the signed value, and so -- matching upstream's
			 * own takumN_root -- returns NaR for an odd root of
			 * a negative number since 1/n generally isn't an
			 * exact integer exponent), takum_log128_root takes
			 * the root of |value| and reapplies the sign
			 * separately (see root.c), so it correctly handles
			 * that case. Mirror that here instead of naively
			 * calling mpfr_pow on a negative base.
			 */
			test128_decode(a, la, 1);
			mpfr_set_sj(nf, (intmax_t)n, MPFR_RNDN);
			mpfr_ui_div(nf, 1, nf, MPFR_RNDN);
			mpfr_abs(a, a, MPFR_RNDN);
			mpfr_pow(expected, a, nf, MPFR_RNDN);
			if (la < 0) {
				mpfr_neg(expected, expected, MPFR_RNDN);
			}
			lres = takum_log128_root(la, n);
			failures_log += test128_compare_saturating(
				"takum_log128_root", (int)i, expected, lres, 1);
		}
	}

	mpfr_clears(a, nf, expected, (mpfr_ptr)0);

	return test128_report("takum128_root", TEST128_TRIALS, failures_takum) |
	       test128_report("takum_log128_root", TEST128_TRIALS,
	                      failures_log);
}
