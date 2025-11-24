/* See LICENSE file for copyright and license details. */
#define sinpi  _sinpi
#define sinpil _sinpil
#include <math.h>
#undef sinpi
#undef sinpil

#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(sin, sin, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(sin, sin, RESULT_FIXER_MACRO)

/*
 * We extend to long double and multiply the argument with pi, returning a
 * rounded long double. sinpil() is still good enough as we have at least 5 bits
 * of wiggle room anyway.
 */
static long double
sinpil(long double f)
{
	long double f_mod_2;

	f_mod_2 = fmodl(f, 2.0l);

	if (f_mod_2 == 0.0l) {
		return 0.0l;
	} else if (f_mod_2 == 0.5l) {
		return 1.0l;
	} else if (f_mod_2 == 1.0l) {
		return 0.0l;
	} else if (f_mod_2 == 1.5l) {
		return -1.0l;
	} else {
		return sinl(PI * f);
	}
}

static double
sinpi(double f)
{
	return (double)sinpil((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(sin_pi_times, sinpi, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(sin_pi_times, sinpi, RESULT_FIXER_MACRO)
