/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
addition_reference(long double a, long double b)
{
	return a + b;
}

static const struct unit_test_block addition_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM,
	.function_name = "addition",
	.data.takum_takum_takum = {
		.reference_function = addition_reference,
		.takum8_function    = takum8_addition,
		.takum16_function   = takum16_addition,
		.takum32_function   = takum32_addition,
		.takum64_function   = takum64_addition,
		.takum_log8_function    = takum_log8_addition,
		.takum_log16_function   = takum_log16_addition,
		.takum_log32_function   = takum_log32_addition,
		.takum_log64_function   = takum_log64_addition,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&addition_utb);
}
