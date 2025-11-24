/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(arg, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(tanh, tanh, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(tanh, tanh, RESULT_FIXER_MACRO)
