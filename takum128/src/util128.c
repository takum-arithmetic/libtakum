/* See LICENSE file for copyright and license details. */
#include <stdint.h>

#include "util128.h"

/*
 * See util_round_uint64_to_number_of_bits in ../../src/util.c for the
 * bit-diagram and rationale; this is the same algorithm widened to
 * unsigned __int128, with UINT128_C(1)-style literals replaced by plain
 * casts since C has no standard 128-bit integer literal suffix.
 */
unsigned __int128
util_round_uint128_to_number_of_bits(unsigned __int128 input,
                                     uint8_t number_of_bits)
{
	int rounding_bit, is_tied;
	unsigned __int128 rounding_bit_mask, filter_mask, result;

	rounding_bit_mask = ((unsigned __int128)1)
	                    << (128 - number_of_bits - 1);
	rounding_bit = ((input & rounding_bit_mask) != 0);

	filter_mask = (((unsigned __int128)1) << (128 - number_of_bits)) - 1;
	is_tied = ((input & filter_mask) == rounding_bit_mask);

	result = input >> (128 - number_of_bits);

	result += rounding_bit && (!is_tied || (result % 2 == 1));

	return result;
}
