/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arccot_reference(long double a)
{
	if (a >= 0.0) {
		return atanl(1.0L / a);
	} else {
		return atanl(1.0L / a) + PI;
	}
}

static const struct unit_test_block arccot_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arccot",
	.data.takum_takum = {
		.reference_function = arccot_reference,
		.takum8_function    = takum8_arccot,
		.takum16_function   = takum16_arccot,
		.takum32_function   = takum32_arccot,
		.takum64_function   = takum64_arccot,
		.takum_log8_function    = takum_log8_arccot,
		.takum_log16_function   = takum_log16_arccot,
		.takum_log32_function   = takum_log32_arccot,
		.takum_log64_function   = takum_log64_arccot,
	},
};

long double
arccot_over_pi_reference(long double a)
{
	if (a >= 0.0) {
		return atanl(1.0L / a) / PI;
	} else {
		return atanl(1.0L / a) / PI + 1;
	}
}

static const struct unit_test_block arccot_over_pi_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arccot_over_pi",
	.data.takum_takum = {
		.reference_function = arccot_over_pi_reference,
		.takum8_function    = takum8_arccot_over_pi,
		.takum16_function   = takum16_arccot_over_pi,
		.takum32_function   = takum32_arccot_over_pi,
		.takum64_function   = takum64_arccot_over_pi,
		.takum_log8_function    = takum_log8_arccot_over_pi,
		.takum_log16_function   = takum_log16_arccot_over_pi,
		.takum_log32_function   = takum_log32_arccot_over_pi,
		.takum_log64_function   = takum_log64_arccot_over_pi,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arccot_utb) +
	       run_unit_test_block(&arccot_over_pi_utb);
}
