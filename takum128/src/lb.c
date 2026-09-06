/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(lb, mpfr_log2)
/* mpfr_log2p1 computes lb(1+x) directly, more accurately than the
 * multiply-by-constant lb(e)*log1p(x) approach ../../src/lb.c uses. */
TAKUM128_UNARY_WRAPPER(lb_1_plus, mpfr_log2p1)
