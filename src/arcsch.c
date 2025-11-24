/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/* no need to fix the result, as we do not overflow near the poles */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
arcschl(long double f)
{
	return asinh(1.0l / f);
}

static double
arcsch(double f)
{
	return (double)arcschl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arcsch, arcsch, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arcsch, arcsch, RESULT_FIXER_MACRO)
