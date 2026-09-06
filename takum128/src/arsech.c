/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/* MPFR has no mpfr_asech; compose it as acosh(1/f), as
 * ../../src/arsech.c does. */
static int
mpfr_asech(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_acosh(rop, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(arsech, mpfr_asech)
