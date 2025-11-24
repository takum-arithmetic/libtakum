/* See LICENSE file for copyright and license details. */
#include <stdint.h>
#include <stdio.h>

#include "../takum.h"
#include "util.h"

#include "../src/codec.h"

takum8
takum8_codec_roundtrip(takum8 t)
{
	return takum8_from_float64(takum8_to_float64(t));
}

takum16
takum16_codec_roundtrip(takum16 t)
{
	return takum16_from_float64(takum16_to_float64(t));
}

takum32
takum32_codec_roundtrip(takum32 t)
{
	return takum32_from_float64(takum32_to_float64(t));
}

takum64
takum64_codec_roundtrip(takum64 t)
{
	return takum64_from_extended_float(takum64_to_extended_float(t));
}

takum_log8
takum_log8_codec_roundtrip(takum_log8 t)
{
	return codec_takum_log8_from_s_and_l(t < 0, codec_takum_log8_to_l(t));
}

takum_log16
takum_log16_codec_roundtrip(takum_log16 t)
{
	return codec_takum_log16_from_s_and_l(t < 0, codec_takum_log16_to_l(t));
}

takum_log32
takum_log32_codec_roundtrip(takum_log32 t)
{
	return codec_takum_log32_from_s_and_l(t < 0, codec_takum_log32_to_l(t));
}

takum_log64
takum_log64_codec_roundtrip(takum_log64 t)
{
	return codec_takum_log64_from_s_and_l(t < 0, codec_takum_log64_to_l(t));
}

static const struct unit_test_block codec_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_ROUNDTRIP,
	.function_name = "to_l/from_s_and_l",
	.data.roundtrip = {
		.takum8_function    = takum8_codec_roundtrip,
		.takum16_function   = takum16_codec_roundtrip,
		.takum32_function   = takum32_codec_roundtrip,
		.takum64_function   = takum64_codec_roundtrip,
		.takum_log8_function    = takum_log8_codec_roundtrip,
		.takum_log16_function   = takum_log16_codec_roundtrip,
		.takum_log32_function   = takum_log32_codec_roundtrip,
		.takum_log64_function   = takum_log64_codec_roundtrip,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&codec_utb);
}
