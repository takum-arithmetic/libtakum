/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arctan, atan, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arctan, atan, RESULT_FIXER_MACRO)

/*
 * We extend to long double and multiply the argument with pi, returning a
 * rounded long double. arctanpil() is still good enough as we have at least 5
 * bits of wiggle room anyway.
 */
static double
arctanpi(double f)
{
	return (double)(atanl((long double)f) / PI);
}

static long double
arctanpil(long double f)
{
	return atanl(f) / PI;
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arctan_over_pi, arctanpi, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arctan_over_pi, arctanpi, RESULT_FIXER_MACRO)
