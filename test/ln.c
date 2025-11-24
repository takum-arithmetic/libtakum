/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
ln_reference(long double a)
{
	return logl(a);
}

static const struct unit_test_block ln_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "ln",
	.data.takum_takum = {
		.reference_function = ln_reference,
		.takum8_function    = takum8_ln,
		.takum16_function   = takum16_ln,
		.takum32_function   = takum32_ln,
		.takum64_function   = takum64_ln,
		.takum_log8_function    = takum_log8_ln,
		.takum_log16_function   = takum_log16_ln,
		.takum_log32_function   = takum_log32_ln,
		.takum_log64_function   = takum_log64_ln,
	},
};

long double
ln_1_plus_reference(long double a)
{
	return log1pl(a);
}

static const struct unit_test_block ln_1_plus_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "ln_1_plus",
	.data.takum_takum = {
		.reference_function = ln_1_plus_reference,
		.takum8_function    = takum8_ln_1_plus,
		.takum16_function   = takum16_ln_1_plus,
		.takum32_function   = takum32_ln_1_plus,
		.takum64_function   = takum64_ln_1_plus,
		.takum_log8_function    = takum_log8_ln_1_plus,
		.takum_log16_function   = takum_log16_ln_1_plus,
		.takum_log32_function   = takum_log32_ln_1_plus,
		.takum_log64_function   = takum_log64_ln_1_plus,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&ln_utb) +
	       run_unit_test_block(&ln_1_plus_utb);
}
