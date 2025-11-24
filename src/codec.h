/* See LICENSE file for copyright and license details. */
#ifndef CODEC_H
#define CODEC_H

#include <stdbool.h>

#include "../takum.h"

float codec_takum_log8_to_l(takum_log8);
float codec_takum_log16_to_l(takum_log16);
double codec_takum_log32_to_l(takum_log32);
long double codec_takum_log64_to_l(takum_log64);

double codec_s_and_linear_l_to_float64(bool, long double);
long double codec_s_and_linear_l_to_extended_float(bool, long double);

double codec_linear_l_from_float32(float);
long double codec_linear_l_from_float64(double);
long double codec_linear_l_from_extended_float(long double);

takum_log8 codec_takum_log8_from_s_and_l(bool, float);
takum_log16 codec_takum_log16_from_s_and_l(bool, double);
takum_log32 codec_takum_log32_from_s_and_l(bool, long double);
takum_log64 codec_takum_log64_from_s_and_l(bool, long double);

#endif /* CODEC_H */
