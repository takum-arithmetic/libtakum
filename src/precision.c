/* See LICENSE file for copyright and license details. */
#include <stdint.h>

#include "../takum.h"

#include "util.h"

/*
 * This 16 byte LUT maps (D R2 R1 R0) interpreted as a 4-bit
 * unsigned integer to the mantissa bit count p = 16 - r - 5 = 11 - r
 * of the first 16 bit fragment
 */
static const uint8_t p_lut[] = {
	[0] = 4,  /* 0 000 → D=0, r=7 */
	[1] = 5,  /* 0 001 → D=0, r=6 */
	[2] = 6,  /* 0 010 → D=0, r=5 */
	[3] = 7,  /* 0 011 → D=0, r=4 */
	[4] = 8,  /* 0 100 → D=0, r=3 */
	[5] = 9,  /* 0 101 → D=0, r=2 */
	[6] = 10, /* 0 110 → D=0, r=1 */
	[7] = 11, /* 0 111 → D=0, r=0 */
	[8] = 11, /* 1 000 → D=1, r=0 */
	[9] = 10, /* 1 001 → D=1, r=1 */
	[10] = 9, /* 1 010 → D=1, r=2 */
	[11] = 8, /* 1 011 → D=1, r=3 */
	[12] = 7, /* 1 100 → D=1, r=4 */
	[13] = 6, /* 1 101 → D=1, r=5 */
	[14] = 5, /* 1 110 → D=1, r=6 */
	[15] = 4, /* 1 111 → D=1, r=7 */
};

uint8_t
takum8_precision(takum8 t)
{
	const union util_takum8_union in = {
		.value = t,
	};
	uint_fast8_t DR;

	if (t == 0 || t == TAKUM8_NAR) {
		/* return the worst case precision n - 12 = 0 */
		return 0;
	} else {
		/* Extract (D R2 R1 R0) */
		DR = (in.bits & UINT8_C(0x78)) >> 3;

		/*
		 * p_lut contains the precision for the 16 bit fragment,
		 * subtract 8 or clamp to zero if we are already below 8
		 */
		return (p_lut[DR] < 8) ? 0 : p_lut[DR] - 8;
	}
}

uint8_t
takum16_precision(takum16 t)
{
	const union util_takum16_union in = {
		.value = t,
	};
	uint_fast8_t DR;

	if (t == 0 || t == TAKUM16_NAR) {
		/* return the worst case precision n - 12 = 4 */
		return 4;
	} else {
		/* Extract (D R2 R1 R0) */
		DR = (in.bits & UINT16_C(0x7800)) >> 11;

		/*
		 * p contains the precision for the 16 bit fragment
		 */
		return p_lut[DR];
	}
}

uint8_t
takum32_precision(takum32 t)
{
	const union util_takum32_union in = {
		.value = t,
	};
	uint_fast8_t DR;

	if (t == 0 || t == TAKUM32_NAR) {
		/* return the worst case precision n - 12 = 20 */
		return 20;
	} else {
		/* Extract (D R2 R1 R0) */
		DR = (in.bits & UINT32_C(0x78000000)) >> 27;

		/*
		 * p contains the precision for the 16 bit fragment,
		 * add 16
		 */
		return p_lut[DR] + 16;
	}
}

uint8_t
takum64_precision(takum64 t)
{
	const union util_takum64_union in = {
		.value = t,
	};
	uint_fast8_t DR;

	if (t == 0 || t == TAKUM64_NAR) {
		/* return the worst case precision n - 12 = 52 */
		return 52;
	} else {
		/* Extract (D R2 R1 R0) */
		DR = (in.bits & UINT64_C(0x7800000000000000)) >> 59;

		/*
		 * p contains the precision for the 16 bit fragment,
		 * add 48
		 */
		return p_lut[DR] + 48;
	}
}

uint8_t
takum_log8_precision(takum_log8 t)
{
	/* linear and (logarithmic) takums don't differ here */
	return takum8_precision((takum8)t);
}

uint8_t
takum_log16_precision(takum_log16 t)
{
	/* linear and (logarithmic) takums don't differ here */
	return takum16_precision((takum16)t);
}

uint8_t
takum_log32_precision(takum_log32 t)
{
	/* linear and (logarithmic) takums don't differ here */
	return takum32_precision((takum32)t);
}

uint8_t
takum_log64_precision(takum_log64 t)
{
	/* linear and (logarithmic) takums don't differ here */
	return takum64_precision((takum64)t);
}
