/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
coth_reference(long double a)
{
	return 1.0L / tanhl(a);
}

static const struct unit_test_block coth_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "coth",
	.data.takum_takum = {
		.reference_function = coth_reference,
		.takum8_function    = takum8_coth,
		.takum16_function   = takum16_coth,
		.takum32_function   = takum32_coth,
		.takum64_function   = takum64_coth,
		.takum_log8_function    = takum_log8_coth,
		.takum_log16_function   = takum_log16_coth,
		.takum_log32_function   = takum_log32_coth,
		.takum_log64_function   = takum_log64_coth,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&coth_utb);
}
