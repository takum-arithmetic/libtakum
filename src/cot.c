/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/* no need to fix the result, as we do not overflow near the poles */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
cotl(long double f)
{
	return 1.0l / tanl(f);
}

static double
cot(double f)
{
	return (double)cotl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(cot, cot, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(cot, cot, RESULT_FIXER_MACRO)

static long double
cot_pi_timesl(long double f)
{
	long double f_mod_1;

	f_mod_1 = fmodl(f, 1.0l);

	if (f_mod_1 == 0.0l) {
		return NAN;
	} else if (f_mod_1 == 0.5) {
		return 0.0;
	} else {
		return cotl(PI * f);
	}
}

static double
cot_pi_times(double f)
{
	return (double)cot_pi_timesl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(cot_pi_times, cot_pi_times, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(cot_pi_times, cot_pi_times,
                                   RESULT_FIXER_MACRO)
