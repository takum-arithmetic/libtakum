/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arsinh_reference(long double a)
{
	return asinhl(a);
}

static const struct unit_test_block arsinh_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arsinh",
	.data.takum_takum = {
		.reference_function = arsinh_reference,
		.takum8_function    = takum8_arsinh,
		.takum16_function   = takum16_arsinh,
		.takum32_function   = takum32_arsinh,
		.takum64_function   = takum64_arsinh,
		.takum_log8_function    = takum_log8_arsinh,
		.takum_log16_function   = takum_log16_arsinh,
		.takum_log32_function   = takum_log32_arsinh,
		.takum_log64_function   = takum_log64_arsinh,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arsinh_utb);
}
