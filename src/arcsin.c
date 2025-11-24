/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arcsin, asin, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arcsin, asin, RESULT_FIXER_MACRO)

/*
 * We extend to long double and multiply the argument with pi, returning a
 * rounded long double. arcsinpil() is still good enough as we have at least 5
 * bits of wiggle room anyway.
 */
static long double
arcsin_over_pil(long double f)
{
	return asinl(f) / PI;
}

static double
arcsin_over_pi(double f)
{
	return (double)arcsin_over_pil((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arcsin_over_pi, arcsin_over_pi,
                               RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arcsin_over_pi, arcsin_over_pi,
                                   RESULT_FIXER_MACRO)
