/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arctan_reference(long double a)
{
	return atanl(a);
}

static const struct unit_test_block arctan_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arctan",
	.data.takum_takum = {
		.reference_function = arctan_reference,
		.takum8_function    = takum8_arctan,
		.takum16_function   = takum16_arctan,
		.takum32_function   = takum32_arctan,
		.takum64_function   = takum64_arctan,
		.takum_log8_function    = takum_log8_arctan,
		.takum_log16_function   = takum_log16_arctan,
		.takum_log32_function   = takum_log32_arctan,
		.takum_log64_function   = takum_log64_arctan,
	},
};

long double
arctan_over_pi_reference(long double a)
{
	return atanl(a) / PI;
}

static const struct unit_test_block arctan_over_pi_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arctan_over_pi",
	.data.takum_takum = {
		.reference_function = arctan_over_pi_reference,
		.takum8_function    = takum8_arctan_over_pi,
		.takum16_function   = takum16_arctan_over_pi,
		.takum32_function   = takum32_arctan_over_pi,
		.takum64_function   = takum64_arctan_over_pi,
		.takum_log8_function    = takum_log8_arctan_over_pi,
		.takum_log16_function   = takum_log16_arctan_over_pi,
		.takum_log32_function   = takum_log32_arctan_over_pi,
		.takum_log64_function   = takum_log64_arctan_over_pi,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arctan_utb) +
	       run_unit_test_block(&arctan_over_pi_utb);
}
