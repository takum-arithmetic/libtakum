/* See LICENSE file for copyright and license details. */
#define cospi  _cospi
#define cospil _cospil
#include <math.h>
#undef cospi
#undef cospil

#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(cos, cos, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(cos, cos, RESULT_FIXER_MACRO)

/*
 * We extend to long double and multiply the argument with pi, returning a
 * rounded long double. cospil() is still good enough as we have at least 5 bits
 * of wiggle room anyway.
 */
static long double
cospil(long double f)
{
	long double f_mod_2;

	f_mod_2 = fmodl(f, 2.0l);

	if (f_mod_2 == 0.0l) {
		return 1.0l;
	} else if (f_mod_2 == 0.5l) {
		return 0.0l;
	} else if (f_mod_2 == 1.0l) {
		return -1.0l;
	} else if (f_mod_2 == 1.5l) {
		return 0.0l;
	} else {
		return cosl(PI * f);
	}
}

static double
cospi(double f)
{
	return (double)cospil((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(cos_pi_times, cospi, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(cos_pi_times, cospi, RESULT_FIXER_MACRO)
