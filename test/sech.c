/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
sech_reference(long double a)
{
	return 1.0L / coshl(a);
}

static const struct unit_test_block sech_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "sech",
	.data.takum_takum = {
		.reference_function = sech_reference,
		.takum8_function    = takum8_sech,
		.takum16_function   = takum16_sech,
		.takum32_function   = takum32_sech,
		.takum64_function   = takum64_sech,
		.takum_log8_function    = takum_log8_sech,
		.takum_log16_function   = takum_log16_sech,
		.takum_log32_function   = takum_log32_sech,
		.takum_log64_function   = takum_log64_sech,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&sech_utb);
}
