/* See LICENSE file for copyright and license details. */
#include "../takum.h"

#include "util.h"

#include <fenv.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *argv0;

enum sampler_mode {
	SAMPLER_MODE_TAKUM_FULL,
	SAMPLER_MODE_TAKUM_RANDOM,
	SAMPLER_MODE_TAKUM_TAKUM_FULL,
	SAMPLER_MODE_TAKUM_TAKUM_RANDOM,
	SAMPLER_MODE_TAKUM_INT64_FULL,
	SAMPLER_MODE_TAKUM_INT64_RANDOM,
};

struct sampler {
	enum sampler_mode mode;
	enum takum_type takum_type;
	const struct unit_test_block *utb;
	int64_t value_x;
	int64_t value_y;
	uint64_t current_count;
	uint64_t target_count;
};

static int8_t
random_int8_next(int8_t previous_state)
{
	uint8_t feedback_bit;

	union {
		int8_t value;
		uint8_t bits;
	} state;

	/* Take our previous state as a starting point */
	state.value = previous_state;

	/*
	 * We will use a LFSR with feedback polynomial
	 * 	x⁸ + x⁶ + x⁵ + x⁴ + 1
	 * that has a period of 2^8-1.
	 */

	/*
	 * Check if the input state is zero, which an LFSR can neither
	 * handle nor output. We make use of this fact by defining a
	 * zero-state as the seed, which means that we cover all numbers
	 * in the uint8_t interval [0,2^8-1].
	 */
	if (state.bits == 0) {
		/* set our 'real' starting seed */
		state.bits = (uint8_t)rand();
	}

	/* Determine the feedback bit with the feedback polynomial */
	feedback_bit = ((state.bits >> 0) ^ (state.bits >> 2) ^
	                (state.bits >> 3) ^ (state.bits >> 4)) &
	               UINT8_C(1);

	/*
	 * Generate the next state by shifting one to the right and
	 * shifting 'in' the feedback bit from the left.
	 */
	state.bits = (feedback_bit << 7) | (state.bits >> 1);

	/* We actually want the signed value */
	return state.value;
}

static int16_t
random_int16_next(int16_t previous_state)
{
	uint16_t feedback_bit;

	union {
		int16_t value;
		uint16_t bits;
	} state;

	/* Take our previous state as a starting point */
	state.value = previous_state;

	/*
	 * We will use a LFSR with feedback polynomial
	 * 	x¹⁶ + x¹⁵ + x¹³ + x⁴ + 1
	 * that has a period of 2^16-1.
	 */

	/*
	 * Check if the input state is zero, which an LFSR can neither
	 * handle nor output. We make use of this fact by defining a
	 * zero-state as the seed, which means that we cover all numbers
	 * in the uint16_t interval [0,2^16-1].
	 */
	if (state.bits == 0) {
		/* set our 'real' starting seed */
		state.bits = (uint16_t)rand();
	}

	/* Determine the feedback bit with the feedback polynomial */
	feedback_bit = ((state.bits >> 0) ^ (state.bits >> 1) ^
	                (state.bits >> 3) ^ (state.bits >> 12)) &
	               UINT16_C(1);

	/*
	 * Generate the next state by shifting one to the right and
	 * shifting 'in' the feedback bit from the left.
	 */
	state.bits = (feedback_bit << (16 - 1)) | (state.bits >> 1);

	/* We actually want the signed value */
	return state.value;
}

static int32_t
random_int32_next(int32_t previous_state)
{
	uint32_t feedback_bit;

	union {
		int32_t value;
		uint32_t bits;
	} state;

	/* Take our previous state as a starting point */
	state.value = previous_state;

	/*
	 * We will use a LFSR with feedback polynomial
	 * 	x³² + x²² + x² + x¹ + 1
	 * that has a period of 2^32-1.
	 */

	/*
	 * Check if the input state is zero, which an LFSR can neither
	 * handle nor output. We make use of this fact by defining a
	 * zero-state as the seed, which means that we cover all numbers
	 * in the uint16_t interval [0,2^32-1].
	 */
	if (state.bits == 0) {
		/* set our 'real' starting seed */
		state.bits = (uint32_t)rand();
	}

	/* Determine the feedback bit with the feedback polynomial */
	feedback_bit = ((state.bits >> 0) ^ (state.bits >> 10) ^
	                (state.bits >> 30) ^ (state.bits >> 31)) &
	               UINT32_C(1);

	/*
	 * Generate the next state by shifting one to the right and
	 * shifting 'in' the feedback bit from the left.
	 */
	state.bits = (feedback_bit << (32 - 1)) | (state.bits >> 1);

	/* We actually want the signed value */
	return state.value;
}

static int64_t
random_int64_next(int64_t previous_state)
{
	uint64_t feedback_bit;

	union {
		int64_t value;
		uint64_t bits;
	} state;

	/* Take our previous state as a starting point */
	state.value = previous_state;

	/*
	 * We will use a LFSR with feedback polynomial
	 * 	x⁶⁴ + x⁶³ + x⁶¹ + x⁶⁰ + 1
	 * that has a period of 2^64-1.
	 */

	/*
	 * Check if the input state is zero, which an LFSR can neither
	 * handle nor output. We make use of this fact by defining a
	 * zero-state as the seed, which means that we cover all numbers
	 * in the uint16_t interval [0,2^64-1].
	 */
	if (state.bits == 0) {
		/* set our 'real' starting seed */
		state.bits = (uint64_t)rand();
	}

	/* Determine the feedback bit with the feedback polynomial */
	feedback_bit = ((state.bits >> 0) ^ (state.bits >> 1) ^
	                (state.bits >> 3) ^ (state.bits >> 4)) &
	               UINT32_C(1);

	/*
	 * Generate the next state by shifting one to the right and
	 * shifting 'in' the feedback bit from the left.
	 */
	state.bits = (feedback_bit << (64 - 1)) | (state.bits >> 1);

	/* We actually want the signed value */
	return state.value;
}

static int64_t
random_next(int64_t previous_state, enum takum_type takum_type)
{
	switch (takum_type) {
	case TAKUM8:
	case TAKUM_LOG8:
		return (int64_t)random_int8_next((int8_t)previous_state);
		break;
	case TAKUM16:
	case TAKUM_LOG16:
		return (int64_t)random_int16_next((int16_t)previous_state);
		break;
	case TAKUM32:
	case TAKUM_LOG32:
		return (int64_t)random_int32_next((int32_t)previous_state);
		break;
	case TAKUM64:
	case TAKUM_LOG64:
		return random_int64_next(previous_state);
		break;
	}

	return 0;
}

static long double
int64_takum8_to_extended_float(int64_t t)
{
	return takum8_to_extended_float((takum8)t);
}

static long double
int64_takum16_to_extended_float(int64_t t)
{
	return takum16_to_extended_float((takum16)t);
}

static long double
int64_takum32_to_extended_float(int64_t t)
{
	return takum32_to_extended_float((takum32)t);
}

static long double
int64_takum64_to_extended_float(int64_t t)
{
	return takum64_to_extended_float((takum64)t);
}

static long double
int64_takum_log8_to_extended_float(int64_t t)
{
	return takum_log8_to_extended_float((takum_log8)t);
}

static long double
int64_takum_log16_to_extended_float(int64_t t)
{
	return takum_log16_to_extended_float((takum_log16)t);
}

static long double
int64_takum_log32_to_extended_float(int64_t t)
{
	return takum_log32_to_extended_float((takum_log32)t);
}

static long double
int64_takum_log64_to_extended_float(int64_t t)
{
	return takum_log64_to_extended_float((takum_log64)t);
}

static int64_t
int64_takum8_from_extended_float(long double f)
{
	return (int64_t)takum8_from_extended_float(f);
}

static int64_t
int64_takum16_from_extended_float(long double f)
{
	return (int64_t)takum16_from_extended_float(f);
}

static int64_t
int64_takum32_from_extended_float(long double f)
{
	return (int64_t)takum32_from_extended_float(f);
}

static int64_t
int64_takum64_from_extended_float(long double f)
{
	return (int64_t)takum64_from_extended_float(f);
}

static int64_t
int64_takum_log8_from_extended_float(long double f)
{
	return (int64_t)takum_log8_from_extended_float(f);
}

static int64_t
int64_takum_log16_from_extended_float(long double f)
{
	return (int64_t)takum_log16_from_extended_float(f);
}

static int64_t
int64_takum_log32_from_extended_float(long double f)
{
	return (int64_t)takum_log32_from_extended_float(f);
}

static int64_t
int64_takum_log64_from_extended_float(long double f)
{
	return (int64_t)takum_log64_from_extended_float(f);
}

const struct takum_type_parameters takum_type_parameters[] = {
	[TAKUM8] = {
		.name             = "takum8",
		.n                = 8,
		.nar              = TAKUM8_NAR,
		.positive_minimum = TAKUM8_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM8_POSITIVE_MAXIMUM,
		.count            = (uint64_t)UINT8_MAX + 1,
		.int64_takum_to_extended_float = int64_takum8_to_extended_float,
		.int64_takum_from_extended_float = int64_takum8_from_extended_float,
	},
	[TAKUM16] = {
		.name             = "takum16",
		.n                = 16,
		.nar              = TAKUM16_NAR,
		.positive_minimum = TAKUM16_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM16_POSITIVE_MAXIMUM,
		.count            = (uint64_t)UINT16_MAX + 1,
		.int64_takum_to_extended_float = int64_takum16_to_extended_float,
		.int64_takum_from_extended_float = int64_takum16_from_extended_float,
	},
	[TAKUM32] = {
		.name             = "takum32",
		.n                = 32,
		.nar              = TAKUM32_NAR,
		.positive_minimum = TAKUM32_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM32_POSITIVE_MAXIMUM,
		.count            = (uint64_t)UINT32_MAX + 1,
		.int64_takum_to_extended_float = int64_takum32_to_extended_float,
		.int64_takum_from_extended_float = int64_takum32_from_extended_float,
	},
	[TAKUM64] = {
		.name             = "takum64",
		.n                = 64,
		.nar              = TAKUM64_NAR,
		.positive_minimum = TAKUM64_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM64_POSITIVE_MAXIMUM,
		.count            = UINT64_MAX /* + 1, but would overflow */,
		.int64_takum_to_extended_float = int64_takum64_to_extended_float,
		.int64_takum_from_extended_float = int64_takum64_from_extended_float,
	},
	[TAKUM_LOG8] = {
		.name             = "takum_log8",
		.n                = 8,
		.nar              = TAKUM_LOG8_NAR,
		.positive_minimum = TAKUM_LOG8_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM_LOG8_POSITIVE_MAXIMUM,
		.count            = (uint64_t)UINT8_MAX + 1,
		.int64_takum_to_extended_float = int64_takum_log8_to_extended_float,
		.int64_takum_from_extended_float = int64_takum_log8_from_extended_float,
	},
	[TAKUM_LOG16] = {
		.name             = "takum_log16",
		.n                = 16,
		.nar              = TAKUM_LOG16_NAR,
		.positive_minimum = TAKUM_LOG16_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM_LOG16_POSITIVE_MAXIMUM,
		.count            = (uint64_t)UINT16_MAX + 1,
		.int64_takum_to_extended_float = int64_takum_log16_to_extended_float,
		.int64_takum_from_extended_float = int64_takum_log16_from_extended_float,
	},
	[TAKUM_LOG32] = {
		.name             = "takum_log32",
		.n                = 32,
		.nar              = TAKUM_LOG32_NAR,
		.positive_minimum = TAKUM_LOG32_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM_LOG32_POSITIVE_MAXIMUM,
		.count            = (uint64_t)UINT32_MAX + 1,
		.int64_takum_to_extended_float = int64_takum_log32_to_extended_float,
		.int64_takum_from_extended_float = int64_takum_log32_from_extended_float,
	},
	[TAKUM_LOG64] = {
		.name             = "takum_log64",
		.n                = 64,
		.nar              = TAKUM_LOG64_NAR,
		.positive_minimum = TAKUM_LOG64_POSITIVE_MINIMUM,
		.positive_maximum = TAKUM_LOG64_POSITIVE_MAXIMUM,
		.count            = UINT64_MAX /* + 1, but would overflow */,
		.int64_takum_to_extended_float = int64_takum_log64_to_extended_float,
		.int64_takum_from_extended_float = int64_takum_log64_from_extended_float,
	},
};

static int64_t
evaluate_reference_function(const struct unit_test_block *utb, int64_t a,
                            int64_t b, enum takum_type takum_type)
{
	long double a_extended_float, b_extended_float,
		raw_output_extended_float = 0.0L;

	/*
	 * Compute the given function, taking special care to handle
	 * possible under - or overflow
	 */
	feclearexcept(FE_UNDERFLOW);
	feclearexcept(FE_OVERFLOW);

	/* convert a to long double */
	a_extended_float =
		takum_type_parameters[takum_type].int64_takum_to_extended_float(
			a);

	switch (utb->type) {
	case UNIT_TEST_BLOCK_TYPE_ROUNDTRIP:
		fprintf(stderr,
		        "%s: evaluate_reference_function: Unexpected call from "
		        "roundtrip test\n",
		        argv0);
		exit(1);
	case UNIT_TEST_BLOCK_TYPE_TAKUM_INT64_TAKUM:
		raw_output_extended_float =
			utb->data.takum_int64_takum.reference_function(
				a_extended_float, b);
		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM:
		raw_output_extended_float =
			utb->data.takum_takum.reference_function(
				a_extended_float);
		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM:
		/* convert b to long double */
		b_extended_float = takum_type_parameters[takum_type]
		                           .int64_takum_to_extended_float(b);

		raw_output_extended_float =
			utb->data.takum_takum_takum.reference_function(
				a_extended_float, b_extended_float);
		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_UINT8:
		/*
		 * we can directly return the raw uint8 output
		 * casted to int64
		 */
		return (int64_t)utb->data.takum_uint8.reference_function(
			a_extended_float, takum_type);
	};

	/*
	 * Depending on possible under-/overflow, obtain the
	 * reference_output
	 */
	if (fetestexcept(FE_UNDERFLOW) && raw_output_extended_float == 0.0) {
		if (signbit(raw_output_extended_float)) {
			return -takum_type_parameters[takum_type]
			                .positive_minimum;
		} else {
			return takum_type_parameters[takum_type]
			        .positive_minimum;
		}
	} else if (fetestexcept(FE_OVERFLOW)) {
		if (raw_output_extended_float > 0.0) {
			return takum_type_parameters[takum_type]
			        .positive_maximum;
		} else if (raw_output_extended_float == 0.0) {
			if (signbit(raw_output_extended_float)) {
				return -takum_type_parameters[takum_type]
				                .positive_minimum;
			} else {
				return takum_type_parameters[takum_type]
				        .positive_minimum;
			}
		} else {
			return -takum_type_parameters[takum_type]
			                .positive_maximum;
		}
	} else {
		return takum_type_parameters[takum_type]
		        .int64_takum_from_extended_float(
				raw_output_extended_float);
	}
}

int
check_unary_binary_case(const struct unit_test_block *utb, int64_t a, int64_t b,
                        enum takum_type takum_type, uint64_t test_number)
{
	int64_t reference_output = 0, output = 1;
	bool failed = true;

	switch (utb->type) {
	case UNIT_TEST_BLOCK_TYPE_ROUNDTRIP:
		/*
		 * Determine the output of the roundtrip function, but
		 * exit early if the function is unspecified (NULL)
		 */
		switch (takum_type) {
		case TAKUM8:
			if (utb->data.roundtrip.takum8_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum8_function((takum8)a);
			} else {
				return 0;
			}
			break;
		case TAKUM16:
			if (utb->data.roundtrip.takum16_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum16_function((takum16)a);
			} else {
				return 0;
			}
			break;
		case TAKUM32:
			if (utb->data.roundtrip.takum32_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum32_function((takum32)a);
			} else {
				return 0;
			}
			break;
		case TAKUM64:
			if (utb->data.roundtrip.takum64_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum64_function((takum64)a);
			} else {
				return 0;
			}
			break;
		case TAKUM_LOG8:
			if (utb->data.roundtrip.takum_log8_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum_log8_function(
							 (takum_log8)a);
			} else {
				return 0;
			}
			break;
		case TAKUM_LOG16:
			if (utb->data.roundtrip.takum_log16_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum_log16_function(
							 (takum_log16)a);
			} else {
				return 0;
			}
			break;
		case TAKUM_LOG32:
			if (utb->data.roundtrip.takum_log32_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum_log32_function(
							 (takum_log32)a);
			} else {
				return 0;
			}
			break;
		case TAKUM_LOG64:
			if (utb->data.roundtrip.takum_log64_function) {
				output = (int64_t)utb->data.roundtrip
				                 .takum_log64_function(
							 (takum_log64)a);
			} else {
				return 0;
			}
			break;
		}

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_INT64_TAKUM:
		/* Compute reference_function(a, b) */
		reference_output =
			evaluate_reference_function(utb, a, b, takum_type);

		/* Determine the output of the tested function */
		switch (takum_type) {
		case TAKUM8:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum8_function((takum8)a, b);
			break;
		case TAKUM16:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum16_function((takum16)a, b);
			break;
		case TAKUM32:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum32_function((takum32)a, b);
			break;
		case TAKUM64:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum64_function((takum64)a, b);
			break;
		case TAKUM_LOG8:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum_log8_function((takum_log8)a, b);
			break;
		case TAKUM_LOG16:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum_log16_function((takum_log16)a,
			                                       b);
			break;
		case TAKUM_LOG32:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum_log32_function((takum_log32)a,
			                                       b);
			break;
		case TAKUM_LOG64:
			output = (int64_t)utb->data.takum_int64_takum
			                 .takum_log64_function((takum_log64)a,
			                                       b);
			break;
		}

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM:
		/* Compute reference_function(a) */
		reference_output =
			evaluate_reference_function(utb, a, 0, takum_type);

		/* Determine the output of the tested function */
		switch (takum_type) {
		case TAKUM8:
			output = (int64_t)utb->data.takum_takum.takum8_function(
				(takum8)a);
			break;
		case TAKUM16:
			output =
				(int64_t)utb->data.takum_takum.takum16_function(
					(takum16)a);
			break;
		case TAKUM32:
			output =
				(int64_t)utb->data.takum_takum.takum32_function(
					(takum32)a);
			break;
		case TAKUM64:
			output =
				(int64_t)utb->data.takum_takum.takum64_function(
					(takum64)a);
			break;
		case TAKUM_LOG8:
			output = (int64_t)utb->data.takum_takum
			                 .takum_log8_function((takum_log8)a);
			break;
		case TAKUM_LOG16:
			output = (int64_t)utb->data.takum_takum
			                 .takum_log16_function((takum_log16)a);
			break;
		case TAKUM_LOG32:
			output = (int64_t)utb->data.takum_takum
			                 .takum_log32_function((takum_log32)a);
			break;
		case TAKUM_LOG64:
			output = (int64_t)utb->data.takum_takum
			                 .takum_log64_function((takum_log64)a);
			break;
		}

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM:
		/* Compute reference_function(a, b) */
		reference_output =
			evaluate_reference_function(utb, a, b, takum_type);

		/* Determine the output of the tested function */
		switch (takum_type) {
		case TAKUM8:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum8_function((takum8)a, (takum8)b);
			break;
		case TAKUM16:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum16_function((takum16)a,
			                                   (takum16)b);
			break;
		case TAKUM32:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum32_function((takum32)a,
			                                   (takum32)b);
			break;
		case TAKUM64:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum64_function((takum64)a,
			                                   (takum64)b);
			break;
		case TAKUM_LOG8:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum_log8_function((takum_log8)a,
			                                      (takum_log8)b);
			break;
		case TAKUM_LOG16:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum_log16_function((takum_log16)a,
			                                       (takum_log16)b);
			break;
		case TAKUM_LOG32:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum_log32_function((takum_log32)a,
			                                       (takum_log32)b);
			break;
		case TAKUM_LOG64:
			output = (int64_t)utb->data.takum_takum_takum
			                 .takum_log64_function((takum_log64)a,
			                                       (takum_log64)b);
			break;
		}

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_UINT8:
		/* Compute reference_function(a) */
		reference_output =
			evaluate_reference_function(utb, a, 0, takum_type);

		/* Determine the output of the tested function */
		switch (takum_type) {
		case TAKUM8:
			output = (int64_t)utb->data.takum_uint8.takum8_function(
				(takum8)a);
			break;
		case TAKUM16:
			output =
				(int64_t)utb->data.takum_uint8.takum16_function(
					(takum16)a);
			break;
		case TAKUM32:
			output =
				(int64_t)utb->data.takum_uint8.takum32_function(
					(takum32)a);
			break;
		case TAKUM64:
			output =
				(int64_t)utb->data.takum_uint8.takum64_function(
					(takum64)a);
			break;
		case TAKUM_LOG8:
			output = (int64_t)utb->data.takum_uint8
			                 .takum_log8_function((takum_log8)a);
			break;
		case TAKUM_LOG16:
			output = (int64_t)utb->data.takum_uint8
			                 .takum_log16_function((takum_log16)a);
			break;
		case TAKUM_LOG32:
			output = (int64_t)utb->data.takum_uint8
			                 .takum_log32_function((takum_log32)a);
			break;
		case TAKUM_LOG64:
			output = (int64_t)utb->data.takum_uint8
			                 .takum_log64_function((takum_log64)a);
			break;
		}

		break;
	}

	switch (utb->type) {
	case UNIT_TEST_BLOCK_TYPE_ROUNDTRIP:
		failed = (output != a);

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_UINT8:
		failed = (output != reference_output);

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_INT64_TAKUM:
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM:
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM:
		/* we allow deviation by 1 LULP */
		if (output != reference_output &&
		    output != reference_output + 1 &&
		    output != reference_output - 1) {
			failed = true;
		} else {
			failed = false;
		}

		break;
	}

	/*
	 * check the output and optionally increment the failure count
	 * and print an error message
	 */
	if (failed) {
		switch (utb->type) {
		case UNIT_TEST_BLOCK_TYPE_ROUNDTRIP:
			fprintf(stderr,
			        "%s: %s_%s: Failed unit test %" PRIu64 " "
			        "(roundtrip of %.20Le(%" PRIi64
			        ") returned %.20Le(%" PRIi64 "))\n",
			        argv0, takum_type_parameters[takum_type].name,
			        utb->function_name, test_number,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(a),
			        a,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(output),
			        output);
			break;
		case UNIT_TEST_BLOCK_TYPE_TAKUM_INT64_TAKUM:
			fprintf(stderr,
			        "%s: %s_%s: Failed unit test %" PRIu64 " "
			        "(%s_%s(%.20Le, %" PRIi64
			        ") returned %.20Le(%" PRIi64 ") "
			        "instead "
			        "of "
			        "%.20Le(%" PRIi64 "))\n",
			        argv0, takum_type_parameters[takum_type].name,
			        utb->function_name, test_number,
			        takum_type_parameters[takum_type].name,
			        utb->function_name,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(a),
			        b,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(output),
			        output,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(
						reference_output),
			        reference_output);
			break;
		case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM:
			fprintf(stderr,
			        "%s: %s_%s: Failed unit test %" PRIu64 " "
			        "(%s_%s(%.20Le) returned %.20Le(%" PRIi64 ") "
			        "instead "
			        "of "
			        "%.20Le(%" PRIi64 "))\n",
			        argv0, takum_type_parameters[takum_type].name,
			        utb->function_name, test_number,
			        takum_type_parameters[takum_type].name,
			        utb->function_name,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(a),
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(output),
			        output,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(
						reference_output),
			        reference_output);
			break;
		case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM:
			fprintf(stderr,
			        "%s: %s_%s: Failed unit test %" PRIu64 " "
			        "(%s_%s(%.20Le, %.20Le) returned "
			        "%.20Le(%" PRIi64 ") "
			        "instead "
			        "of "
			        "%.20Le(%" PRIi64 "))\n",
			        argv0, takum_type_parameters[takum_type].name,
			        utb->function_name, test_number,
			        takum_type_parameters[takum_type].name,
			        utb->function_name,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(a),
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(b),
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(output),
			        output,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(
						reference_output),
			        reference_output);
			break;
		case UNIT_TEST_BLOCK_TYPE_TAKUM_UINT8:
			fprintf(stderr,
			        "%s: %s_%s: Failed unit test %" PRIu64 " "
			        "(%s_%s(%.20Le) returned %" PRIi64 " "
			        "instead of %" PRIi64 ")\n",
			        argv0, takum_type_parameters[takum_type].name,
			        utb->function_name, test_number,
			        takum_type_parameters[takum_type].name,
			        utb->function_name,
			        takum_type_parameters[takum_type]
			                .int64_takum_to_extended_float(a),
			        output, reference_output);
			break;
		}

		return 1;
	} else {
		return 0;
	}
}

uint64_t
safe_uint64_multiplication(uint64_t a, uint64_t b)
{
	if (a >= UINT64_MAX / b) {
		return UINT64_MAX;
	} else {
		return a * b;
	}
}

static void
sampler_init(const struct unit_test_block *utb, enum takum_type takum_type,
             size_t maximum_sample_count, struct sampler *sampler)
{
	uint64_t full_count;

	sampler->takum_type = takum_type;
	sampler->utb = utb;

	switch (utb->type) {
	case UNIT_TEST_BLOCK_TYPE_ROUNDTRIP:
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM:
	case UNIT_TEST_BLOCK_TYPE_TAKUM_UINT8:
		/* 1D */
		full_count = takum_type_parameters[takum_type].count;

		if (full_count <= maximum_sample_count) {
			sampler->mode = SAMPLER_MODE_TAKUM_FULL;
			sampler->target_count = full_count;

			/* Initialise the x value to NaR to make a full sweep */
			sampler->value_x =
				takum_type_parameters[takum_type].nar;

			/* Initialise the y value to NaR as it is not used in 1D
			 */
			sampler->value_y =
				takum_type_parameters[takum_type].nar;
		} else {
			sampler->mode = SAMPLER_MODE_TAKUM_RANDOM;
			sampler->target_count = maximum_sample_count;

			/*
			 * The start value is chosen such that the bit
			 * representation is all zeros. This is because
			 * the LFSR PRNG cannot cover the all-zero-state.
			 * If it is given the all-zero-state to generate
			 * the next state, it will automatically set the
			 * 'real' starting seed.
			 */
			sampler->value_x = 0;

			/* Initialise the y value to NaR as it is not used in 1D
			 */
			sampler->value_y =
				takum_type_parameters[takum_type].nar;
		}

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_INT64_TAKUM:
		/* 1D with given second argument integer test cases */
		full_count = safe_uint64_multiplication(
			takum_type_parameters[takum_type].count,
			utb->data.takum_int64_takum.integer_test_case_count);

		if (full_count <= maximum_sample_count) {
			sampler->mode = SAMPLER_MODE_TAKUM_INT64_FULL;
			sampler->target_count = full_count;

			/* Initialise the x value to NaR to make a full sweep */
			sampler->value_x =
				takum_type_parameters[takum_type].nar;

			/* Initialise the y value to the first integer test case
			 */
			sampler->value_y = utb->data.takum_int64_takum
			                           .integer_test_cases[0];
		} else {
			sampler->mode = SAMPLER_MODE_TAKUM_INT64_RANDOM;
			sampler->target_count = maximum_sample_count;

			/*
			 * The start value is chosen such that the bit
			 * representation is all zeros. This is because
			 * the LFSR PRNG cannot cover the all-zero-state.
			 * If it is given the all-zero-state to generate
			 * the next state, it will automatically set the
			 * 'real' starting seed.
			 */
			sampler->value_x = 0;

			/* Initialise the y value to the first integer test case
			 */
			sampler->value_y = utb->data.takum_int64_takum
			                           .integer_test_cases[0];
		}

		break;
	case UNIT_TEST_BLOCK_TYPE_TAKUM_TAKUM_TAKUM:
		/* 2D */
		full_count = safe_uint64_multiplication(
			takum_type_parameters[takum_type].count,
			takum_type_parameters[takum_type].count);

		if (full_count <= maximum_sample_count) {
			sampler->mode = SAMPLER_MODE_TAKUM_TAKUM_FULL;
			sampler->target_count = full_count;

			/*
			 * Initialise the x and y values to NaR to make a
			 * full sweep
			 */
			sampler->value_x =
				takum_type_parameters[takum_type].nar;
			sampler->value_y =
				takum_type_parameters[takum_type].nar;
		} else {
			sampler->mode = SAMPLER_MODE_TAKUM_TAKUM_RANDOM;
			sampler->target_count = maximum_sample_count;

			/*
			 * The start values are chosen such that the bit
			 * representation is all zeros. This is because
			 * the LFSR PRNG cannot cover the all-zero-state.
			 * If it is given the all-zero-state to generate
			 * the next state, it will automatically set the
			 * 'real' starting seed.
			 */
			sampler->value_x = 0;
			sampler->value_y = 0;
		}

		break;
	}

	sampler->current_count = 1;
}

static int
sampler_next(struct sampler *sampler)
{
	size_t i;

	switch (sampler->mode) {
	case SAMPLER_MODE_TAKUM_FULL:
		if (sampler->value_x ==
		    takum_type_parameters[sampler->takum_type]
		            .positive_maximum) {
			/* we are done */
			return 1;
		} else {
			sampler->value_x++;
		}

		break;
	case SAMPLER_MODE_TAKUM_RANDOM:
		if (sampler->current_count >= sampler->target_count) {
			/* we are done */
			return 1;
		} else {
			sampler->value_x = random_next(sampler->value_x,
			                               sampler->takum_type);
		}

		break;
	case SAMPLER_MODE_TAKUM_TAKUM_FULL:
		if (sampler->value_y ==
		    takum_type_parameters[sampler->takum_type]
		            .positive_maximum) {
			/* we have completed a full iteration of the y
			 * coordinates */
			if (sampler->value_x ==
			    takum_type_parameters[sampler->takum_type]
			            .positive_maximum) {
				/* the x coordinates are also done, we are done
				 */
				return 1;
			} else {
				sampler->value_y = takum_type_parameters
				                           [sampler->takum_type]
				                                   .nar;
				sampler->value_x += 1;
			}
		} else {
			sampler->value_y += 1;
		}

		break;
	case SAMPLER_MODE_TAKUM_TAKUM_RANDOM:
		if (sampler->current_count >= sampler->target_count) {
			/* we are done */
			return 1;
		} else {
			sampler->value_x = random_next(sampler->value_x,
			                               sampler->takum_type);
			sampler->value_y = random_next(sampler->value_y,
			                               sampler->takum_type);
		}

		break;
	case SAMPLER_MODE_TAKUM_INT64_FULL:
		/* determine the offset of the current y-value integer test case
		 */
		for (i = 0; i < sampler->utb->data.takum_int64_takum
		                        .integer_test_case_count;
		     i++) {
			if (sampler->value_y ==
			    sampler->utb->data.takum_int64_takum
			            .integer_test_cases[i]) {
				break;
			}
		}
		if (i == sampler->utb->data.takum_int64_takum
		                 .integer_test_case_count) {
			fprintf(stderr,
			        "%s: sampler_next: Unexpected integer test "
			        "case mismatch\n",
			        argv0);
			exit(1);
		} else if (i == sampler->utb->data.takum_int64_takum
		                                .integer_test_case_count -
		                        1) {
			/* we have completed a full iteration of the integer
			 * test cases */
			if (sampler->value_x ==
			    takum_type_parameters[sampler->takum_type]
			            .positive_maximum) {
				/* the x coordinates are also done, we are done
				 */
				return 1;
			} else {
				sampler->value_y =
					sampler->utb->data.takum_int64_takum
						.integer_test_cases[0];
				sampler->value_x += 1;
			}
		} else {
			/* get the next integer sample */
			sampler->value_y = sampler->utb->data.takum_int64_takum
			                           .integer_test_cases[i + 1];
		}

		break;
	case SAMPLER_MODE_TAKUM_INT64_RANDOM:
		if (sampler->current_count >= sampler->target_count) {
			/* we are done */
			return 1;
		} else {
			/* determine the offset of the current y-value integer
			 * test case */
			for (i = 0; i < sampler->utb->data.takum_int64_takum
			                        .integer_test_case_count;
			     i++) {
				if (sampler->value_y ==
				    sampler->utb->data.takum_int64_takum
				            .integer_test_cases[i]) {
					break;
				}
			}
			if (i == sampler->utb->data.takum_int64_takum
			                 .integer_test_case_count) {
				fprintf(stderr,
				        "%s: sampler_next: Unexpected integer "
				        "test case mismatch\n",
				        argv0);
				exit(1);
			} else if (i ==
			           sampler->utb->data.takum_int64_takum
			                           .integer_test_case_count -
			                   1) {
				/*
				 * we have completed a full iteration of the
				 * integer test cases, reset and get a new x
				 * value
				 */
				sampler->value_y =
					sampler->utb->data.takum_int64_takum
						.integer_test_cases[0];
				sampler->value_x = random_next(
					sampler->value_x, sampler->takum_type);
			} else {
				/* get the next integer sample */
				sampler->value_y =
					sampler->utb->data.takum_int64_takum
						.integer_test_cases[i + 1];
			}
		}

		break;
	}

	sampler->current_count++;

	return 0;
}

static int
run_unit_test_on_type(const struct unit_test_block *utb,
                      enum takum_type takum_type, uint64_t maximum_sample_count)

{
	struct sampler sampler = { 0 };
	uint64_t failed_count = 0;

	/*
	 * We iterate over (almost) all takums of the given type,
	 * especially making sure that the results properly saturate
	 * (both on under- and overflow) and NaN is propagated in
	 * all cases.
	 *
	 * For this we assume that our conversion routines between
	 * takum and float are correct, which is a valid assumption
	 * given we test those separately.
	 */
	sampler_init(utb, takum_type, maximum_sample_count, &sampler);

	do {
		failed_count += check_unary_binary_case(
			utb, sampler.value_x, sampler.value_y, takum_type,
			sampler.current_count);
	} while (!sampler_next(&sampler));

	printf("%s: %s_%s: %" PRIu64 "/%" PRIu64 " unit tests passed.\n", argv0,
	       takum_type_parameters[takum_type].name, utb->function_name,
	       sampler.target_count - failed_count, sampler.target_count);

	return (failed_count > 0) ? 1 : 0;
}

int
run_unit_test_block(const struct unit_test_block *utb)
{
	uint64_t maximum_sample_count = UINT64_C(1) << 22;

	/* seed the random number generator */
	srand(time(NULL));

	return run_unit_test_on_type(utb, TAKUM8, maximum_sample_count) +
	       run_unit_test_on_type(utb, TAKUM16, maximum_sample_count) +
	       run_unit_test_on_type(utb, TAKUM32, maximum_sample_count) +
	       run_unit_test_on_type(utb, TAKUM64, maximum_sample_count) +
	       run_unit_test_on_type(utb, TAKUM_LOG8, maximum_sample_count) +
	       run_unit_test_on_type(utb, TAKUM_LOG16, maximum_sample_count) +
	       run_unit_test_on_type(utb, TAKUM_LOG32, maximum_sample_count) +
	       run_unit_test_on_type(utb, TAKUM_LOG64, maximum_sample_count);
}
