/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(arccos, mpfr_acos)
TAKUM128_UNARY_WRAPPER(arccos_over_pi, mpfr_acospi)
