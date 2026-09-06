/* See LICENSE file for copyright and license details. */
#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>
#include <stdio.h>

#include "../../takum128.h"

#include "util128.h"

/*
 * Independent re-derivation of the p_lut (see ../src/precision.c) so
 * this test isn't just re-running the same table against itself.
 */
static const uint8_t p_lut[] = {
	4, 5, 6, 7, 8, 9, 10, 11, 11, 10, 9, 8, 7, 6, 5, 4,
};

static uint8_t
expected_precision(unsigned __int128 bits, __int128 value)
{
	uint_fast8_t DR;

	if (value == 0 || value == TAKUM128_NAR) {
		return 116;
	}

	DR = (uint_fast8_t)((bits >> 123) & 0xf);

	return (uint8_t)(p_lut[DR] + 112);
}

int
main(int argc, char *argv[])
{
	gmp_randstate_t rng;
	takum128 ta;
	takum_log128 la;
	unsigned __int128 bits;
	uint64_t i, failures_takum = 0, failures_log = 0;
	uint8_t expected, actual;

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);

	for (i = 0; i < TEST128_TRIALS; i++) {
		bits = test128_random_bits(rng);

		ta = (takum128)bits;
		expected = expected_precision(bits, ta);
		actual = takum128_precision(ta);
		if (expected != actual) {
			fprintf(stderr,
			        "%s: takum128_precision: trial %d: "
			        "expected=%u actual=%u\n",
			        argv0, (int)i, expected, actual);
			failures_takum++;
		}

		la = (takum_log128)bits;
		expected = expected_precision(bits, la);
		actual = takum_log128_precision(la);
		if (expected != actual) {
			fprintf(stderr,
			        "%s: takum_log128_precision: trial %d: "
			        "expected=%u actual=%u\n",
			        argv0, (int)i, expected, actual);
			failures_log++;
		}
	}

	return test128_report("takum128_precision", TEST128_TRIALS,
	                      failures_takum) |
	       test128_report("takum_log128_precision", TEST128_TRIALS,
	                      failures_log);
}
