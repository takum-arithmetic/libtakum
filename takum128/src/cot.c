/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

TAKUM128_UNARY_WRAPPER(cot, mpfr_cot)

/*
 * MPFR has no mpfr_cotpi; compose it as the reciprocal of mpfr_tanpi
 * (which, unlike a hand-multiplied pi*x, is exact at the poles -- see
 * sin.c -- so 1/tanpi(x) naturally overflows to infinity there, which
 * the standard codec128 encode path already turns into NaR, matching
 * ../../src/cot.c's explicit NaN-at-the-poles behaviour).
 */
static int
mpfr_cotpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_tanpi(rop, op, rnd);
	mpfr_ui_div(rop, 1, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(cot_pi_times, mpfr_cotpi)
