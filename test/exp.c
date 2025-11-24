/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
exp_reference(long double a)
{
	return expl(a);
}

static const struct unit_test_block exp_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "exp",
	.data.takum_takum = {
		.reference_function = exp_reference,
		.takum8_function    = takum8_exp,
		.takum16_function   = takum16_exp,
		.takum32_function   = takum32_exp,
		.takum64_function   = takum64_exp,
		.takum_log8_function    = takum_log8_exp,
		.takum_log16_function   = takum_log16_exp,
		.takum_log32_function   = takum_log32_exp,
		.takum_log64_function   = takum_log64_exp,
	},
};

long double
exp_minus_1_reference(long double a)
{
	return expm1l(a);
}

static const struct unit_test_block exp_minus_1_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "exp_minus_1",
	.data.takum_takum = {
		.reference_function = exp_minus_1_reference,
		.takum8_function    = takum8_exp_minus_1,
		.takum16_function   = takum16_exp_minus_1,
		.takum32_function   = takum32_exp_minus_1,
		.takum64_function   = takum64_exp_minus_1,
		.takum_log8_function    = takum_log8_exp_minus_1,
		.takum_log16_function   = takum_log16_exp_minus_1,
		.takum_log32_function   = takum_log32_exp_minus_1,
		.takum_log64_function   = takum_log64_exp_minus_1,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&exp_utb) +
	       run_unit_test_block(&exp_minus_1_utb);
}
