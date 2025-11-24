/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/* fix under- and overflow in the result */
#define EXP_RESULT_FIXER_MACRO(arg, res)                                       \
	(((res) == 0.0) ? DBL_MIN : isinf(res) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(exp, exp, EXP_RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(exp, exp, EXP_RESULT_FIXER_MACRO)

/* fix overflow in the result */
#define EXP_MINUS_ONE_RESULT_FIXER_MACRO(arg, res)                             \
	(isinf(res) ? DBL_MAX : (res))

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(exp_minus_1, expm1,
                               EXP_MINUS_ONE_RESULT_FIXER_MACRO)
UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER(exp_minus_1, expm1,
                                   EXP_MINUS_ONE_RESULT_FIXER_MACRO)
