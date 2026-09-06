/* See LICENSE file for copyright and license details. */
#include <stdint.h> /* included before mpfr.h so its intmax_t-taking
                     * _sj functions (mpfr_pow_sj) are declared, letting
                     * this take the full int64_t range of n without a
                     * narrowing cast to `long` */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

takum128
takum128_integer_power(takum128 t, int64_t n)
{
	mpfr_t l, v, res, out_l;
	takum128 result;

	if (t == TAKUM128_NAR || (t == 0 && n <= 0)) {
		return TAKUM128_NAR;
	}

	mpfr_inits2(TAKUM128_MPFR_PREC, l, v, res, out_l, (mpfr_ptr)0);

	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(v, t < 0, l);
	mpfr_pow_sj(res, v, (intmax_t)n, MPFR_RNDN);

	codec128_linear_l_from_value(out_l, res);
	result = codec128_log_from_s_and_l(mpfr_sgn(res) < 0, out_l);

	mpfr_clears(l, v, res, out_l, (mpfr_ptr)0);

	return result;
}

/*
 * The case NaR is automatically covered given NaN*n=NaN holds for any
 * n. Mirrors ../../src/integer_power.c's takum_log* case: raising to an
 * integer power is a closed-form multiply of the stored l by n.
 */
takum_log128
takum_log128_integer_power(takum_log128 t, int64_t n)
{
	mpfr_t l, nf;
	takum_log128 result;

	if (t == 0 && n <= 0) {
		return TAKUM_LOG128_NAR;
	}

	mpfr_inits2(TAKUM128_MPFR_PREC, l, nf, (mpfr_ptr)0);
	codec128_log_to_l(l, t);
	mpfr_set_sj(nf, (intmax_t)n, MPFR_RNDN); /* exact, n fits in 64 bits */
	mpfr_mul(l, l, nf, MPFR_RNDN);

	result = codec128_log_from_s_and_l((t < 0 && n % 2 != 0), l);

	mpfr_clears(l, nf, (mpfr_ptr)0);

	return result;
}
