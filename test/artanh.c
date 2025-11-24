/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
artanh_reference(long double a)
{
	return atanhl(a);
}

static const struct unit_test_block artanh_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "artanh",
	.data.takum_takum = {
		.reference_function = artanh_reference,
		.takum8_function    = takum8_artanh,
		.takum16_function   = takum16_artanh,
		.takum32_function   = takum32_artanh,
		.takum64_function   = takum64_artanh,
		.takum_log8_function    = takum_log8_artanh,
		.takum_log16_function   = takum_log16_artanh,
		.takum_log32_function   = takum_log32_artanh,
		.takum_log64_function   = takum_log64_artanh,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&artanh_utb);
}
