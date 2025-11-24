/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/*
 * near the poles, the results of sec() never overflow. Thus any infinity
 * returned by sec() is a 'true' infinity.
 */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
secl(long double f)
{
	return 1.0l / cosl(f);
}

static double
sec(double f)
{
	return (double)secl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(sec, sec, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(sec, sec, RESULT_FIXER_MACRO)

static long double
sec_pi_timesl(long double f)
{
	long double f_mod_2;

	f_mod_2 = fmodl(f, 2.0l);

	if (f_mod_2 == 0.0l) {
		return 1.0l;
	} else if (f_mod_2 == 0.5l) {
		return NAN;
	} else if (f_mod_2 == 1.0l) {
		return -1.0l;
	} else if (f_mod_2 == 1.5l) {
		return NAN;
	} else {
		return secl(PI * f);
	}
}

static double
sec_pi_times(double f)
{
	return (double)sec_pi_timesl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(sec_pi_times, sec_pi_times, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(sec_pi_times, sec_pi_times,
                                   RESULT_FIXER_MACRO)
