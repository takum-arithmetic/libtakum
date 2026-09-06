/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

takum128
takum128_addition(takum128 a, takum128 b)
{
	mpfr_t la, lb, va, vb, res, l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, la, lb, va, vb, res, l, (mpfr_ptr)0);

	codec128_log_to_l(la, (takum_log128)a);
	codec128_linear_value_from_s_and_l(va, a < 0, la);
	codec128_log_to_l(lb, (takum_log128)b);
	codec128_linear_value_from_s_and_l(vb, b < 0, lb);

	mpfr_add(res, va, vb, MPFR_RNDN);

	codec128_linear_l_from_value(l, res);
	result = codec128_log_from_s_and_l(mpfr_sgn(res) < 0, l);

	mpfr_clears(la, lb, va, vb, res, l, (mpfr_ptr)0);

	return result;
}

/*
 * Unlike multiplication/division, addition has no closed form in the
 * log domain, so this decodes both operands to their actual linear
 * value (codec128_log_value_from_t, which already maps 0 -> 0 and NaR
 * -> NaN) and re-encodes the sum the same way takum128_addition does.
 */
takum_log128
takum_log128_addition(takum_log128 a, takum_log128 b)
{
	mpfr_t va, vb, res;
	takum_log128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, va, vb, res, (mpfr_ptr)0);

	codec128_log_value_from_t(va, a);
	codec128_log_value_from_t(vb, b);

	mpfr_add(res, va, vb, MPFR_RNDN);

	result = codec128_log_from_value(res);

	mpfr_clears(va, vb, res, (mpfr_ptr)0);

	return result;
}
