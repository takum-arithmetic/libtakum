/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arcoth_reference(long double a)
{
	return atanh(1.0L / a);
}

static const struct unit_test_block arcoth_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arcoth",
	.data.takum_takum = {
		.reference_function = arcoth_reference,
		.takum8_function    = takum8_arcoth,
		.takum16_function   = takum16_arcoth,
		.takum32_function   = takum32_arcoth,
		.takum64_function   = takum64_arcoth,
		.takum_log8_function    = takum_log8_arcoth,
		.takum_log16_function   = takum_log16_arcoth,
		.takum_log32_function   = takum_log32_arcoth,
		.takum_log64_function   = takum_log64_arcoth,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arcoth_utb);
}
