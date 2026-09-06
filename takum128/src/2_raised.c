/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(2_raised, mpfr_exp2)
/* mpfr_exp2m1 computes 2^x-1 directly, avoiding the catastrophic
 * cancellation ../../src/2_raised.c's exp2l(f)-1.0L hack explicitly
 * warns about for small x. */
TAKUM128_UNARY_WRAPPER(2_raised_minus_1, mpfr_exp2m1)
