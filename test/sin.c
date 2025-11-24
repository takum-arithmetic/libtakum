/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
sin_reference(long double a)
{
	return sinl(a);
}

static const struct unit_test_block sin_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "sin",
	.data.takum_takum = {
		.reference_function = sin_reference,
		.takum8_function    = takum8_sin,
		.takum16_function   = takum16_sin,
		.takum32_function   = takum32_sin,
		.takum64_function   = takum64_sin,
		.takum_log8_function    = takum_log8_sin,
		.takum_log16_function   = takum_log16_sin,
		.takum_log32_function   = takum_log32_sin,
		.takum_log64_function   = takum_log64_sin,
	},
};

long double
sin_pi_times_reference(long double a)
{
	long double a_mod_2;

	a_mod_2 = fmodl(a, 2.0l);

	if (a_mod_2 == 0.0l) {
		return 0.0l;
	} else if (a_mod_2 == 0.5l) {
		return 1.0l;
	} else if (a_mod_2 == 1.0l) {
		return 0.0l;
	} else if (a_mod_2 == 1.5l) {
		return -1.0l;
	} else {
		return sinl(PI * a);
	}
}

static const struct unit_test_block sin_pi_times_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "sin_pi_times",
	.data.takum_takum = {
		.reference_function = sin_pi_times_reference,
		.takum8_function    = takum8_sin_pi_times,
		.takum16_function   = takum16_sin_pi_times,
		.takum32_function   = takum32_sin_pi_times,
		.takum64_function   = takum64_sin_pi_times,
		.takum_log8_function    = takum_log8_sin_pi_times,
		.takum_log16_function   = takum_log16_sin_pi_times,
		.takum_log32_function   = takum_log32_sin_pi_times,
		.takum_log64_function   = takum_log64_sin_pi_times,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&sin_utb) +
	       run_unit_test_block(&sin_pi_times_utb);
}
