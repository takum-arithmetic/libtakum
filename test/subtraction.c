/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
subtraction_reference(long double a, long double b)
{
	return a - b;
}

static const struct unit_test_block subtraction_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM,
	.function_name = "subtraction",
	.data.takum_takum_takum = {
		.reference_function = subtraction_reference,
		.takum8_function    = takum8_subtraction,
		.takum16_function   = takum16_subtraction,
		.takum32_function   = takum32_subtraction,
		.takum64_function   = takum64_subtraction,
		.takum_log8_function    = takum_log8_subtraction,
		.takum_log16_function   = takum_log16_subtraction,
		.takum_log32_function   = takum_log32_subtraction,
		.takum_log64_function   = takum_log64_subtraction,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&subtraction_utb);
}
