/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

static long double
csch_reference(long double a)
{
	return 1.0l / sinhl(a);
}

static const struct unit_test_block csch_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "csch",
	.data.takum_takum = {
		.reference_function = csch_reference,
		.takum8_function    = takum8_csch,
		.takum16_function   = takum16_csch,
		.takum32_function   = takum32_csch,
		.takum64_function   = takum64_csch,
		.takum_log8_function    = takum_log8_csch,
		.takum_log16_function   = takum_log16_csch,
		.takum_log32_function   = takum_log32_csch,
		.takum_log64_function   = takum_log64_csch,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&csch_utb);
}
