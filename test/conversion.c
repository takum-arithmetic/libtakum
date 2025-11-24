/* See LICENSE file for copyright and license details. */
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "../takum.h"
#include "util.h"

takum8
takum8_conversion_float64_roundtrip(takum8 t)
{
	return takum8_from_float64(takum8_to_float64(t));
}

takum16
takum16_conversion_float64_roundtrip(takum16 t)
{
	return takum16_from_float64(takum16_to_float64(t));
}

takum32
takum32_conversion_float64_roundtrip(takum32 t)
{
	return takum32_from_float64(takum32_to_float64(t));
}

takum_log8
takum_log8_conversion_float64_roundtrip(takum_log8 t)
{
	return takum_log8_from_float64(takum_log8_to_float64(t));
}

takum_log16
takum_log16_conversion_float64_roundtrip(takum_log16 t)
{
	return takum_log16_from_float64(takum_log16_to_float64(t));
}

takum_log32
takum_log32_conversion_float64_roundtrip(takum_log32 t)
{
	return takum_log32_from_float64(takum_log32_to_float64(t));
}

static const struct unit_test_block conversion_float64_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_ROUNDTRIP,
	.function_name = "to_float64/from_float64",
	.data.roundtrip = {
		.takum8_function    = takum8_conversion_float64_roundtrip,
		.takum16_function   = takum16_conversion_float64_roundtrip,
		.takum32_function   = takum32_conversion_float64_roundtrip,
		.takum64_function   = NULL,
		.takum_log8_function    = takum_log8_conversion_float64_roundtrip,
		.takum_log16_function   = takum_log16_conversion_float64_roundtrip,
		.takum_log32_function   = takum_log32_conversion_float64_roundtrip,
		.takum_log64_function   = NULL,
	},
};

takum8
takum8_conversion_extended_float_roundtrip(takum8 t)
{
	return takum8_from_extended_float(takum8_to_extended_float(t));
}

takum16
takum16_conversion_extended_float_roundtrip(takum16 t)
{
	return takum16_from_extended_float(takum16_to_extended_float(t));
}

takum32
takum32_conversion_extended_float_roundtrip(takum32 t)
{
	return takum32_from_extended_float(takum32_to_extended_float(t));
}

takum64
takum64_conversion_extended_float_roundtrip(takum64 t)
{
	return takum64_from_extended_float(takum64_to_extended_float(t));
}

takum_log8
takum_log8_conversion_extended_float_roundtrip(takum_log8 t)
{
	return takum_log8_from_extended_float(takum_log8_to_extended_float(t));
}

takum_log16
takum_log16_conversion_extended_float_roundtrip(takum_log16 t)
{
	return takum_log16_from_extended_float(
		takum_log16_to_extended_float(t));
}

takum_log32
takum_log32_conversion_extended_float_roundtrip(takum_log32 t)
{
	return takum_log32_from_extended_float(
		takum_log32_to_extended_float(t));
}

takum_log64
takum_log64_conversion_extended_float_roundtrip(takum_log64 t)
{
	return takum_log64_from_extended_float(
		takum_log64_to_extended_float(t));
}

static const struct unit_test_block conversion_extended_float_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_ROUNDTRIP,
	.function_name = "to_extended_float/from_extended_float",
	.data.roundtrip = {
		.takum8_function    = takum8_conversion_extended_float_roundtrip,
		.takum16_function   = takum16_conversion_extended_float_roundtrip,
		.takum32_function   = takum32_conversion_extended_float_roundtrip,
		.takum64_function   = takum64_conversion_extended_float_roundtrip,
		.takum_log8_function    = takum_log8_conversion_extended_float_roundtrip,
		.takum_log16_function   = takum_log16_conversion_extended_float_roundtrip,
		.takum_log32_function   = takum_log32_conversion_extended_float_roundtrip,
		.takum_log64_function   = takum_log64_conversion_extended_float_roundtrip,
	},
};

takum_log64
float64_conversion_takum64_roundtrip(takum_log64 t)
{
	union {
		takum64 takum64_value;
		double float64_value;
	} helper_union = {
		.takum64_value = t,
	};

	double f;

	/* Interpret the input as a float64 */
	f = helper_union.float64_value;

	/*
	 * Check if it is real and in the range of numbers representable
	 * with takum_log64
	 */
	if (!isfinite(f) || fabs(f) >= exp2(255) || fabs(f) <= exp2(-255)) {
		/* skip this test case */
		return t;
	} else {
		/*
		 * Convert to a takum_log64 and back and reinterpret
		 * the result as a takum_log64 that is returned as
		 * output
		 */
		helper_union.float64_value =
			takum64_to_float64(takum64_from_float64(f));

		return helper_union.takum64_value;
	}
}

static const struct unit_test_block conversion_float64_full_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_ROUNDTRIP,
	.function_name = "from_float64/to_float64",
	.data.roundtrip = {
		.takum8_function    = NULL,
		.takum16_function   = NULL,
		.takum32_function   = NULL,
		.takum64_function   = float64_conversion_takum64_roundtrip,
		.takum_log8_function    = NULL,
		.takum_log16_function   = NULL,
		.takum_log32_function   = NULL,
		.takum_log64_function   = NULL,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&conversion_float64_utb) +
	       run_unit_test_block(&conversion_extended_float_utb) +
	       run_unit_test_block(&conversion_float64_full_utb);
}
