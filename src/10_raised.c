/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/*
 * Define exp10 using pow
 */
static double
ten_raised(double f)
{
	return (double)powl(10.0L, (long double)f);
}

static long double
ten_raisedl(long double f)
{
	return powl(10.0L, f);
}

/* fix under- and overflow in the result */
#define TEN_RAISED_RESULT_FIXER_MACRO(arg, res)                                \
	(((res) == 0.0) ? DBL_MIN : isinf(res) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(10_raised, ten_raised,
                               TEN_RAISED_RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(10_raised, ten_raised,
                                   TEN_RAISED_RESULT_FIXER_MACRO)

/*
 * This implementation is a bit of a hack by extending the arguments to long
 * double, however this is not enough to always get correct results as you would
 * need around 512 fraction bits to cover all cases.
 */
static double
ten_raised_minus_1(double f)
{
	return (double)(powl(10.0L, (long double)f) - 1.0L);
}

static long double
ten_raised_minus_1l(long double f)
{
	return powl(10.0L, f) - 1.0L;
}

/* fix overflow in the result */
#define TEN_RAISED_MINUS_ONE_RESULT_FIXER_MACRO(arg, res)                      \
	(isinf(res) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(10_raised_minus_1, ten_raised_minus_1,
                               TEN_RAISED_MINUS_ONE_RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(10_raised_minus_1, ten_raised_minus_1,
                                   TEN_RAISED_MINUS_ONE_RESULT_FIXER_MACRO)
