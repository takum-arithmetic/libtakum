/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>
#include <stdint.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

takum8
takum8_root(takum8 t, int64_t n)
{
	long double f, res;

	if (n == 0 || (t < 0 && n % 2 == 0)) {
		return TAKUM8_NAR;
	}

	f = takum8_to_extended_float(t);
	res = powl(f, 1.0l / (long double)n);

	if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum8_from_extended_float(res);
}

takum16
takum16_root(takum16 t, int64_t n)
{
	long double f, res;

	if (n == 0 || (t < 0 && n % 2 == 0)) {
		return TAKUM16_NAR;
	}

	f = takum16_to_extended_float(t);
	res = powl(f, 1.0l / (long double)n);

	if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum16_from_extended_float(res);
}

takum32
takum32_root(takum32 t, int64_t n)
{
	long double f, res;

	if (n == 0 || (t < 0 && n % 2 == 0)) {
		return TAKUM32_NAR;
	}

	f = takum32_to_extended_float(t);
	res = powl(f, 1.0l / (long double)n);

	if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum32_from_extended_float(res);
}

takum64
takum64_root(takum64 t, int64_t n)
{
	long double f, res;

	if (n == 0 || (t < 0 && n % 2 == 0)) {
		return TAKUM64_NAR;
	}

	f = takum64_to_extended_float(t);
	res = powl(f, 1.0l / (long double)n);

	if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum64_from_extended_float(res);
}

/*
 * The case NaR is automatically covered given NaN/n=NaN holds for any n.
 *
 * We use a 64 bit integer as a possible base root as even the smallest
 * positive l (which is 2^(-n+5)) divided by the largest signed 64
 * bit integer (2^63-1) is still within the dynamic range of float32,
 * let alone float64, which means that there will never be underflows
 * in terms of l. Of course the final takum representation may underflow
 * to 1.0 in the process.
 * Using different integer types for each takum bit string length would
 * serve no purpose other than to complicate the API. We allow signed n
 * as there is no reason not to.
 */
takum_log8
takum_log8_root(takum_log8 t, int64_t n)
{
	if (n == 0 || (t < 0 && n % 2 == 0) || (t == 0 && n < 0)) {
		return TAKUM_LOG8_NAR;
	} else {
		return codec_takum_log8_from_s_and_l(
			(t < 0), codec_takum_log8_to_l(t) / n);
	}
}

takum_log16
takum_log16_root(takum_log16 t, int64_t n)
{
	if (n == 0 || (t < 0 && n % 2 == 0) || (t == 0 && n < 0)) {
		return TAKUM_LOG16_NAR;
	} else {
		return codec_takum_log16_from_s_and_l(
			(t < 0), codec_takum_log16_to_l(t) / n);
	}
}

takum_log32
takum_log32_root(takum_log32 t, int64_t n)
{
	if (n == 0 || (t < 0 && n % 2 == 0) || (t == 0 && n < 0)) {
		return TAKUM_LOG32_NAR;
	} else {
		return codec_takum_log32_from_s_and_l(
			(t < 0), codec_takum_log32_to_l(t) / n);
	}
}

takum_log64
takum_log64_root(takum_log64 t, int64_t n)
{
	if (n == 0 || (t < 0 && n % 2 == 0) || (t == 0 && n < 0)) {
		return TAKUM_LOG64_NAR;
	} else {
		return codec_takum_log64_from_s_and_l(
			(t < 0), codec_takum_log64_to_l(t) / n);
	}
}
