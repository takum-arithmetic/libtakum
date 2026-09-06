/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/*
 * MPFR has no mpfr_acot; compose it as atan(1/f), with the same
 * quadrant correction ../../src/arccot.c's arccotl() applies for
 * negative f (atan alone only ever returns a value in (-pi/2, pi/2),
 * but arccot's conventional range is (0, pi)).
 */
static int
mpfr_acot(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_t pi;
	int negative = mpfr_sgn(op) < 0;

	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_atan(rop, rop, rnd);
	if (negative) {
		mpfr_init2(pi, mpfr_get_prec(rop));
		mpfr_const_pi(pi, rnd);
		mpfr_add(rop, rop, pi, rnd);
		mpfr_clear(pi);
	}

	return 0;
}

TAKUM128_UNARY_WRAPPER(arccot, mpfr_acot)

/* Same quadrant correction, but composed from mpfr_atanpi (atan(x)/pi)
 * so the "+pi" correction above becomes "+1" instead. */
static int
mpfr_acotpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	int negative = mpfr_sgn(op) < 0;

	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_atanpi(rop, rop, rnd);
	if (negative) {
		mpfr_add_ui(rop, rop, 1, rnd);
	}

	return 0;
}

TAKUM128_UNARY_WRAPPER(arccot_over_pi, mpfr_acotpi)
