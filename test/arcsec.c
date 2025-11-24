/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>

long double
arcsec_reference(long double a)
{
	return acosl(1.0L / a);
}

static const struct unit_test_block arcsec_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arcsec",
	.data.takum_takum = {
		.reference_function = arcsec_reference,
		.takum8_function    = takum8_arcsec,
		.takum16_function   = takum16_arcsec,
		.takum32_function   = takum32_arcsec,
		.takum64_function   = takum64_arcsec,
		.takum_log8_function    = takum_log8_arcsec,
		.takum_log16_function   = takum_log16_arcsec,
		.takum_log32_function   = takum_log32_arcsec,
		.takum_log64_function   = takum_log64_arcsec,
	},
};

long double
arcsec_over_pi_reference(long double a)
{
	return acosl(1.0L / a) / PI;
}

static const struct unit_test_block arcsec_over_pi_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM,
	.function_name = "arcsec_over_pi",
	.data.takum_takum = {
		.reference_function = arcsec_over_pi_reference,
		.takum8_function    = takum8_arcsec_over_pi,
		.takum16_function   = takum16_arcsec_over_pi,
		.takum32_function   = takum32_arcsec_over_pi,
		.takum64_function   = takum64_arcsec_over_pi,
		.takum_log8_function    = takum_log8_arcsec_over_pi,
		.takum_log16_function   = takum_log16_arcsec_over_pi,
		.takum_log32_function   = takum_log32_arcsec_over_pi,
		.takum_log64_function   = takum_log64_arcsec_over_pi,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&arcsec_utb) +
	       run_unit_test_block(&arcsec_over_pi_utb);
}
