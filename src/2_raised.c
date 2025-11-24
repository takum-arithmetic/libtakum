/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/* fix under- and overflow in the result */
#define TWO_RAISED_RESULT_FIXER_MACRO(arg, res)                                \
	(((res) == 0.0) ? DBL_MIN : isinf(res) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(2_raised, exp2, TWO_RAISED_RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(2_raised, exp2,
                                   TWO_RAISED_RESULT_FIXER_MACRO)

/*
 * This implementation is a bit of a hack by extending the arguments to long
 * double, however this is not enough to always get correct results as you would
 * need around 512 fraction bits to cover all cases.
 */
static double
two_raised_minus_1(double f)
{
	return (double)(exp2l((long double)f) - 1.0L);
}

static long double
two_raised_minus_1l(long double f)
{
	return exp2l(f) - 1.0L;
}

/* fix overflow in the result */
#define TWO_RAISED_MINUS_ONE_RESULT_FIXER_MACRO(arg, res)                      \
	(isinf(res) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(2_raised_minus_1, two_raised_minus_1,
                               TWO_RAISED_MINUS_ONE_RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(2_raised_minus_1, two_raised_minus_1,
                                   TWO_RAISED_MINUS_ONE_RESULT_FIXER_MACRO)
