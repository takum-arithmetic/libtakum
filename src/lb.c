/* See LICENSE file for copyright and license details. */
#include <float.h>
#define log21p  _log21p
#define log21pl _log21pl
#include <math.h>
#undef log21p
#undef log21pl

#include "util.h"

/*
 * no need to fix the result for negative infinity (zero argument), as
 * it is a 'true' infinity, but we fix the overflow to positive infinity
 */
#define RESULT_FIXER_MACRO(arg, res)                                           \
	((isinf(res) && (res) > 0.0) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(lb, log2, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(lb, log2, RESULT_FIXER_MACRO)

static long double
lb_1_plusl(long double f)
{
	return LB_E * log1pl(f);
}

static double
lb_1_plus(double f)
{
	return (double)lb_1_plusl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(lb_1_plus, lb_1_plus, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(lb_1_plus, lb_1_plus, RESULT_FIXER_MACRO)
