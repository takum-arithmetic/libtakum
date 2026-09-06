/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

takum128
takum128_multiplication(takum128 a, takum128 b)
{
	mpfr_t la, lb, va, vb, res, l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, la, lb, va, vb, res, l, (mpfr_ptr)0);

	codec128_log_to_l(la, (takum_log128)a);
	codec128_linear_value_from_s_and_l(va, a < 0, la);
	codec128_log_to_l(lb, (takum_log128)b);
	codec128_linear_value_from_s_and_l(vb, b < 0, lb);

	mpfr_mul(res, va, vb, MPFR_RNDN);

	codec128_linear_l_from_value(l, res);
	result = codec128_log_from_s_and_l(mpfr_sgn(res) < 0, l);

	mpfr_clears(la, lb, va, vb, res, l, (mpfr_ptr)0);

	return result;
}

/*
 * Unlike the regular (tapered) takum128, takum_log128's stored value IS
 * (twice) a logarithm, so multiplication has a closed form directly on
 * the two operands' l: l(a*b) = l(a) + l(b). Mirrors
 * ../../src/multiplication.c's takum_log* case exactly -- codec128_log_to_l
 * returning -inf for 0 and NaN for NaR is enough to make zero and NaR
 * propagate correctly through the addition with no extra special-casing.
 */
takum_log128
takum_log128_multiplication(takum_log128 a, takum_log128 b)
{
	mpfr_t la, lb, lres;
	takum_log128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, la, lb, lres, (mpfr_ptr)0);

	codec128_log_to_l(la, a);
	codec128_log_to_l(lb, b);
	mpfr_add(lres, la, lb, MPFR_RNDN);

	result = codec128_log_from_s_and_l((a > 0) != (b > 0), lres);

	mpfr_clears(la, lb, lres, (mpfr_ptr)0);

	return result;
}
