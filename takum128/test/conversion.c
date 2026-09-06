/* See LICENSE file for copyright and license details. */
#include <gmp.h>
#include <math.h>
#include <mpfr.h>
#include <stdint.h>

#include "../../takum128.h"

#include "util128.h"

/*
 * takum's dynamic range is fixed by its characteristic field, which
 * (see ../src/codec128.c) does *not* grow with bit width -- only
 * precision does. takum128's max magnitude is ~2^255, takum_log128's is
 * ~e^127.5 (~2^184, since takum_log's stored value is twice a natural
 * logarithm). Values drawn with a magnitude comfortably inside the
 * *smaller* of those two ranges can't legitimately saturate in either
 * type, which keeps the round-trip/cross-conversion checks below
 * meaningful instead of exercising (correct, but exact-match-breaking)
 * overflow saturation.
 */
#define SAFE_MAX_BINARY_EXPONENT 100

static void
random_bounded_value(mpfr_t out, gmp_randstate_t rng)
{
	long shift;

	mpfr_urandom(out, rng, MPFR_RNDN);    /* uniform in [0,1) */
	mpfr_add_d(out, out, 1.0, MPFR_RNDN); /* now in [1,2) */
	shift = (long)gmp_urandomm_ui(rng, 2 * SAFE_MAX_BINARY_EXPONENT + 1) -
	        SAFE_MAX_BINARY_EXPONENT;
	mpfr_mul_2si(out, out, shift, MPFR_RNDN);
	if (gmp_urandomb_ui(rng, 1)) {
		mpfr_neg(out, out, MPFR_RNDN);
	}
}

/*
 * Round-trip a random (bounded-magnitude, see above) double through
 * takum128/takum_log128 and back; doubles have far fewer mantissa bits
 * than either type can store, so this should be an exact round trip.
 */
static uint64_t
test_float64_roundtrip(gmp_randstate_t rng)
{
	mpfr_t v;
	uint64_t i, failures = 0;
	double f;

	mpfr_init2(v, TEST128_REFERENCE_PREC);

	for (i = 0; i < TEST128_TRIALS; i++) {
		random_bounded_value(v, rng);
		f = mpfr_get_d(v, MPFR_RNDN);

		if (takum128_to_float64(takum128_from_float64(f)) != f) {
			failures++;
		}
		if (takum_log128_to_float64(takum_log128_from_float64(f)) !=
		    f) {
			failures++;
		}
	}

	mpfr_clear(v);

	return failures;
}

/*
 * Widening takum64 -> takum128 -> back to takum64 must be the identity
 * (no precision is lost widening into a much larger mantissa and then
 * narrowing back to exactly the original width) -- this one exercises
 * the full bit-pattern space (including takum64's own saturation edge
 * cases), unlike the value-based round trips above, since it never
 * leaves takum64's own representable range to begin with.
 */
static uint64_t
test_takum64_roundtrip(gmp_randstate_t rng)
{
	uint64_t i, failures = 0;
	takum64 t, back;
	takum_log64 lt, lback;
	uint64_t bits;

	for (i = 0; i < TEST128_TRIALS; i++) {
		bits = ((uint64_t)gmp_urandomb_ui(rng, 32) << 32) |
		       gmp_urandomb_ui(rng, 32);

		t = (takum64)bits;
		back = takum64_from_takum128(takum128_from_takum64(t));
		if (back != t) {
			failures++;
		}

		lt = (takum_log64)bits;
		lback = takum_log64_from_takum_log128(
			takum_log128_from_takum_log64(lt));
		if (lback != lt) {
			failures++;
		}
	}

	return failures;
}

/*
 * takum128 <-> takum_log128 conversion should agree with the decoded
 * value on both sides (checked via the same relative-error tolerance
 * used elsewhere, since the conversion goes through the log <-> linear
 * transform and isn't bit-exact by construction). Uses bounded-magnitude
 * values (see above) so neither direction can legitimately saturate.
 */
static uint64_t
test_log_crossconversion(gmp_randstate_t rng)
{
	mpfr_t v, decoded;
	uint64_t i, failures = 0;
	takum128 ta;
	takum_log128 la;

	mpfr_inits2(TEST128_REFERENCE_PREC, v, decoded, (mpfr_ptr)0);

	for (i = 0; i < TEST128_TRIALS; i++) {
		random_bounded_value(v, rng);

		ta = test128_encode(v, 0);
		test128_decode(decoded, takum_log128_from_takum128(ta), 1);
		failures += test128_compare("takum_log128_from_takum128",
		                            (int)i, v, decoded);

		la = test128_encode(v, 1);
		test128_decode(decoded, takum128_from_takum_log128(la), 0);
		failures += test128_compare("takum128_from_takum_log128",
		                            (int)i, v, decoded);
	}

	mpfr_clears(v, decoded, (mpfr_ptr)0);

	return failures;
}

int
main(int argc, char *argv[])
{
	gmp_randstate_t rng;
	uint64_t f64_failures, w64_failures, log_failures;

	(void)argc;
	argv0 = argv[0];

	test128_seed(rng);

	f64_failures = test_float64_roundtrip(rng);
	w64_failures = test_takum64_roundtrip(rng);
	log_failures = test_log_crossconversion(rng);

	return test128_report("float64 roundtrip", 2 * TEST128_TRIALS,
	                      f64_failures) |
	       test128_report("takum64 roundtrip", 2 * TEST128_TRIALS,
	                      w64_failures) |
	       test128_report("takum128 <-> takum_log128", 2 * TEST128_TRIALS,
	                      log_failures);
}
