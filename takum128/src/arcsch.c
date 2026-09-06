/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/* MPFR has no mpfr_acsch; compose it as asinh(1/f), as
 * ../../src/arcsch.c does. */
static int
mpfr_acsch(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_asinh(rop, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(arcsch, mpfr_acsch)
