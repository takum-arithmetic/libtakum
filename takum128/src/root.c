/* See LICENSE file for copyright and license details. */
#include <stdint.h> /* before mpfr.h, see integer_power.c */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/*
 * Uses mpfr_pow with a reciprocal exponent (1/n) rather than
 * mpfr_rootn_si, deliberately: ../../src/root.c computes roots the same
 * way (powl(f, 1.0l/n)), which means an odd root of a negative number
 * already returns NaR in the reference implementation (pow with a
 * negative base only special-cases an *exactly* integral exponent, and
 * 1/n generally isn't one) -- mpfr_rootn_si would handle that case
 * correctly and thus diverge from the width-8/16/32/64 behaviour this
 * is meant to match.
 */
takum128
takum128_root(takum128 t, int64_t n)
{
	mpfr_t l, v, nf, res, out_l;
	takum128 result;

	if (n == 0 || (t < 0 && n % 2 == 0)) {
		return TAKUM128_NAR;
	}

	mpfr_inits2(TAKUM128_MPFR_PREC, l, v, nf, res, out_l, (mpfr_ptr)0);

	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(v, t < 0, l);
	mpfr_set_sj(nf, (intmax_t)n, MPFR_RNDN);
	mpfr_ui_div(nf, 1, nf, MPFR_RNDN); /* nf = 1/n */
	mpfr_pow(res, v, nf, MPFR_RNDN);

	codec128_linear_l_from_value(out_l, res);
	result = codec128_log_from_s_and_l(mpfr_sgn(res) < 0, out_l);

	mpfr_clears(l, v, nf, res, out_l, (mpfr_ptr)0);

	return result;
}

/*
 * The case NaR is automatically covered given NaN/n=NaN holds for any
 * n. Mirrors ../../src/root.c's takum_log* case: an nth root is a
 * closed-form division of the stored l by n.
 */
takum_log128
takum_log128_root(takum_log128 t, int64_t n)
{
	mpfr_t l, nf;
	takum_log128 result;

	if (n == 0 || (t < 0 && n % 2 == 0) || (t == 0 && n < 0)) {
		return TAKUM_LOG128_NAR;
	}

	mpfr_inits2(TAKUM128_MPFR_PREC, l, nf, (mpfr_ptr)0);
	codec128_log_to_l(l, t);
	mpfr_set_sj(nf, (intmax_t)n, MPFR_RNDN);
	mpfr_div(l, l, nf, MPFR_RNDN);

	result = codec128_log_from_s_and_l((t < 0), l);

	mpfr_clears(l, nf, (mpfr_ptr)0);

	return result;
}
