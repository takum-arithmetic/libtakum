/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(10_raised, mpfr_exp10)
/* mpfr_exp10m1 computes 10^x-1 directly, avoiding the catastrophic
 * cancellation ../../src/10_raised.c's hack around exp2l/-1.0L (its
 * exact analogue for base 10) explicitly warns about for small x. */
TAKUM128_UNARY_WRAPPER(10_raised_minus_1, mpfr_exp10m1)
