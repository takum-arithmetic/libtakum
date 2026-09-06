/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(tan, mpfr_tan)
/* See sin.c: mpfr_tanpi needs no hand-written pole special-casing --
 * an exact half-integer in correctly produces an infinity out, which
 * the standard codec128 encode path already turns into NaR. */
TAKUM128_UNARY_WRAPPER(tan_pi_times, mpfr_tanpi)
