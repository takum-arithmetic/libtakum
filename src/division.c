/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

/* no need to fix the result */
#define RESULT_FIXER_MACRO(a, b, res) (res)

static double
division(double a, double b)
{
	return a / b;
}

static long double
divisionl(long double a, long double b)
{
	return a / b;
}

UTIL_BINARY_FLOAT_TAKUM_WRAPPER(division, division, RESULT_FIXER_MACRO)

/*
 * As codec_takum_log*_to_l() returns -Inf for 0 and
 * NaN for NaR both cases are conveniently covered
 * without special checks as a - (-Inf) = Inf, which
 * is interpreted as NaR, for regular a and
 * a = -Inf, and a - NaN = NaN in all cases.
 */
takum_log8
takum_log8_division(takum_log8 a, takum_log8 b)
{
	return codec_takum_log8_from_s_and_l((a > 0) != (b > 0),
	                                     codec_takum_log8_to_l(a) -
	                                             codec_takum_log8_to_l(b));
}

takum_log16
takum_log16_division(takum_log16 a, takum_log16 b)
{
	return codec_takum_log16_from_s_and_l(
		(a > 0) != (b > 0),
		codec_takum_log16_to_l(a) - codec_takum_log16_to_l(b));
}

takum_log32
takum_log32_division(takum_log32 a, takum_log32 b)
{
	return codec_takum_log32_from_s_and_l(
		(a > 0) != (b > 0),
		codec_takum_log32_to_l(a) - codec_takum_log32_to_l(b));
}

takum_log64
takum_log64_division(takum_log64 a, takum_log64 b)
{
	return codec_takum_log64_from_s_and_l(
		(a > 0) != (b > 0),
		codec_takum_log64_to_l(a) - codec_takum_log64_to_l(b));
}
