/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_BINARY_WRAPPER(arctan2, mpfr_atan2)
TAKUM128_BINARY_WRAPPER(arctan2_over_pi, mpfr_atan2pi)
