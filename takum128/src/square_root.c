/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

takum128
takum128_square_root(takum128 t)
{
	mpfr_t l, v, res, out_l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, l, v, res, out_l, (mpfr_ptr)0);

	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(v, t < 0, l);
	/* mpfr_sqrt of a negative finite value yields NaN, which propagates
	 * to NaR through codec128_linear_l_from_value/codec128_log_from_s_and_l
	 * exactly as intended -- no special case needed. */
	mpfr_sqrt(res, v, MPFR_RNDN);

	codec128_linear_l_from_value(out_l, res);
	result = codec128_log_from_s_and_l(mpfr_sgn(res) < 0, out_l);

	mpfr_clears(l, v, res, out_l, (mpfr_ptr)0);

	return result;
}

/*
 * The case NaR is automatically covered given NaN/2=NaN holds. Mirrors
 * ../../src/square_root.c's takum_log* case: sqrt halves the stored l,
 * but only for non-negative t (l/2 alone can't express "negative input"
 * since NaR isn't simply "the negative of a valid l").
 */
takum_log128
takum_log128_square_root(takum_log128 t)
{
	mpfr_t l;
	takum_log128 result;

	if (t < 0) {
		return TAKUM_LOG128_NAR;
	}

	mpfr_init2(l, TAKUM128_MPFR_PREC);
	codec128_log_to_l(l, t);
	mpfr_mul_2si(l, l, -1, MPFR_RNDN);
	result = codec128_log_from_s_and_l(0, l);
	mpfr_clear(l);

	return result;
}
