/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/* no need to fix the result, as we do not overflow near the poles */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
arcothl(long double f)
{
	return atanh(1.0l / f);
}

static double
arcoth(double f)
{
	return (double)arcothl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arcoth, arcoth, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arcoth, arcoth, RESULT_FIXER_MACRO)
