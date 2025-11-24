/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

#include "../takum.h"

/* no need to fix the result, as we do not overflow near the poles */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
arcsecl(long double f)
{
	return acosl(1.0l / f);
}

static double
arcsec(double f)
{
	return (double)arcsecl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arcsec, arcsec, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arcsec, arcsec, RESULT_FIXER_MACRO)

static long double
arcsec_over_pil(long double f)
{
	return acosl(1.0l / f) / PI;
}

static double
arcsec_over_pi(double f)
{
	return (double)arcsec_over_pil((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arcsec_over_pi, arcsec_over_pi,
                               RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arcsec_over_pi, arcsec_over_pi,
                                   RESULT_FIXER_MACRO)
