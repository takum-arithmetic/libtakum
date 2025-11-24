/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

#include "../takum.h"

/* even float64 underflows to zero from above */
#define RESULT_FIXER_MACRO(arg, res) ((res == 0.0) ? DBL_MIN : (res))

static double
sech(double f)
{
	return 1.0 / cosh(f);
}

static long double
sechl(long double f)
{
	return 1.0l / coshl(f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(sech, sech, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(sech, sech, RESULT_FIXER_MACRO)
