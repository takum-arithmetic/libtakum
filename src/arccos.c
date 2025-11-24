/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arccos, acos, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arccos, acos, RESULT_FIXER_MACRO)

/*
 * We extend to long double and multiply the argument with pi, returning a
 * rounded long double. arccospil() is still good enough as we have at least 5
 * bits of wiggle room anyway.
 */
static double
arccospi(double f)
{
	return (double)(acosl((long double)f) / PI);
}

static long double
arccospil(long double f)
{
	return acosl(f) / PI;
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arccos_over_pi, arccospi, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arccos_over_pi, arccospi, RESULT_FIXER_MACRO)
