/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arccsc_reference(long double a)
{
	return asinl(1.0L / a);
}

static const struct unit_test_block arccsc_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arccsc",
	.data.takum_takum = {
		.reference_function = arccsc_reference,
		.takum8_function    = takum8_arccsc,
		.takum16_function   = takum16_arccsc,
		.takum32_function   = takum32_arccsc,
		.takum64_function   = takum64_arccsc,
		.takum_log8_function    = takum_log8_arccsc,
		.takum_log16_function   = takum_log16_arccsc,
		.takum_log32_function   = takum_log32_arccsc,
		.takum_log64_function   = takum_log64_arccsc,
	},
};

long double
arccsc_over_pi_reference(long double a)
{
	return asinl(1.0L / a) / PI;
}

static const struct unit_test_block arccsc_over_pi_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arccsc_over_pi",
	.data.takum_takum = {
		.reference_function = arccsc_over_pi_reference,
		.takum8_function    = takum8_arccsc_over_pi,
		.takum16_function   = takum16_arccsc_over_pi,
		.takum32_function   = takum32_arccsc_over_pi,
		.takum64_function   = takum64_arccsc_over_pi,
		.takum_log8_function    = takum_log8_arccsc_over_pi,
		.takum_log16_function   = takum_log16_arccsc_over_pi,
		.takum_log32_function   = takum_log32_arccsc_over_pi,
		.takum_log64_function   = takum_log64_arccsc_over_pi,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arccsc_utb) +
	       run_unit_test_block(&arccsc_over_pi_utb);
}
