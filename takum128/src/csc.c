/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(csc, mpfr_csc)

/* See cot.c: composed as the reciprocal of the exact-at-the-poles
 * mpfr_sinpi, needing no hand-written pole special-casing. */
static int
mpfr_cscpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_sinpi(rop, op, rnd);
	mpfr_ui_div(rop, 1, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(csc_pi_times, mpfr_cscpi)
