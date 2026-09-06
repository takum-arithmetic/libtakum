/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(cos, mpfr_cos)
/* See sin.c: mpfr_cospi needs no hand-written pole special-casing. */
TAKUM128_UNARY_WRAPPER(cos_pi_times, mpfr_cospi)
