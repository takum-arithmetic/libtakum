/* See LICENSE file for copyright and license details. */
#include <float.h>
#define log101p   _log101p
#define log1010pl _log101pl
#include <math.h>
#undef log101p
#undef log101pl

#include "util.h"

/*
 * no need to fix the result for negative infinity (zero argument), as
 * it is a 'true' infinity, but we fix the overflow to positive infinity
 */
#define RESULT_FIXER_MACRO(arg, res)                                           \
	((isinf(res) && (res) > 0.0) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(lg, log10, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(lg, log10, RESULT_FIXER_MACRO)

static long double
lg_1_plusl(long double f)
{
	return LG_E * log1pl(f);
}

static double
lg_1_plus(double f)
{
	return (double)lg_1_plusl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(lg_1_plus, lg_1_plus, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(lg_1_plus, lg_1_plus, RESULT_FIXER_MACRO)
