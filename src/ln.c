/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/*
 * no need to fix the result for negative infinity (zero argument), as
 * it is a 'true' infinity, but we fix the overflow to positive infinity
 */
#define RESULT_FIXER_MACRO(arg, res)                                           \
	((isinf(res) && (res) > 0.0) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(ln, log, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(ln, log, RESULT_FIXER_MACRO)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(ln_1_plus, log1p, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(ln_1_plus, log1p, RESULT_FIXER_MACRO)
