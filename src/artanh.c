/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "util.h"

/* no need to fix the result, as infinities for +-1 are 'true' infinities */
#define RESULT_FIXER_MACRO(arg, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(artanh, atanh, RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(artanh, atanh, RESULT_FIXER_MACRO)
