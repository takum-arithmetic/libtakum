/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/*
 * near the pole in 0, the results of csc() never overflow. Thus any infinity
 * returned by csc() is a 'true' infinity.
 */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
cscl(long double f)
{
	return 1.0l / sinl(f);
}

static double
csc(double f)
{
	return (double)cscl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(csc, csc, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(csc, csc, RESULT_FIXER_MACRO)

static long double
csc_pi_timesl(long double f)
{
	long double f_mod_2;

	f_mod_2 = fmodl(f, 2.0l);

	if (f_mod_2 == 0.0l) {
		return NAN;
	} else if (f_mod_2 == 0.5l) {
		return 1.0l;
	} else if (f_mod_2 == 1.0l) {
		return NAN;
	} else if (f_mod_2 == 1.5l) {
		return -1.0l;
	} else {
		return cscl(PI * f);
	}
}

static double
csc_pi_times(double f)
{
	return (double)csc_pi_timesl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(csc_pi_times, csc_pi_times, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(csc_pi_times, csc_pi_times,
                                   RESULT_FIXER_MACRO)
