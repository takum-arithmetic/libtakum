/* See LICENSE file for copyright and license details. */
#include <math.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

/*
 * As codec_takum*_to_l() returns -Inf for 0 and
 * NaN for NaR both cases are conveniently covered
 * without special checks as a + (-Inf) = -Inf
 * for regular a and a = -Inf, and a + NaN = NaN in
 * all cases.
 */
takum8
takum8_multiplication(takum8 a, takum8 b)
{
	return codec_takum8_from_s_and_l((a > 0) != (b > 0),
	                                 codec_takum8_to_l(a) +
	                                         codec_takum8_to_l(b));
}

takum16
takum16_multiplication(takum16 a, takum16 b)
{
	return codec_takum16_from_s_and_l((a > 0) != (b > 0),
	                                  codec_takum16_to_l(a) +
	                                          codec_takum16_to_l(b));
}

takum32
takum32_multiplication(takum32 a, takum32 b)
{
	return codec_takum32_from_s_and_l((a > 0) != (b > 0),
	                                  codec_takum32_to_l(a) +
	                                          codec_takum32_to_l(b));
}

takum64
takum64_multiplication(takum64 a, takum64 b)
{
	return codec_takum64_from_s_and_l((a > 0) != (b > 0),
	                                  codec_takum64_to_l(a) +
	                                          codec_takum64_to_l(b));
}

/* no need to fix the result */
#define RESULT_FIXER_MACRO(a, b, res) (res)

static double
multiplication(double a, double b)
{
	return a * b;
}

static long double
multiplicationl(long double a, long double b)
{
	return a * b;
}

UTIL_BINARY_FLOAT_TAKUM_LINEAR_WRAPPER(multiplication, multiplication,
                                       RESULT_FIXER_MACRO)
