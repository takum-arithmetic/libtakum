/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
lg_reference(long double a)
{
	return log10l(a);
}

static const struct unit_test_block lg_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "lg",
	.data.takum_takum = {
		.reference_function = lg_reference,
		.takum8_function    = takum8_lg,
		.takum16_function   = takum16_lg,
		.takum32_function   = takum32_lg,
		.takum64_function   = takum64_lg,
		.takum_log8_function    = takum_log8_lg,
		.takum_log16_function   = takum_log16_lg,
		.takum_log32_function   = takum_log32_lg,
		.takum_log64_function   = takum_log64_lg,
	},
};

long double
lg_1_plus_reference(long double a)
{
	return LG_E * log1pl(a);
}

static const struct unit_test_block lg_1_plus_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "lg_1_plus",
	.data.takum_takum = {
		.reference_function = lg_1_plus_reference,
		.takum8_function    = takum8_lg_1_plus,
		.takum16_function   = takum16_lg_1_plus,
		.takum32_function   = takum32_lg_1_plus,
		.takum64_function   = takum64_lg_1_plus,
		.takum_log8_function    = takum_log8_lg_1_plus,
		.takum_log16_function   = takum_log16_lg_1_plus,
		.takum_log32_function   = takum_log32_lg_1_plus,
		.takum_log64_function   = takum_log64_lg_1_plus,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&lg_utb) +
	       run_unit_test_block(&lg_1_plus_utb);
}
