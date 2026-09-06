/* See LICENSE file for copyright and license details. */
#ifndef CODEC128_H
#define CODEC128_H

#include <mpfr.h>
#include <stdbool.h>

#include "../../takum128.h"

/*
 * Decode a takum_log128's stored logarithmic value into out_l, at
 * TAKUM128_MPFR_PREC precision. Mirrors codec_takum_log64_to_l in
 * ../../src/codec.c: t == 0 -> -inf, t == NaR -> NaN, otherwise the
 * signed l = (-1)^s (c + m).
 */
void codec128_log_to_l(mpfr_t out_l, takum_log128 t);

/*
 * Encode a signed l (as produced by codec128_log_to_l or
 * codec128_linear_l_from_value) together with an explicit sign s into a
 * takum_log128, applying the takum format's round-to-nearest-even and
 * saturation rules. Mirrors codec_takum_log64_from_s_and_l.
 */
takum_log128 codec128_log_from_s_and_l(bool s, mpfr_t l);

/*
 * Algorithm 5 (takum paper): convert a (sign, l) pair to the actual
 * linear value it represents. Mirrors
 * codec_s_and_linear_l_to_extended_float.
 */
void codec128_linear_value_from_s_and_l(mpfr_t out, bool s, mpfr_t l);

/*
 * Algorithm 4 (takum paper): convert a linear value to its signed l.
 * Mirrors codec_linear_l_from_extended_float.
 */
void codec128_linear_l_from_value(mpfr_t out_l, mpfr_t value);

/*
 * takum_log128's "value" (as opposed to its stored l): value =
 * sign * exp(l/2). Mirrors takum_log64_to_extended_float.
 */
void codec128_log_value_from_t(mpfr_t out, takum_log128 t);

/*
 * Inverse of the above: encode a linear value directly as a
 * takum_log128 via l = 2 ln|value|. Mirrors the takum_log64_from_s_and_l
 * call pattern used throughout ../../src/conversion.c.
 */
takum_log128 codec128_log_from_value(mpfr_t value);

#endif /* CODEC128_H */
