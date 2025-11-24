/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arsech_reference(long double a)
{
	return acoshl(1.0l / a);
}

static const struct unit_test_block arsech_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arsech",
	.data.takum_takum = {
		.reference_function = arsech_reference,
		.takum8_function    = takum8_arsech,
		.takum16_function   = takum16_arsech,
		.takum32_function   = takum32_arsech,
		.takum64_function   = takum64_arsech,
		.takum_log8_function    = takum_log8_arsech,
		.takum_log16_function   = takum_log16_arsech,
		.takum_log32_function   = takum_log32_arsech,
		.takum_log64_function   = takum_log64_arsech,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arsech_utb);
}
