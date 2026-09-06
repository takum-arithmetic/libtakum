/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(arctan, mpfr_atan)
TAKUM128_UNARY_WRAPPER(arctan_over_pi, mpfr_atanpi)
