/* See LICENSE file for copyright and license details. */
#include <stdint.h>

#include "../../takum128.h"

#include "util128.h"

/*
 * Byte-for-byte copy of the p_lut in ../../src/precision.c (and
 * codec128.c) -- the (D R2 R1 R0) -> fragment mantissa width mapping is
 * width-independent.
 */
static const uint8_t p_lut[] = {
	[0] = 4,  [1] = 5,  [2] = 6,  [3] = 7,  [4] = 8,  [5] = 9,
	[6] = 10, [7] = 11, [8] = 11, [9] = 10, [10] = 9, [11] = 8,
	[12] = 7, [13] = 6, [14] = 5, [15] = 4,
};

uint8_t
takum128_precision(takum128 t)
{
	const union util_takum128_union in = {
		.value = t,
	};
	uint_fast8_t DR;

	if (t == 0 || t == TAKUM128_NAR) {
		/* worst case precision n - 12 = 116 */
		return 116;
	} else {
		DR = (uint_fast8_t)((in.bits >> 123) & 0xf);

		return p_lut[DR] + TAKUM128_WIDTH_EXTRA;
	}
}

uint8_t
takum_log128_precision(takum_log128 t)
{
	/* linear and (logarithmic) takums don't differ here */
	return takum128_precision((takum128)t);
}
