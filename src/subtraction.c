/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(a, b, res) (res)

static double
subtraction(double a, double b)
{
	return a - b;
}

static long double
subtractionl(long double a, long double b)
{
	return a - b;
}

UTIL_BINARY_FLOAT_TAKUM_WRAPPER(subtraction, subtraction, RESULT_FIXER_MACRO)
UTIL_BINARY_FLOAT_TAKUM_LOG_WRAPPER(subtraction, subtraction,
                                    RESULT_FIXER_MACRO)
