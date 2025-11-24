/* See LICENSE file for copyright and license details. */
#include <math.h>
#include <stdbool.h>

#include "../takum.h"

#include "codec.h"
#include "util.h"

/* Takum conversion helper macros */
#define TAKUM_INTERNAL_CONVERT_EXPAND(FROM, TO)                                \
	do {                                                                   \
		const union util_takum##FROM##_union in = {                    \
			.value = t,                                            \
		};                                                             \
		union util_takum##TO##_union out = {                           \
			.bits = ((uint##TO##_t)in.bits) << (TO - FROM),        \
		};                                                             \
                                                                               \
		return out.value;                                              \
	} while (0);

#define TAKUM_INTERNAL_CONVERT_REDUCE(FROM, TO)                                \
	do {                                                                   \
		const union util_takum##FROM##_union in = {                    \
			.value = t,                                            \
		};                                                             \
		union util_takum##TO##_union out;                              \
                                                                               \
		out.bits = (uint##TO##_t)                                      \
			util_round_uint##FROM##_to_number_of_bits(in.bits,     \
		                                                  TO);         \
                                                                               \
		/* saturate over-/underflows */                                \
		out.bits += (((out.bits == 0) & (in.bits != 0)) -              \
		             ((out.value == TAKUM##TO##_NAR) &                 \
		              (in.value != TAKUM##FROM##_NAR))) *              \
		            (1 - 2 * (in.value < 0));                          \
                                                                               \
		return out.value;                                              \
	} while (0);

/* Conversion from float32 */
takum8
takum8_from_float32(float f)
{
	return (takum8)codec_takum_log8_from_s_and_l(
		f < 0, (float)codec_linear_l_from_float32(f));
}

takum16
takum16_from_float32(float f)
{
	return (takum16)codec_takum_log16_from_s_and_l(
		f < 0, (float)codec_linear_l_from_float32(f));
}

takum32
takum32_from_float32(float f)
{
	return (takum32)codec_takum_log32_from_s_and_l(
		f < 0, codec_linear_l_from_float32(f));
}

takum64
takum64_from_float32(float f)
{
	return (takum64)codec_takum_log64_from_s_and_l(
		f < 0, (long double)codec_linear_l_from_float32(f));
}

takum_log8
takum_log8_from_float32(float f)
{
	if (f == 0.0f) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG8_NAR;
	} else {
		return codec_takum_log8_from_s_and_l(f < 0,
		                                     2 * log(fabs((double)f)));
	}
}

takum_log16
takum_log16_from_float32(float f)
{
	if (f == 0.0f) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG16_NAR;
	} else {
		return codec_takum_log16_from_s_and_l(f < 0,
		                                      2 * log(fabs((double)f)));
	}
}

takum_log32
takum_log32_from_float32(float f)
{
	if (f == 0.0f) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG32_NAR;
	} else {
		return codec_takum_log32_from_s_and_l(f < 0,
		                                      2 * log(fabs((double)f)));
	}
}

takum_log64
takum_log64_from_float32(float f)
{
	if (f == 0.0f) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG64_NAR;
	} else {
		return codec_takum_log64_from_s_and_l(
			f < 0, 2 * logl(fabsl((long double)f)));
	}
}

/* Conversion from float64 */
takum8
takum8_from_float64(double f)
{
	return (takum8)codec_takum_log8_from_s_and_l(
		f < 0, (float)codec_linear_l_from_float64(f));
}

takum16
takum16_from_float64(double f)
{
	return (takum16)codec_takum_log16_from_s_and_l(
		f < 0, (double)codec_linear_l_from_float64(f));
}

takum32
takum32_from_float64(double f)
{
	return (takum32)codec_takum_log32_from_s_and_l(
		f < 0, codec_linear_l_from_float64(f));
}

takum64
takum64_from_float64(double f)
{
	return (takum64)codec_takum_log64_from_s_and_l(
		f < 0, codec_linear_l_from_float64(f));
}

takum_log8
takum_log8_from_float64(double f)
{
	if (f == 0.0) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG8_NAR;
	} else {
		return takum_log8_from_takum_log64(
			codec_takum_log64_from_s_and_l(
				f < 0, 2 * logl(fabsl((long double)f))));
	}
}

takum_log16
takum_log16_from_float64(double f)
{
	if (f == 0.0) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG16_NAR;
	} else {
		return takum_log16_from_takum_log64(
			codec_takum_log64_from_s_and_l(
				f < 0, 2 * logl(fabsl((long double)f))));
	}
}

takum_log32
takum_log32_from_float64(double f)
{
	if (f == 0.0) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG32_NAR;
	} else {
		return codec_takum_log32_from_s_and_l(
			f < 0, 2 * logl(fabsl((long double)f)));
	}
}

takum_log64
takum_log64_from_float64(double f)
{
	if (f == 0.0) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG64_NAR;
	} else {
		return codec_takum_log64_from_s_and_l(
			f < 0, (long double)(2 * logl(fabsl((long double)f))));
	}
}

/* Conversion from extended float */
takum8
takum8_from_extended_float(long double f)
{
	return (takum8)codec_takum_log8_from_s_and_l(
		f < 0, (float)codec_linear_l_from_extended_float(f));
}

takum16
takum16_from_extended_float(long double f)
{
	return (takum16)codec_takum_log16_from_s_and_l(
		f < 0, (double)codec_linear_l_from_extended_float(f));
}

takum32
takum32_from_extended_float(long double f)
{
	return (takum32)codec_takum_log32_from_s_and_l(
		f < 0, codec_linear_l_from_extended_float(f));
}

takum64
takum64_from_extended_float(long double f)
{
	return (takum64)codec_takum_log64_from_s_and_l(
		f < 0, codec_linear_l_from_extended_float(f));
}

takum_log8
takum_log8_from_extended_float(long double f)
{
	if (f == 0.0L) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG8_NAR;
	} else {
		return takum_log8_from_takum_log64(
			codec_takum_log64_from_s_and_l(f < 0,
		                                       2 * logl(fabsl(f))));
	}
}

takum_log16
takum_log16_from_extended_float(long double f)
{
	if (f == 0.0L) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG16_NAR;
	} else {
		return takum_log16_from_takum_log64(
			codec_takum_log64_from_s_and_l(f < 0,
		                                       2 * logl(fabsl(f))));
	}
}

takum_log32
takum_log32_from_extended_float(long double f)
{
	if (f == 0.0L) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG32_NAR;
	} else {
		return takum_log32_from_takum_log64(
			codec_takum_log64_from_s_and_l(f < 0,
		                                       2 * logl(fabsl(f))));
	}
}

takum_log64
takum_log64_from_extended_float(long double f)
{
	if (f == 0.0L) {
		return 0;
	} else if (!isfinite(f)) {
		return TAKUM_LOG64_NAR;
	} else {
		return codec_takum_log64_from_s_and_l(f < 0,
		                                      2 * logl(fabsl(f)));
	}
}

/* Conversion from takum8 */
takum16
takum16_from_takum8(takum8 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(8, 16);
}

takum32
takum32_from_takum8(takum8 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(8, 32);
}

takum64
takum64_from_takum8(takum8 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(8, 64);
}

takum_log8
takum_log8_from_takum8(takum8 t)
{
	return takum_log8_from_float64(takum8_to_float64(t));
}

takum_log16
takum_log16_from_takum8(takum8 t)
{
	return takum_log16_from_float64(takum8_to_float64(t));
}

takum_log32
takum_log32_from_takum8(takum8 t)
{
	return takum_log32_from_float64(takum8_to_float64(t));
}

takum_log64
takum_log64_from_takum8(takum8 t)
{
	return takum_log64_from_extended_float(takum8_to_extended_float(t));
}

/* Conversion from takum16 */
takum8
takum8_from_takum16(takum16 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(16, 8);
}

takum32
takum32_from_takum16(takum16 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(16, 32);
}

takum64
takum64_from_takum16(takum16 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(16, 64);
}

takum_log8
takum_log8_from_takum16(takum16 t)
{
	return takum_log8_from_float64(takum16_to_float64(t));
}

takum_log16
takum_log16_from_takum16(takum16 t)
{
	return takum_log16_from_float64(takum16_to_float64(t));
}

takum_log32
takum_log32_from_takum16(takum16 t)
{
	return takum_log32_from_float64(takum16_to_float64(t));
}

takum_log64
takum_log64_from_takum16(takum16 t)
{
	return takum_log64_from_extended_float(takum16_to_extended_float(t));
}

/* Conversion from takum32 */
takum8
takum8_from_takum32(takum32 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(32, 8);
}

takum16
takum16_from_takum32(takum32 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(32, 16);
}

takum64
takum64_from_takum32(takum32 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(32, 64);
}

takum_log8
takum_log8_from_takum32(takum32 t)
{
	return takum_log8_from_float64(takum32_to_float64(t));
}

takum_log16
takum_log16_from_takum32(takum32 t)
{
	return takum_log16_from_float64(takum32_to_float64(t));
}

takum_log32
takum_log32_from_takum32(takum32 t)
{
	return takum_log32_from_float64(takum32_to_float64(t));
}

takum_log64
takum_log64_from_takum32(takum32 t)
{
	return takum_log64_from_extended_float(takum32_to_extended_float(t));
}

/* Conversion from takum64 */
takum8
takum8_from_takum64(takum64 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(64, 8);
}

takum16
takum16_from_takum64(takum64 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(64, 16);
}

takum32
takum32_from_takum64(takum64 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(64, 32);
}

takum_log8
takum_log8_from_takum64(takum64 t)
{
	return takum_log8_from_extended_float(takum64_to_extended_float(t));
}

takum_log16
takum_log16_from_takum64(takum64 t)
{
	return takum_log16_from_extended_float(takum64_to_extended_float(t));
}

takum_log32
takum_log32_from_takum64(takum64 t)
{
	return takum_log32_from_extended_float(takum64_to_extended_float(t));
}

takum_log64
takum_log64_from_takum64(takum64 t)
{
	return takum_log64_from_extended_float(takum64_to_extended_float(t));
}

/* Conversion from takum_log8 */
takum8
takum8_from_takum_log8(takum_log8 t)
{
	return takum8_from_float64(takum_log8_to_float64(t));
}

takum16
takum16_from_takum_log8(takum_log8 t)
{
	return takum16_from_float64(takum_log8_to_float64(t));
}

takum32
takum32_from_takum_log8(takum_log8 t)
{
	return takum32_from_float64(takum_log8_to_float64(t));
}

takum64
takum64_from_takum_log8(takum_log8 t)
{
	return takum64_from_extended_float(takum_log8_to_extended_float(t));
}

takum_log16
takum_log16_from_takum_log8(takum_log8 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(8, 16);
}

takum_log32
takum_log32_from_takum_log8(takum_log8 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(8, 32);
}

takum_log64
takum_log64_from_takum_log8(takum_log8 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(8, 64);
}

/* Conversion from takum_log16 */
takum8
takum8_from_takum_log16(takum_log16 t)
{
	return takum8_from_float64(takum_log16_to_float64(t));
}

takum16
takum16_from_takum_log16(takum_log16 t)
{
	return takum16_from_float64(takum_log16_to_float64(t));
}

takum32
takum32_from_takum_log16(takum_log16 t)
{
	return takum32_from_float64(takum_log16_to_float64(t));
}

takum64
takum64_from_takum_log16(takum_log16 t)
{
	return takum64_from_extended_float(takum_log16_to_extended_float(t));
}

takum_log8
takum_log8_from_takum_log16(takum_log16 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(16, 8);
}

takum_log32
takum_log32_from_takum_log16(takum_log16 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(16, 32);
}

takum_log64
takum_log64_from_takum_log16(takum_log16 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(16, 64);
}

/* Conversion from takum_log32 */
takum8
takum8_from_takum_log32(takum_log32 t)
{
	return takum8_from_float64(takum_log32_to_float64(t));
}

takum16
takum16_from_takum_log32(takum_log32 t)
{
	return takum16_from_float64(takum_log32_to_float64(t));
}

takum32
takum32_from_takum_log32(takum_log32 t)
{
	return takum32_from_float64(takum_log32_to_float64(t));
}

takum64
takum64_from_takum_log32(takum_log32 t)
{
	return takum64_from_extended_float(takum_log32_to_extended_float(t));
}

takum_log8
takum_log8_from_takum_log32(takum_log32 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(32, 8);
}

takum_log16
takum_log16_from_takum_log32(takum_log32 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(32, 16);
}

takum_log64
takum_log64_from_takum_log32(takum_log32 t)
{
	TAKUM_INTERNAL_CONVERT_EXPAND(32, 64);
}

/* Conversion from takum_log64 */
takum8
takum8_from_takum_log64(takum_log64 t)
{
	return takum8_from_extended_float(takum_log64_to_extended_float(t));
}

takum16
takum16_from_takum_log64(takum_log64 t)
{
	return takum16_from_extended_float(takum_log64_to_extended_float(t));
}

takum32
takum32_from_takum_log64(takum_log64 t)
{
	return takum32_from_extended_float(takum_log64_to_extended_float(t));
}

takum64
takum64_from_takum_log64(takum_log64 t)
{
	return takum64_from_extended_float(takum_log64_to_extended_float(t));
}

takum_log8
takum_log8_from_takum_log64(takum_log64 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(64, 8);
}

takum_log16
takum_log16_from_takum_log64(takum_log64 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(64, 16);
}

takum_log32
takum_log32_from_takum_log64(takum_log64 t)
{
	TAKUM_INTERNAL_CONVERT_REDUCE(64, 32);
}

/* Conversion to float32 */
float
takum8_to_float32(takum8 t)
{
	return (float)codec_s_and_linear_l_to_float64(
		t < 0, (long double)codec_takum_log8_to_l((takum_log8)t));
}

float
takum16_to_float32(takum16 t)
{
	return (float)codec_s_and_linear_l_to_float64(
		t < 0, (long double)codec_takum_log16_to_l((takum_log16)t));
}

float
takum32_to_float32(takum32 t)
{
	return (float)codec_s_and_linear_l_to_float64(
		t < 0, (long double)codec_takum_log32_to_l((takum_log32)t));
}

float
takum64_to_float32(takum64 t)
{
	return (float)codec_s_and_linear_l_to_float64(
		t < 0, codec_takum_log64_to_l((takum_log64)t));
}

float
takum_log8_to_float32(takum_log8 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powf(SQRTE, codec_takum_log8_to_l(t));
}

float
takum_log16_to_float32(takum_log16 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powf(SQRTE, codec_takum_log16_to_l(t));
}

float
takum_log32_to_float32(takum_log32 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powf(SQRTE, (float)codec_takum_log32_to_l(t));
}

float
takum_log64_to_float32(takum_log64 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powf(SQRTE, (float)codec_takum_log64_to_l(t));
}

/* Conversion to float64 */
double
takum8_to_float64(takum8 t)
{
	return codec_s_and_linear_l_to_float64(
		t < 0, (long double)codec_takum_log8_to_l((takum_log8)t));
}

double
takum16_to_float64(takum16 t)
{
	return codec_s_and_linear_l_to_float64(
		t < 0, (long double)codec_takum_log16_to_l((takum_log16)t));
}

double
takum32_to_float64(takum32 t)
{
	return codec_s_and_linear_l_to_float64(
		t < 0, (long double)codec_takum_log32_to_l((takum_log32)t));
}

double
takum64_to_float64(takum64 t)
{
	return codec_s_and_linear_l_to_float64(
		t < 0, codec_takum_log64_to_l((takum_log64)t));
}

double
takum_log8_to_float64(takum_log8 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powl(SQRTE, (long double)codec_takum_log8_to_l(t));
}

double
takum_log16_to_float64(takum_log16 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       pow(SQRTE, (double)codec_takum_log16_to_l(t));
}

double
takum_log32_to_float64(takum_log32 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       pow(SQRTE, codec_takum_log32_to_l(t));
}

double
takum_log64_to_float64(takum_log64 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       pow(SQRTE, (double)codec_takum_log64_to_l(t));
}

/* Conversion to extended float */
long double
takum8_to_extended_float(takum8 t)
{
	return (long double)codec_s_and_linear_l_to_float64(
		t < 0, (double)codec_takum_log8_to_l((takum_log8)t));
}

long double
takum16_to_extended_float(takum16 t)
{
	return (long double)codec_s_and_linear_l_to_float64(
		t < 0, codec_takum_log16_to_l((takum_log16)t));
}

long double
takum32_to_extended_float(takum32 t)
{
	return (long double)codec_s_and_linear_l_to_float64(
		t < 0, codec_takum_log32_to_l((takum_log32)t));
}

long double
takum64_to_extended_float(takum64 t)
{
	return codec_s_and_linear_l_to_extended_float(
		t < 0, codec_takum_log64_to_l((takum_log64)t));
}

long double
takum_log8_to_extended_float(takum_log8 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powl(SQRTE, (long double)codec_takum_log8_to_l(t));
}

long double
takum_log16_to_extended_float(takum_log16 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powl(SQRTE, (long double)codec_takum_log16_to_l(t));
}

long double
takum_log32_to_extended_float(takum_log32 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powl(SQRTE, (long double)codec_takum_log32_to_l(t));
}

long double
takum_log64_to_extended_float(takum_log64 t)
{
	return (t != 0) * (1 - 2 * (t < 0)) *
	       powl(SQRTE, codec_takum_log64_to_l(t));
}
