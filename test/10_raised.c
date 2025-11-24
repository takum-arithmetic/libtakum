/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
ten_raised_reference(long double a)
{
	return powl(10.0L, a);
}

static const struct unit_test_block ten_raised_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "10_raised",
	.data.takum_takum = {
		.reference_function = ten_raised_reference,
		.takum8_function    = takum8_10_raised,
		.takum16_function   = takum16_10_raised,
		.takum32_function   = takum32_10_raised,
		.takum64_function   = takum64_10_raised,
		.takum_log8_function    = takum_log8_10_raised,
		.takum_log16_function   = takum_log16_10_raised,
		.takum_log32_function   = takum_log32_10_raised,
		.takum_log64_function   = takum_log64_10_raised,
	},
};

long double
ten_raised_minus_1_reference(long double a)
{
	return powl(10.0L, a) - 1.0L;
}

static const struct unit_test_block ten_raised_minus_1_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "10_raised_minus_1",
	.data.takum_takum = {
		.reference_function = ten_raised_minus_1_reference,
		.takum8_function    = takum8_10_raised_minus_1,
		.takum16_function   = takum16_10_raised_minus_1,
		.takum32_function   = takum32_10_raised_minus_1,
		.takum64_function   = takum64_10_raised_minus_1,
		.takum_log8_function    = takum_log8_10_raised_minus_1,
		.takum_log16_function   = takum_log16_10_raised_minus_1,
		.takum_log32_function   = takum_log32_10_raised_minus_1,
		.takum_log64_function   = takum_log64_10_raised_minus_1,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&ten_raised_utb) +
	       run_unit_test_block(&ten_raised_minus_1_utb);
}
