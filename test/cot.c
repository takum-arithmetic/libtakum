/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
cot_reference(long double a)
{
	return 1.0l / tanl(a);
}

static const struct unit_test_block cot_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "cot",
	.data.takum_takum = {
		.reference_function = cot_reference,
		.takum8_function    = takum8_cot,
		.takum16_function   = takum16_cot,
		.takum32_function   = takum32_cot,
		.takum64_function   = takum64_cot,
		.takum_log8_function    = takum_log8_cot,
		.takum_log16_function   = takum_log16_cot,
		.takum_log32_function   = takum_log32_cot,
		.takum_log64_function   = takum_log64_cot,
	},
};

long double
cot_pi_times_reference(long double a)
{
	long double a_mod_1;

	a_mod_1 = fmodl(a, 1.0l);

	if (a_mod_1 == 0.0l) {
		return NAN;
	} else if (a_mod_1 == 0.5) {
		return 0.0;
	} else {
		return cot_reference(PI * a);
	}
}

static const struct unit_test_block cot_pi_times_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "cot_pi_times",
	.data.takum_takum = {
		.reference_function = cot_pi_times_reference,
		.takum8_function    = takum8_cot_pi_times,
		.takum16_function   = takum16_cot_pi_times,
		.takum32_function   = takum32_cot_pi_times,
		.takum64_function   = takum64_cot_pi_times,
		.takum_log8_function    = takum_log8_cot_pi_times,
		.takum_log16_function   = takum_log16_cot_pi_times,
		.takum_log32_function   = takum_log32_cot_pi_times,
		.takum_log64_function   = takum_log64_cot_pi_times,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&cot_utb) +
	       run_unit_test_block(&cot_pi_times_utb);
}
