/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
square_root_reference(long double a)
{
	return sqrtl(a);
}

static const struct unit_test_block square_root_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "square_root",
	.data.takum_takum = {
		.reference_function = square_root_reference,
		.takum8_function    = takum8_square_root,
		.takum16_function   = takum16_square_root,
		.takum32_function   = takum32_square_root,
		.takum64_function   = takum64_square_root,
		.takum_log8_function    = takum_log8_square_root,
		.takum_log16_function   = takum_log16_square_root,
		.takum_log32_function   = takum_log32_square_root,
		.takum_log64_function   = takum_log64_square_root,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&square_root_utb);
}
