/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
absolute_reference(long double a)
{
	if (isfinite(a)) {
		return (a < 0) ? -a : a;
	} else {
		return NAN;
	}
}

static const struct unit_test_block absolute_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "absolute",
	.data.takum_takum = {
		.reference_function = absolute_reference,
		.takum8_function    = takum8_absolute,
		.takum16_function   = takum16_absolute,
		.takum32_function   = takum32_absolute,
		.takum64_function   = takum64_absolute,
		.takum_log8_function    = takum_log8_absolute,
		.takum_log16_function   = takum_log16_absolute,
		.takum_log32_function   = takum_log32_absolute,
		.takum_log64_function   = takum_log64_absolute,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&absolute_utb);
}
