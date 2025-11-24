/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
tan_reference(long double a)
{
	return tanl(a);
}

static const struct unit_test_block tan_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "tan",
	.data.takum_takum = {
		.reference_function = tan_reference,
		.takum8_function    = takum8_tan,
		.takum16_function   = takum16_tan,
		.takum32_function   = takum32_tan,
		.takum64_function   = takum64_tan,
		.takum_log8_function    = takum_log8_tan,
		.takum_log16_function   = takum_log16_tan,
		.takum_log32_function   = takum_log32_tan,
		.takum_log64_function   = takum_log64_tan,
	},
};

long double
tan_pi_times_reference(long double a)
{
	long double a_mod_1;

	a_mod_1 = fmodl(a, 1.0l);

	if (a_mod_1 == 0.0l) {
		return 0.0;
	} else if (a_mod_1 == 0.5) {
		return NAN;
	} else {
		return tan_reference(PI * a);
	}
}

static const struct unit_test_block tan_pi_times_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "tan_pi_times",
	.data.takum_takum = {
		.reference_function = tan_pi_times_reference,
		.takum8_function    = takum8_tan_pi_times,
		.takum16_function   = takum16_tan_pi_times,
		.takum32_function   = takum32_tan_pi_times,
		.takum64_function   = takum64_tan_pi_times,
		.takum_log8_function    = takum_log8_tan_pi_times,
		.takum_log16_function   = takum_log16_tan_pi_times,
		.takum_log32_function   = takum_log32_tan_pi_times,
		.takum_log64_function   = takum_log64_tan_pi_times,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&tan_utb) +
	       run_unit_test_block(&tan_pi_times_utb);
}
