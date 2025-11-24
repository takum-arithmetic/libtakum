/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
cos_reference(long double a)
{
	return cosl(a);
}

static const struct unit_test_block cos_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "cos",
	.data.takum_takum = {
		.reference_function = cos_reference,
		.takum8_function    = takum8_cos,
		.takum16_function   = takum16_cos,
		.takum32_function   = takum32_cos,
		.takum64_function   = takum64_cos,
		.takum_log8_function    = takum_log8_cos,
		.takum_log16_function   = takum_log16_cos,
		.takum_log32_function   = takum_log32_cos,
		.takum_log64_function   = takum_log64_cos,

	},
};

long double
cos_pi_times_reference(long double a)
{
	long double a_mod_2;

	a_mod_2 = fmodl(a, 2.0l);

	if (a_mod_2 == 0.0l) {
		return 1.0l;
	} else if (a_mod_2 == 0.5l) {
		return 0.0l;
	} else if (a_mod_2 == 1.0l) {
		return -1.0l;
	} else if (a_mod_2 == 1.5l) {
		return 0.0l;
	} else {
		return cosl(PI * a);
	}
}

static const struct unit_test_block cos_pi_times_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "cos_pi_times",
	.data.takum_takum = {
		.reference_function = cos_pi_times_reference,
		.takum8_function    = takum8_cos_pi_times,
		.takum16_function   = takum16_cos_pi_times,
		.takum32_function   = takum32_cos_pi_times,
		.takum64_function   = takum64_cos_pi_times,
		.takum_log8_function    = takum_log8_cos_pi_times,
		.takum_log16_function   = takum_log16_cos_pi_times,
		.takum_log32_function   = takum_log32_cos_pi_times,
		.takum_log64_function   = takum_log64_cos_pi_times,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&cos_utb) +
	       run_unit_test_block(&cos_pi_times_utb);
}
