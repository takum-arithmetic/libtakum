/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
sec_reference(long double a)
{
	return 1.0L / cosl(a);
}

static const struct unit_test_block sec_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "sec",
	.data.takum_takum = {
		.reference_function = sec_reference,
		.takum8_function    = takum8_sec,
		.takum16_function   = takum16_sec,
		.takum32_function   = takum32_sec,
		.takum64_function   = takum64_sec,
		.takum_log8_function    = takum_log8_sec,
		.takum_log16_function   = takum_log16_sec,
		.takum_log32_function   = takum_log32_sec,
		.takum_log64_function   = takum_log64_sec,
	},
};

long double
sec_pi_times_reference(long double a)
{
	long double a_mod_2;

	a_mod_2 = fmodl(a, 2.0l);

	if (a_mod_2 == 0.0l) {
		return 1.0l;
	} else if (a_mod_2 == 0.5l) {
		return NAN;
	} else if (a_mod_2 == 1.0l) {
		return -1.0l;
	} else if (a_mod_2 == 1.5l) {
		return NAN;
	} else {
		return sec_reference(PI * a);
	}
}

static const struct unit_test_block sec_pi_times_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "sec_pi_times",
	.data.takum_takum = {
		.reference_function = sec_pi_times_reference,
		.takum8_function    = takum8_sec_pi_times,
		.takum16_function   = takum16_sec_pi_times,
		.takum32_function   = takum32_sec_pi_times,
		.takum64_function   = takum64_sec_pi_times,
		.takum_log8_function    = takum_log8_sec_pi_times,
		.takum_log16_function   = takum_log16_sec_pi_times,
		.takum_log32_function   = takum_log32_sec_pi_times,
		.takum_log64_function   = takum_log64_sec_pi_times,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&sec_utb) +
	       run_unit_test_block(&sec_pi_times_utb);
}
