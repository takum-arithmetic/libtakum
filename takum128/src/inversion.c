/* See LICENSE file for copyright and license details. */
#include <mpfr.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/* no need to fix the result, as inv(0)=inf yields NaR without our doing */
takum128
takum128_inversion(takum128 t)
{
	mpfr_t l, v, res, out_l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, l, v, res, out_l, (mpfr_ptr)0);

	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(v, t < 0, l);
	mpfr_ui_div(res, 1, v, MPFR_RNDN);

	codec128_linear_l_from_value(out_l, res);
	result = codec128_log_from_s_and_l(mpfr_sgn(res) < 0, out_l);

	mpfr_clears(l, v, res, out_l, (mpfr_ptr)0);

	return result;
}

/*
 * Direct 128-bit transcription of ../../src/inversion.c's takum_log*
 * case: inversion negates l, but the encoding isn't plain sign-magnitude,
 * so it's implemented as "flip everything but the sign bit, then add 1"
 * rather than arithmetic negation -- exactly like the smaller widths.
 */
takum_log128
takum_log128_inversion(takum_log128 t)
{
	union util_takum128_union out = {
		.value = t,
	};

	out.bits = (out.bits ^
	            (unsigned __int128)~(((unsigned __int128)1) << 127)) +
	           1;

	return (t == TAKUM_LOG128_NAR) ? TAKUM_LOG128_NAR : out.value;
}
