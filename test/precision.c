/* See LICENSE file for copyright and license details. */
#include "../takum.h"
#include "util.h"

#include <math.h>
#include <stdint.h>
#include <sys/types.h>

uint8_t
precision_reference(long double a, enum takum_type takum_type)
{
	if (!isfinite(a) || a == 0.0L) {
		/* return worst case precision n - 12 */
		if (takum_type_parameters[takum_type].n < 12) {
			return 0;
		} else {
			return takum_type_parameters[takum_type].n - 12;
		}
	} else {
		union util_takum64_union t = { 0 };
		uint16_t prefix;
		uint8_t R, r;

		/* obtain the clean takum from the long double in the
		 * native type, then shift it such that the highest 16
		 * bits are the prefix, yielding a 64-bit takum */
		switch (takum_type) {
		case TAKUM8:
			t.value = (int64_t)takum8_from_extended_float(a);
			t.bits <<= 56;
			break;
		case TAKUM16:
			t.value = (int64_t)takum16_from_extended_float(a);
			t.bits <<= 48;
			break;
		case TAKUM32:
			t.value = (int64_t)takum32_from_extended_float(a);
			t.bits <<= 32;
			break;
		case TAKUM64:
			t.value = (int64_t)takum64_from_extended_float(a);
			break;
		case TAKUM_LOG8:
			t.value = (int64_t)takum_log8_from_extended_float(a);
			t.bits <<= 56;
			break;
		case TAKUM_LOG16:
			t.value = (int64_t)takum_log16_from_extended_float(a);
			t.bits <<= 48;
			break;
		case TAKUM_LOG32:
			t.value = (int64_t)takum_log32_from_extended_float(a);
			t.bits <<= 32;
			break;
		case TAKUM_LOG64:
			t.value = (int64_t)takum_log64_from_extended_float(a);
			break;
		}

		/* get the prefix */
		prefix = (t.bits >> 48) & 0xffff;

		/* get the regime bits */
		R = (prefix & 0x3800) >> 11;

		/* get the regime depending on D */
		r = (prefix & 0x4000) ? R : 7 - R;

		/* compute final result */
		if (r > takum_type_parameters[takum_type].n - 5) {
			return 0;
		} else {
			return takum_type_parameters[takum_type].n - 5 - r;
		}
	}
}

static const struct unit_test_block precision_utb = {
	.type = UNIT_TEST_BLOCK_TYPE_TAKUM_UINT8,
	.function_name = "precision",
	.data.takum_uint8 = {
		.reference_function = precision_reference,
		.takum8_function    = takum8_precision,
		.takum16_function   = takum16_precision,
		.takum32_function   = takum32_precision,
		.takum64_function   = takum64_precision,
		.takum_log8_function    = takum_log8_precision,
		.takum_log16_function   = takum_log16_precision,
		.takum_log32_function   = takum_log32_precision,
		.takum_log64_function   = takum_log64_precision,
	},
};

int
main(int argc, char *argv[])
{
	(void)argc;
	argv0 = argv[0];

	return run_unit_test_block(&precision_utb);
}
