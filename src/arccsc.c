/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
arccscl(long double f)
{
	return asinl(1.0l / f);
}

static double
arccsc(double f)
{
	return (double)arccscl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arccsc, arccsc, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arccsc, arccsc, RESULT_FIXER_MACRO)

long double
arccsc_over_pil(long double f)
{
	return asinl(1.0l / f) / PI;
}

double
arccsc_over_pi(double f)
{
	return (double)arccsc_over_pil((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arccsc_over_pi, arccsc_over_pi,
                               RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arccsc_over_pi, arccsc_over_pi,
                                   RESULT_FIXER_MACRO)
