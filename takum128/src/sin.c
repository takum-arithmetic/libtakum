/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(sin, mpfr_sin)
/* mpfr_sinpi computes sin(pi*x) directly (correctly rounded, exact at
 * rational multiples of a half-turn), so unlike ../../src/sin.c's
 * sinpil() there's no need to special-case the poles by hand -- an
 * exact zero/one in, an exact zero/one (or the correctly rounded
 * neighbourhood of one) out. */
TAKUM128_UNARY_WRAPPER(sin_pi_times, mpfr_sinpi)
