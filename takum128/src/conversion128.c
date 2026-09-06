/* See LICENSE file for copyright and license details. */
#include <mpfr.h>
#include <stdint.h>

#include "../../takum128.h"

#include "codec128.h"
#include "util128.h"

/*
 * Widen a smaller takum/takum_log into a takum128/takum_log128: pure
 * bit-shift-left, no precision loss, no MPFR needed. Mirrors
 * TAKUM_INTERNAL_CONVERT_EXPAND in ../../src/conversion.c.
 */
#define TAKUM128_WIDEN(FROM_WIDTH)                                             \
	do {                                                                   \
		union util_takum128_union out_;                                \
		out_.bits = ((unsigned __int128)(uint##FROM_WIDTH##_t)t)       \
		            << (128 - (FROM_WIDTH));                           \
		return out_.value;                                             \
	} while (0)

/*
 * Narrow a takum128/takum_log128 into a smaller takum/takum_log: pure
 * integer rounding (util_round_uint128_to_number_of_bits) plus
 * saturation on over-/underflow, no MPFR needed. Mirrors
 * TAKUM_INTERNAL_CONVERT_REDUCE in ../../src/conversion.c.
 */
#define TAKUM128_NARROW(TO_TYPE, TO_WIDTH, FROM_NAR, TO_NAR)                   \
	do {                                                                   \
		const union util_takum128_union in_ = {                        \
			.value = t,                                            \
		};                                                             \
		union {                                                        \
			TO_TYPE value;                                         \
			uint##TO_WIDTH##_t bits;                               \
		} out_;                                                        \
                                                                               \
		out_.bits = (uint##TO_WIDTH##_t)                               \
			util_round_uint128_to_number_of_bits(in_.bits,         \
		                                             (TO_WIDTH));      \
                                                                               \
		out_.bits +=                                                   \
			(((out_.bits == 0) & (in_.bits != 0)) -                \
		         ((out_.value == (TO_NAR)) & (t != (FROM_NAR)))) *     \
			(1 - 2 * (t < 0));                                     \
                                                                               \
		return out_.value;                                             \
	} while (0)

/* Widening: takum{8,16,32,64} -> takum128 */
takum128
takum128_from_takum8(takum8 t)
{
	TAKUM128_WIDEN(8);
}

takum128
takum128_from_takum16(takum16 t)
{
	TAKUM128_WIDEN(16);
}

takum128
takum128_from_takum32(takum32 t)
{
	TAKUM128_WIDEN(32);
}

takum128
takum128_from_takum64(takum64 t)
{
	TAKUM128_WIDEN(64);
}

/* Widening: takum_log{8,16,32,64} -> takum_log128 */
takum_log128
takum_log128_from_takum_log8(takum_log8 t)
{
	TAKUM128_WIDEN(8);
}

takum_log128
takum_log128_from_takum_log16(takum_log16 t)
{
	TAKUM128_WIDEN(16);
}

takum_log128
takum_log128_from_takum_log32(takum_log32 t)
{
	TAKUM128_WIDEN(32);
}

takum_log128
takum_log128_from_takum_log64(takum_log64 t)
{
	TAKUM128_WIDEN(64);
}

/* Narrowing: takum128 -> takum{8,16,32,64} */
takum8
takum8_from_takum128(takum128 t)
{
	TAKUM128_NARROW(takum8, 8, TAKUM128_NAR, TAKUM8_NAR);
}

takum16
takum16_from_takum128(takum128 t)
{
	TAKUM128_NARROW(takum16, 16, TAKUM128_NAR, TAKUM16_NAR);
}

takum32
takum32_from_takum128(takum128 t)
{
	TAKUM128_NARROW(takum32, 32, TAKUM128_NAR, TAKUM32_NAR);
}

takum64
takum64_from_takum128(takum128 t)
{
	TAKUM128_NARROW(takum64, 64, TAKUM128_NAR, TAKUM64_NAR);
}

/* Narrowing: takum_log128 -> takum_log{8,16,32,64} */
takum_log8
takum_log8_from_takum_log128(takum_log128 t)
{
	TAKUM128_NARROW(takum_log8, 8, TAKUM_LOG128_NAR, TAKUM_LOG8_NAR);
}

takum_log16
takum_log16_from_takum_log128(takum_log128 t)
{
	TAKUM128_NARROW(takum_log16, 16, TAKUM_LOG128_NAR, TAKUM_LOG16_NAR);
}

takum_log32
takum_log32_from_takum_log128(takum_log128 t)
{
	TAKUM128_NARROW(takum_log32, 32, TAKUM_LOG128_NAR, TAKUM_LOG32_NAR);
}

takum_log64
takum_log64_from_takum_log128(takum_log128 t)
{
	TAKUM128_NARROW(takum_log64, 64, TAKUM_LOG128_NAR, TAKUM_LOG64_NAR);
}

/*
 * Cross conversions between takum{8,16,32,64} and takum_log128, and
 * between takum_log{8,16,32,64} and takum128, all route through the
 * two directly-adjacent conversions (mirrors the pattern
 * ../../src/conversion.c uses, e.g. takum_log8_from_takum32 composing
 * takum_log8_from_takum_log64(codec...)).
 */
takum_log128
takum_log128_from_takum8(takum8 t)
{
	return takum128_from_takum_log128(takum128_from_takum8(t));
}

takum_log128
takum_log128_from_takum16(takum16 t)
{
	return takum128_from_takum_log128(takum128_from_takum16(t));
}

takum_log128
takum_log128_from_takum32(takum32 t)
{
	return takum128_from_takum_log128(takum128_from_takum32(t));
}

takum_log128
takum_log128_from_takum64(takum64 t)
{
	return takum128_from_takum_log128(takum128_from_takum64(t));
}

takum128
takum128_from_takum_log8(takum_log8 t)
{
	return takum_log128_from_takum128(takum_log128_from_takum_log8(t));
}

takum128
takum128_from_takum_log16(takum_log16 t)
{
	return takum_log128_from_takum128(takum_log128_from_takum_log16(t));
}

takum128
takum128_from_takum_log32(takum_log32 t)
{
	return takum_log128_from_takum128(takum_log128_from_takum_log32(t));
}

takum128
takum128_from_takum_log64(takum_log64 t)
{
	return takum_log128_from_takum128(takum_log128_from_takum_log64(t));
}

takum_log8
takum_log8_from_takum128(takum128 t)
{
	return takum_log8_from_takum_log128(takum_log128_from_takum128(t));
}

takum_log16
takum_log16_from_takum128(takum128 t)
{
	return takum_log16_from_takum_log128(takum_log128_from_takum128(t));
}

takum_log32
takum_log32_from_takum128(takum128 t)
{
	return takum_log32_from_takum_log128(takum_log128_from_takum128(t));
}

takum_log64
takum_log64_from_takum128(takum128 t)
{
	return takum_log64_from_takum_log128(takum_log128_from_takum128(t));
}

takum8
takum8_from_takum_log128(takum_log128 t)
{
	return takum8_from_takum128(takum128_from_takum_log128(t));
}

takum16
takum16_from_takum_log128(takum_log128 t)
{
	return takum16_from_takum128(takum128_from_takum_log128(t));
}

takum32
takum32_from_takum_log128(takum_log128 t)
{
	return takum32_from_takum128(takum128_from_takum_log128(t));
}

takum64
takum64_from_takum_log128(takum_log128 t)
{
	return takum64_from_takum128(takum128_from_takum_log128(t));
}

/* takum128 <-> takum_log128 */
takum_log128
takum_log128_from_takum128(takum128 t)
{
	mpfr_t l, value;
	takum_log128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, l, value, (mpfr_ptr)0);

	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(value, t < 0, l);
	result = codec128_log_from_value(value);

	mpfr_clears(l, value, (mpfr_ptr)0);

	return result;
}

takum128
takum128_from_takum_log128(takum_log128 t)
{
	mpfr_t value, l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, value, l, (mpfr_ptr)0);

	codec128_log_value_from_t(value, t);
	codec128_linear_l_from_value(l, value);
	result = codec128_log_from_s_and_l(t < 0, l);

	mpfr_clears(value, l, (mpfr_ptr)0);

	return result;
}

/* Conversion from float32/float64/extended float */
takum128
takum128_from_float32(float f)
{
	mpfr_t value, l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, value, l, (mpfr_ptr)0);
	mpfr_set_flt(value, f, MPFR_RNDN);
	codec128_linear_l_from_value(l, value);
	result = codec128_log_from_s_and_l(f < 0, l);
	mpfr_clears(value, l, (mpfr_ptr)0);

	return result;
}

takum128
takum128_from_float64(double f)
{
	mpfr_t value, l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, value, l, (mpfr_ptr)0);
	mpfr_set_d(value, f, MPFR_RNDN);
	codec128_linear_l_from_value(l, value);
	result = codec128_log_from_s_and_l(f < 0, l);
	mpfr_clears(value, l, (mpfr_ptr)0);

	return result;
}

takum128
takum128_from_extended_float(long double f)
{
	mpfr_t value, l;
	takum128 result;

	mpfr_inits2(TAKUM128_MPFR_PREC, value, l, (mpfr_ptr)0);
	mpfr_set_ld(value, f, MPFR_RNDN);
	codec128_linear_l_from_value(l, value);
	result = codec128_log_from_s_and_l(f < 0, l);
	mpfr_clears(value, l, (mpfr_ptr)0);

	return result;
}

takum_log128
takum_log128_from_float32(float f)
{
	mpfr_t value;
	takum_log128 result;

	mpfr_init2(value, TAKUM128_MPFR_PREC);
	mpfr_set_flt(value, f, MPFR_RNDN);
	result = codec128_log_from_value(value);
	mpfr_clear(value);

	return result;
}

takum_log128
takum_log128_from_float64(double f)
{
	mpfr_t value;
	takum_log128 result;

	mpfr_init2(value, TAKUM128_MPFR_PREC);
	mpfr_set_d(value, f, MPFR_RNDN);
	result = codec128_log_from_value(value);
	mpfr_clear(value);

	return result;
}

takum_log128
takum_log128_from_extended_float(long double f)
{
	mpfr_t value;
	takum_log128 result;

	mpfr_init2(value, TAKUM128_MPFR_PREC);
	mpfr_set_ld(value, f, MPFR_RNDN);
	result = codec128_log_from_value(value);
	mpfr_clear(value);

	return result;
}

/* Conversion to float32/float64/extended float */
float
takum128_to_float32(takum128 t)
{
	mpfr_t l, value;
	float result;

	mpfr_inits2(TAKUM128_MPFR_PREC, l, value, (mpfr_ptr)0);
	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(value, t < 0, l);
	result = mpfr_get_flt(value, MPFR_RNDN);
	mpfr_clears(l, value, (mpfr_ptr)0);

	return result;
}

double
takum128_to_float64(takum128 t)
{
	mpfr_t l, value;
	double result;

	mpfr_inits2(TAKUM128_MPFR_PREC, l, value, (mpfr_ptr)0);
	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(value, t < 0, l);
	result = mpfr_get_d(value, MPFR_RNDN);
	mpfr_clears(l, value, (mpfr_ptr)0);

	return result;
}

long double
takum128_to_extended_float(takum128 t)
{
	mpfr_t l, value;
	long double result;

	mpfr_inits2(TAKUM128_MPFR_PREC, l, value, (mpfr_ptr)0);
	codec128_log_to_l(l, (takum_log128)t);
	codec128_linear_value_from_s_and_l(value, t < 0, l);
	result = mpfr_get_ld(value, MPFR_RNDN);
	mpfr_clears(l, value, (mpfr_ptr)0);

	return result;
}

float
takum_log128_to_float32(takum_log128 t)
{
	mpfr_t value;
	float result;

	mpfr_init2(value, TAKUM128_MPFR_PREC);
	codec128_log_value_from_t(value, t);
	result = mpfr_get_flt(value, MPFR_RNDN);
	mpfr_clear(value);

	return result;
}

double
takum_log128_to_float64(takum_log128 t)
{
	mpfr_t value;
	double result;

	mpfr_init2(value, TAKUM128_MPFR_PREC);
	codec128_log_value_from_t(value, t);
	result = mpfr_get_d(value, MPFR_RNDN);
	mpfr_clear(value);

	return result;
}

long double
takum_log128_to_extended_float(takum_log128 t)
{
	mpfr_t value;
	long double result;

	mpfr_init2(value, TAKUM128_MPFR_PREC);
	codec128_log_value_from_t(value, t);
	result = mpfr_get_ld(value, MPFR_RNDN);
	mpfr_clear(value);

	return result;
}
