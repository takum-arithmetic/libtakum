/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arctan2_reference(long double a, long double b)
{
	return atan2l(a, b);
}

static const struct unit_test_block arctan2_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM,
	.function_name = "arctan2",
	.data.takum_takum_takum = {
		.reference_function = arctan2_reference,
		.takum8_function    = takum8_arctan2,
		.takum16_function   = takum16_arctan2,
		.takum32_function   = takum32_arctan2,
		.takum64_function   = takum64_arctan2,
		.takum_log8_function    = takum_log8_arctan2,
		.takum_log16_function   = takum_log16_arctan2,
		.takum_log32_function   = takum_log32_arctan2,
		.takum_log64_function   = takum_log64_arctan2,
	},
};

long double
arctan2_over_pi_reference(long double a, long double b)
{
	return atan2l(a, b) / PI;
}

static const struct unit_test_block arctan2_over_pi_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM,
	.function_name = "arctan2_over_pi",
	.data.takum_takum_takum = {
		.reference_function = arctan2_over_pi_reference,
		.takum8_function    = takum8_arctan2_over_pi,
		.takum16_function   = takum16_arctan2_over_pi,
		.takum32_function   = takum32_arctan2_over_pi,
		.takum64_function   = takum64_arctan2_over_pi,
		.takum_log8_function    = takum_log8_arctan2_over_pi,
		.takum_log16_function   = takum_log16_arctan2_over_pi,
		.takum_log32_function   = takum_log32_arctan2_over_pi,
		.takum_log64_function   = takum_log64_arctan2_over_pi,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arctan2_utb) +
	       run_unit_test_block(&arctan2_over_pi_utb);
}
