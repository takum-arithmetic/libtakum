/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arcosh_reference(long double a)
{
	return acoshl(a);
}

static const struct unit_test_block arcosh_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arcosh",
	.data.takum_takum = {
		.reference_function = arcosh_reference,
		.takum8_function    = takum8_arcosh,
		.takum16_function   = takum16_arcosh,
		.takum32_function   = takum32_arcosh,
		.takum64_function   = takum64_arcosh,
		.takum_log8_function    = takum_log8_arcosh,
		.takum_log16_function   = takum_log16_arcosh,
		.takum_log32_function   = takum_log32_arcosh,
		.takum_log64_function   = takum_log64_arcosh,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arcosh_utb);
}
