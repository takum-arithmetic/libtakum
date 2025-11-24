/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
tanh_reference(long double a)
{
	return tanhl(a);
}

static const struct unit_test_block tanh_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "tanh",
	.data.takum_takum = {
		.reference_function = tanh_reference,
		.takum8_function    = takum8_tanh,
		.takum16_function   = takum16_tanh,
		.takum32_function   = takum32_tanh,
		.takum64_function   = takum64_tanh,
		.takum_log8_function    = takum_log8_tanh,
		.takum_log16_function   = takum_log16_tanh,
		.takum_log32_function   = takum_log32_tanh,
		.takum_log64_function   = takum_log64_tanh,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&tanh_utb);
}
