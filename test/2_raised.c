/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
two_raised_reference(long double a)
{
	return exp2l(a);
}

static const struct unit_test_block two_raised_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "2_raised",
	.data.takum_takum = {
		.reference_function = two_raised_reference,
		.takum8_function    = takum8_2_raised,
		.takum16_function   = takum16_2_raised,
		.takum32_function   = takum32_2_raised,
		.takum64_function   = takum64_2_raised,
		.takum_log8_function    = takum_log8_2_raised,
		.takum_log16_function   = takum_log16_2_raised,
		.takum_log32_function   = takum_log32_2_raised,
		.takum_log64_function   = takum_log64_2_raised,
	},
};

long double
two_raised_minus_1_reference(long double a)
{
	return exp2l(a) - 1.0L;
}

static const struct unit_test_block two_raised_minus_1_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "2_raised_minus_1",
	.data.takum_takum = {
		.reference_function = two_raised_minus_1_reference,
		.takum8_function    = takum8_2_raised_minus_1,
		.takum16_function   = takum16_2_raised_minus_1,
		.takum32_function   = takum32_2_raised_minus_1,
		.takum64_function   = takum64_2_raised_minus_1,
		.takum_log8_function    = takum_log8_2_raised_minus_1,
		.takum_log16_function   = takum_log16_2_raised_minus_1,
		.takum_log32_function   = takum_log32_2_raised_minus_1,
		.takum_log64_function   = takum_log64_2_raised_minus_1,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&two_raised_utb) +
	       run_unit_test_block(&two_raised_minus_1_utb);
}
