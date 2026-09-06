/* See LICENSE file for copyright and license details. */
#ifndef TEST_UTIL128_H
#define TEST_UTIL128_H

#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>

#include "../../takum128.h"

/*
 * Reference computations run at a higher precision than
 * TAKUM128_MPFR_PREC (192, see ../src/util128.h) so the oracle never
 * shares rounding error with the implementation under test.
 */
#define TEST128_REFERENCE_PREC 256

/* Number of random trials each test runs. */
#define TEST128_TRIALS 20000

extern char *argv0;

/* Seeded once per test binary; deterministic across runs for repro. */
void test128_seed(gmp_randstate_t rng);

/* A uniformly random 128-bit pattern, NaR/zero included in the space. */
unsigned __int128 test128_random_bits(gmp_randstate_t rng);

/*
 * Decode t's *actual represented value* into out at TEST128_REFERENCE_PREC:
 * for takum128 (is_log = 0) via Algorithm 5, for takum_log128 (is_log = 1)
 * via exp(l/2). NaR decodes to NaN, 0 to 0, mirroring codec128.c.
 */
void test128_decode(mpfr_t out, __int128 t, int is_log);

/*
 * Encode a TEST128_REFERENCE_PREC value back to a takum128/takum_log128
 * bit pattern, for tests that want to compare encoded bit patterns
 * rather than decoded values (e.g. conversion tests).
 */
__int128 test128_encode(mpfr_t value, int is_log);

/*
 * Compare expected vs. actual (both already decoded to values) allowing
 * a small relative-error tolerance to absorb legitimate double-rounding
 * between the TEST128_REFERENCE_PREC oracle and the 192-bit
 * implementation; NaN/NaR and zero are compared exactly. Returns 1 on
 * mismatch (and prints a diagnostic), 0 on match.
 */
int test128_compare(const char *function_name, int trial, mpfr_t expected,
                    mpfr_t actual);

/*
 * Like test128_compare, but for comparing an unbounded-range reference
 * value (as an arbitrary-precision mpfr_t, e.g. straight out of
 * mpfr_add with no notion of takum128's representable range) against an
 * actual takum128/takum_log128 result: expected_value is first encoded
 * and decoded exactly as the implementation under test would (so a
 * mathematically correct but out-of-range expected value is compared
 * against its *correctly saturated* form, not the raw unbounded one).
 * This still independently verifies the arithmetic (which mpfr calls
 * were made, in what order, with what operands) -- it only stops
 * independently re-verifying the encode/saturate step itself, which
 * ../../takum128/test/conversion.c already exercises directly.
 */
int test128_compare_saturating(const char *function_name, int trial,
                               mpfr_t expected_value, __int128 actual_result,
                               int is_log);

/* Prints the pass/fail summary in the same style as ../../test/util.c
 * and returns 1 if any failures occurred (fit for use as main()'s
 * return value), 0 otherwise. */
int test128_report(const char *function_name, uint64_t trials,
                   uint64_t failures);

#endif /* TEST_UTIL128_H */
