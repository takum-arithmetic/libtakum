/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(lg, mpfr_log10)
/* mpfr_log10p1 computes lg(1+x) directly, more accurately than the
 * multiply-by-constant lg(e)*log1p(x) approach ../../src/lg.c uses. */
TAKUM128_UNARY_WRAPPER(lg_1_plus, mpfr_log10p1)
