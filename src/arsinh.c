/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/* fix overflow in the result */
#define RESULT_FIXER_MACRO(arg, res)                                           \
	(isinf(res) ? ((res) >= 0.0) ? DBL_MAX : -DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(arsinh, asinh, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(arsinh, asinh, RESULT_FIXER_MACRO)
