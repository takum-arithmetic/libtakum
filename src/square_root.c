/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(f, res) (res)

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(square_root, sqrt, RESULT_FIXER_MACRO)

/*
 * The case NaR is automatically covered given
 * NaN/2=NaN holds.
 */
takum_log8
takum_log8_square_root(takum_log8 t)
{
	if (t < 0) {
		return TAKUM_LOG8_NAR;
	} else {
		return codec_takum_log8_from_s_and_l(
			0, ldexpf(codec_takum_log8_to_l(t), -1));
	}
}

takum_log16
takum_log16_square_root(takum_log16 t)
{
	if (t < 0) {
		return TAKUM_LOG16_NAR;
	} else {
		return codec_takum_log16_from_s_and_l(
			0, ldexpf(codec_takum_log16_to_l(t), -1));
	}
}

takum_log32
takum_log32_square_root(takum_log32 t)
{
	if (t < 0) {
		return TAKUM_LOG32_NAR;
	} else {
		return codec_takum_log32_from_s_and_l(
			0, ldexp(codec_takum_log32_to_l(t), -1));
	}
}

takum_log64
takum_log64_square_root(takum_log64 t)
{
	if (t < 0) {
		return TAKUM_LOG64_NAR;
	} else {
		return codec_takum_log64_from_s_and_l(
			0, ldexpl(codec_takum_log64_to_l(t), -1));
	}
}
