/* See LICENSE file for copyright and license details. */
#ifndef UTIL128_H
#define UTIL128_H

#include <mpfr.h>
#include <stdint.h>

#include "../../takum128.h"

#include "codec128.h"

/*
 * Working precision for all internal mpfr_t temporaries. A takum128's
 * mantissa field is at most p_lut[8] + 112 = 123 bits (see codec128.c);
 * 192 bits leaves 69 guard bits, which is ample to keep composite
 * operations (e.g. sec = 1/cos) from losing accuracy to double rounding.
 */
#define TAKUM128_MPFR_PREC 192

/* 128 - 16: the width beyond the 16-bit fragment that get_c_and_return_shift
 * operates on. All of it is extra mantissa (see codec128.c for why). */
#define TAKUM128_WIDTH_EXTRA 112

#undef LEN
#define LEN(x) (sizeof(x) / sizeof(*(x)))

/* type punning union, mirrors util_takum64_union in ../../src/util.h */
union util_takum128_union {
	__int128 value;
	unsigned __int128 bits;
};

/*
 * Assume the input is a left-aligned fixed-point representation of a
 * value [0,1) with 128 bits. Round to a right-aligned representation
 * with exactly the given number of bits, ties to even. Direct 128-bit
 * transcription of util_round_uint64_to_number_of_bits in ../../src/util.c
 * (no UINT128_C-style literal suffix exists, hence the explicit casts).
 */
unsigned __int128 util_round_uint128_to_number_of_bits(unsigned __int128 input,
                                                       uint8_t number_of_bits);

/*
 * Generate takum128_NAME/takum_log128_NAME from a single MPFR function
 * of shape int(mpfr_t rop, const mpfr_t op, mpfr_rnd_t rnd) -- mirrors
 * UTIL_UNARY_FLOAT_TAKUM_WRAPPER/UTIL_UNARY_FLOAT_TAKUM_LOG_WRAPPER in
 * ../../src/util.h, but there is no RESULT_FIXER_MACRO: MPFR's huge
 * native exponent range means intermediate overflow/underflow the way
 * hardware float can hit just doesn't happen here (see codec128.c) --
 * the only saturation point is the final encode, which
 * codec128_log_from_s_and_l already clamps correctly.
 *
 * For composite functions with no direct MPFR primitive (e.g. arccot),
 * define a small static helper of the same (mpfr_t, mpfr_t, mpfr_rnd_t)
 * shape and pass that instead -- exactly like ../../src/arccot.c defines
 * its own static arccotl() before invoking the generic wrapper.
 */
#define TAKUM128_UNARY_WRAPPER(NAME, MPFR_FUNC)                                \
	takum128 takum128_##NAME(takum128 t)                                   \
	{                                                                       \
		mpfr_t l_, v_, out_l_;                                          \
		takum128 result_;                                              \
                                                                                \
		mpfr_inits2(TAKUM128_MPFR_PREC, l_, v_, out_l_, (mpfr_ptr)0);   \
		codec128_log_to_l(l_, (takum_log128)t);                        \
		codec128_linear_value_from_s_and_l(v_, t < 0, l_);              \
		MPFR_FUNC(v_, v_, MPFR_RNDN);                                   \
		codec128_linear_l_from_value(out_l_, v_);                       \
		result_ = codec128_log_from_s_and_l(mpfr_sgn(v_) < 0, out_l_);  \
		mpfr_clears(l_, v_, out_l_, (mpfr_ptr)0);                       \
                                                                                \
		return result_;                                                 \
	}                                                                       \
                                                                                \
	takum_log128 takum_log128_##NAME(takum_log128 t)                       \
	{                                                                       \
		mpfr_t v_;                                                      \
		takum_log128 result_;                                          \
                                                                                \
		mpfr_init2(v_, TAKUM128_MPFR_PREC);                             \
		codec128_log_value_from_t(v_, t);                               \
		MPFR_FUNC(v_, v_, MPFR_RNDN);                                   \
		result_ = codec128_log_from_value(v_);                          \
		mpfr_clear(v_);                                                 \
                                                                                \
		return result_;                                                 \
	}

/*
 * Same idea for a 2-argument MPFR function of shape
 * int(mpfr_t rop, const mpfr_t a, const mpfr_t b, mpfr_rnd_t rnd) --
 * mirrors UTIL_BINARY_FLOAT_TAKUM_WRAPPER/_LOG_WRAPPER.
 */
#define TAKUM128_BINARY_WRAPPER(NAME, MPFR_FUNC)                               \
	takum128 takum128_##NAME(takum128 a, takum128 b)                       \
	{                                                                       \
		mpfr_t la_, lb_, va_, vb_, res_, out_l_;                        \
		takum128 result_;                                              \
                                                                                \
		mpfr_inits2(TAKUM128_MPFR_PREC, la_, lb_, va_, vb_, res_,       \
		            out_l_, (mpfr_ptr)0);                               \
		codec128_log_to_l(la_, (takum_log128)a);                       \
		codec128_linear_value_from_s_and_l(va_, a < 0, la_);            \
		codec128_log_to_l(lb_, (takum_log128)b);                       \
		codec128_linear_value_from_s_and_l(vb_, b < 0, lb_);            \
		MPFR_FUNC(res_, va_, vb_, MPFR_RNDN);                           \
		codec128_linear_l_from_value(out_l_, res_);                     \
		result_ = codec128_log_from_s_and_l(mpfr_sgn(res_) < 0,         \
		                                     out_l_);                   \
		mpfr_clears(la_, lb_, va_, vb_, res_, out_l_, (mpfr_ptr)0);     \
                                                                                \
		return result_;                                                 \
	}                                                                       \
                                                                                \
	takum_log128 takum_log128_##NAME(takum_log128 a, takum_log128 b)       \
	{                                                                       \
		mpfr_t va_, vb_, res_;                                          \
		takum_log128 result_;                                          \
                                                                                \
		mpfr_inits2(TAKUM128_MPFR_PREC, va_, vb_, res_, (mpfr_ptr)0);   \
		codec128_log_value_from_t(va_, a);                              \
		codec128_log_value_from_t(vb_, b);                              \
		MPFR_FUNC(res_, va_, vb_, MPFR_RNDN);                           \
		result_ = codec128_log_from_value(res_);                        \
		mpfr_clears(va_, vb_, res_, (mpfr_ptr)0);                       \
                                                                                \
		return result_;                                                 \
	}

#endif /* UTIL128_H */
