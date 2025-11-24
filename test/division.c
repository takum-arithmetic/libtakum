/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
division_reference(long double a, long double b)
{
	return a / b;
}

static const struct unit_test_block division_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM,
	.function_name = "division",
	.data.takum_takum_takum = {
		.reference_function = division_reference,
		.takum8_function    = takum8_division,
		.takum16_function   = takum16_division,
		.takum32_function   = takum32_division,
		.takum64_function   = takum64_division,
		.takum_log8_function    = takum_log8_division,
		.takum_log16_function   = takum_log16_division,
		.takum_log32_function   = takum_log32_division,
		.takum_log64_function   = takum_log64_division,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&division_utb);
}
