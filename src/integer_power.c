/* See LICENSE file for copyright and license details. */
#include <float.h>
#include <math.h>
#include <stdint.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

/*
 * The case NaR is automatically covered given NaN*n=NaN holds for any n.
 *
 * We use a 64 bit integer for powers as even the largest positive l
 * (which is close to 255) multiplied with the largest signed 64 bit
 * integer (2^63-1) is still within the dynamic range of float32, let
 * alone float64, which means that there will never be overflows
 * in terms of l. Of course the final takum representation may saturate
 * in the process.
 * Using different integer types for each takum bit string length would
 * serve no purpose other than to complicate the API. We allow signed n
 * as there is no reason not to.
 */
takum8
takum8_integer_power(takum8 t, int64_t n)
{
	if (t == 0 && n <= 0) {
		return TAKUM8_NAR;
	} else {
		return codec_takum8_from_s_and_l((t < 0 && n % 2 != 0),
		                                 codec_takum8_to_l(t) * n);
	}
}

takum16
takum16_integer_power(takum16 t, int64_t n)
{
	if (t == 0 && n <= 0) {
		return TAKUM16_NAR;
	} else {
		return codec_takum16_from_s_and_l((t < 0 && n % 2 != 0),
		                                  codec_takum16_to_l(t) * n);
	}
}

takum32
takum32_integer_power(takum32 t, int64_t n)
{
	if (t == 0 && n <= 0) {
		return TAKUM32_NAR;
	} else {
		return codec_takum32_from_s_and_l((t < 0 && n % 2 != 0),
		                                  codec_takum32_to_l(t) * n);
	}
}

/*
 * We use long double in all cases to really max out the integral
 * representation power of floats
 */
takum64
takum64_integer_power(takum64 t, int64_t n)
{
	long double f, res;

	if (t == TAKUM64_NAR || (t == 0 && n <= 0)) {
		return TAKUM64_NAR;
	}

	f = takum64_to_extended_float(t);
	res = powl(f, (long double)n);

	if (isinf(res)) {
		res = (res > 0.0) ? DBL_MAX : -DBL_MAX;
	} else if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum64_from_extended_float(res);
}

takum_linear8
takum_linear8_integer_power(takum_linear8 t, int64_t n)
{
	long double f, res;

	if (t == TAKUM_LINEAR8_NAR || (t == 0 && n <= 0)) {
		return TAKUM_LINEAR8_NAR;
	}

	f = takum_linear8_to_extended_float(t);
	res = powl(f, (long double)n);

	if (isinf(res)) {
		res = (res > 0.0) ? DBL_MAX : -DBL_MAX;
	} else if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum_linear8_from_extended_float(res);
}

takum_linear16
takum_linear16_integer_power(takum_linear16 t, int64_t n)
{
	long double f, res;

	if (t == TAKUM_LINEAR16_NAR || (t == 0 && n <= 0)) {
		return TAKUM_LINEAR16_NAR;
	}

	f = takum_linear16_to_extended_float(t);
	res = powl(f, (long double)n);

	if (isinf(res)) {
		res = (res > 0.0) ? DBL_MAX : -DBL_MAX;
	} else if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum_linear16_from_extended_float(res);
}

takum_linear32
takum_linear32_integer_power(takum_linear32 t, int64_t n)
{
	long double f, res;

	if (t == TAKUM_LINEAR32_NAR || (t == 0 && n <= 0)) {
		return TAKUM_LINEAR32_NAR;
	}

	f = takum_linear32_to_extended_float(t);
	res = powl(f, (long double)n);

	if (isinf(res)) {
		res = (res > 0.0) ? DBL_MAX : -DBL_MAX;
	} else if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum_linear32_from_extended_float(res);
}

takum_linear64
takum_linear64_integer_power(takum_linear64 t, int64_t n)
{
	long double f, res;

	if (t == TAKUM_LINEAR64_NAR || (t == 0 && n <= 0)) {
		return TAKUM_LINEAR64_NAR;
	}

	f = takum_linear64_to_extended_float(t);
	res = powl(f, (long double)n);

	if (isinf(res)) {
		res = (res > 0.0) ? DBL_MAX : -DBL_MAX;
	} else if (res == 0.0l && t != 0) {
		res = (t < 0 && n % 2 != 0) ? -DBL_MIN : DBL_MIN;
	}

	return takum_linear64_from_extended_float(res);
}
