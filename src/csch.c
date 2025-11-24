/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

#include "../takum.h"

/*
 * near the pole in 0, the results of csc() never overflow. Thus any infinity
 * returned by csc() is a 'true' infinity. However, even float64 underflows to
 * zero from below.
 */
#define RESULT_FIXER_MACRO(arg, res)                                           \
	((res == 0.0) ? (arg < 0) ? -DBL_MIN : DBL_MIN : (res))

static long double
cschl(long double f)
{
	return 1.0l / sinhl(f);
}

static double
csch(double f)
{
	return (double)cschl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(csch, csch, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(csch, csch, RESULT_FIXER_MACRO)
