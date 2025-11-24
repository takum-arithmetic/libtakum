/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
arccotl(long double f)
{
	if (f >= 0.0) {
		return atanl(1.0l / f);
	} else {
		return atanl(1.0l / f) + PI;
	}
}

static double
arccot(double f)
{
	return (double)arccotl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arccot, arccot, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arccot, arccot, RESULT_FIXER_MACRO)

long double
arccot_over_pil(long double f)
{
	if (f >= 0.0) {
		return atanl(1.0l / f) / PI;
	} else {
		return atanl(1.0l / f) / PI + 1.0l;
	}
}

double
arccot_over_pi(double f)
{
	return (double)arccot_over_pil((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arccot_over_pi, arccot_over_pi,
                               RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arccot_over_pi, arccot_over_pi,
                                   RESULT_FIXER_MACRO)
