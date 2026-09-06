/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/* MPFR has no mpfr_acsc; compose it as asin(1/f), as ../../src/arccsc.c
 * does. */
static int
mpfr_acsc(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_asin(rop, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(arccsc, mpfr_acsc)

static int
mpfr_acscpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_asinpi(rop, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(arccsc_over_pi, mpfr_acscpi)
