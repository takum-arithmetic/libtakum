/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/* MPFR has no mpfr_asec; compose it as acos(1/f), as ../../src/arcsec.c
 * does (no quadrant correction is needed, unlike arccot). */
static int
mpfr_asec(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_acos(rop, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(arcsec, mpfr_asec)

static int
mpfr_asecpi(mpfr_ptr rop, mpfr_srcptr op, mpfr_rnd_t rnd)
{
	mpfr_ui_div(rop, 1, op, rnd);
	mpfr_acospi(rop, rop, rnd);

	return 0;
}

TAKUM128_UNARY_WRAPPER(arcsec_over_pi, mpfr_asecpi)
