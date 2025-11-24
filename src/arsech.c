/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
arsechl(long double f)
{
	return acoshl(1.0l / f);
}

static double
arsech(double f)
{
	return (double)arsechl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arsech, arsech, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arsech, arsech, RESULT_FIXER_MACRO)
