/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/* fix overflow in the result */
#define RESULT_FIXER_MACRO(a, b, res) (isinf(res) ? DBL_MAX : (res))

UTIL_BINARY_FLOAT_TAKUM_WRAPPER(hypotenuse, hypot, RESULT_FIXER_MACRO)
UTIL_BINARY_FLOAT_TAKUM_LOG_WRAPPER(hypotenuse, hypot, RESULT_FIXER_MACRO)
