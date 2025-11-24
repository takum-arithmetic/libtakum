/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arcsin_reference(long double a)
{
	return asinl(a);
}

static const struct unit_test_block arcsin_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arcsin",
	.data.takum_takum = {
		.reference_function = arcsin_reference,
		.takum8_function    = takum8_arcsin,
		.takum16_function   = takum16_arcsin,
		.takum32_function   = takum32_arcsin,
		.takum64_function   = takum64_arcsin,
		.takum_log8_function    = takum_log8_arcsin,
		.takum_log16_function   = takum_log16_arcsin,
		.takum_log32_function   = takum_log32_arcsin,
		.takum_log64_function   = takum_log64_arcsin,
	},
};

long double
arcsin_over_pi_reference(long double a)
{
	return asinl(a) / PI;
}

static const struct unit_test_block arcsin_over_pi_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arcsin_over_pi",
	.data.takum_takum = {
		.reference_function = arcsin_over_pi_reference,
		.takum8_function    = takum8_arcsin_over_pi,
		.takum16_function   = takum16_arcsin_over_pi,
		.takum32_function   = takum32_arcsin_over_pi,
		.takum64_function   = takum64_arcsin_over_pi,
		.takum_log8_function    = takum_log8_arcsin_over_pi,
		.takum_log16_function   = takum_log16_arcsin_over_pi,
		.takum_log32_function   = takum_log32_arcsin_over_pi,
		.takum_log64_function   = takum_log64_arcsin_over_pi,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arcsin_utb) +
	       run_unit_test_block(&arcsin_over_pi_utb);
}
