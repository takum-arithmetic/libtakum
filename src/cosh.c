/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/* fix overflow in the result */
#define RESULT_FIXER_MACRO(arg, res) (isinf(res) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(cosh, cosh, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(cosh, cosh, RESULT_FIXER_MACRO)
