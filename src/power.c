/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>

#include "util.h"

/*
 * fix underflow (which is the case when the argument is non-zero but the
 * result is zero) and overflow
 */
#define RESULT_FIXER_MACRO(a, b, res)                                          \
	(((res) == 0.0) ? (a == 0.0)   ? 0.0 :                                 \
	                  signbit(res) ? -DBL_MIN :                            \
	                                 DBL_MIN :                             \
	 isinf(res)     ? (a == 0.0)   ? NAN :                                 \
	                  signbit(res) ? -DBL_MAX :                            \
	                                 DBL_MAX :                             \
	                  (res))

UTIL_BINARY_FLOAT_TAKUM_WRAPPER(power, pow, RESULT_FIXER_MACRO)
UTIL_BINARY_FLOAT_TAKUM_LOG_WRAPPER(power, pow, RESULT_FIXER_MACRO)
