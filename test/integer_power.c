/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>
#include <stdint.h>

long double
integer_power_reference(long double a, int64_t b)
{
	if (isnan(a) || (a == 0.0 && b == 0)) {
		return NAN;
	} else {
		return powl(a, (long double)b);
	}
}

static const int64_t integer_test_cases[] = {
	-100, -10, -1, 0, 1, 10, 100,
};

static const struct unit_test_block integer_power_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_INT64_TAKUM,
	.function_name = "integer_power",
	.data.takum_int64_takum = {
		.reference_function      = integer_power_reference,
		.takum8_function         = takum8_integer_power,
		.takum16_function        = takum16_integer_power,
		.takum32_function        = takum32_integer_power,
		.takum64_function        = takum64_integer_power,
		.takum_log8_function         = takum_log8_integer_power,
		.takum_log16_function        = takum_log16_integer_power,
		.takum_log32_function        = takum_log32_integer_power,
		.takum_log64_function        = takum_log64_integer_power,
		.integer_test_cases      = integer_test_cases,
		.integer_test_case_count = LEN(integer_test_cases),
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&integer_power_utb);
}
