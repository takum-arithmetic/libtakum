/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/* MPFR has no mpfr_acoth; compose it as atanh(1/f), as
 * ../../src/arcoth.c does. */
static int
mpfr_acoth(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_atanh(rop, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(arcoth, mpfr_acoth)
