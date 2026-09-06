/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(sec, mpfr_sec)

/* See cot.c: composed as the reciprocal of the exact-at-the-poles
 * mpfr_cospi, needing no hand-written pole special-casing. */
static int
mpfr_secpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_cospi(rop, op, rnd);
	mpfr_ui_div(rop, 1, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(sec_pi_times, mpfr_secpi)
