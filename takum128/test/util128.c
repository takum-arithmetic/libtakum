/* See LICENSE file for copyright and license details. */
#include <stdio.h> /* before gmp.h/mpfr.h, so mpfr_fprintf is declared */
#include <gmp.h>
#include <mpfr.h>
#include <stdint.h>

#include "../../takum128.h"

#include "../src/codec128.h"
#include "../src/util128.h"
#include "util128.h"

char *argv0;

void
test128_seed(gmp_randstate_t rng)
{
	gmp_randinit_default(rng);
	/* fixed seed: reproducible across runs, same spirit as the LFSR
	 * seeding in ../../test/util.c */
	gmp_randseed_ui(rng, 0xd1ab011cUL);
}

unsigned __int128
test128_random_bits(gmp_randstate_t rng)
{
	mpz_t z;
	unsigned long lo, hi;
	unsigned __int128 result;

	mpz_init(z);
	mpz_urandomb(z, rng, 128);

	lo = mpz_get_ui(z);
	mpz_tdiv_q_2exp(z, z, 64);
	hi = mpz_get_ui(z);
	result = (((unsigned __int128)hi) << 64) | lo;

	mpz_clear(z);

	return result;
}

void
test128_decode(mpfr_t out, __int128 t, int is_log)
{
	mpfr_t l;

	mpfr_init2(l, TEST128_REFERENCE_PREC);

	if (is_log) {
		codec128_log_value_from_t(out, (takum_log128)t);
	} else {
		codec128_log_to_l(l, (takum_log128)t);
		codec128_linear_value_from_s_and_l(out, t < 0, l);
	}

	mpfr_clear(l);
}

__int128
test128_encode(mpfr_t value, int is_log)
{
	mpfr_t l;
	__int128 result;

	if (is_log) {
		result = codec128_log_from_value(value);
	} else {
		mpfr_init2(l, TEST128_REFERENCE_PREC);
		codec128_linear_l_from_value(l, value);
		result = codec128_log_from_s_and_l(mpfr_sgn(value) < 0, l);
		mpfr_clear(l);
	}

	return result;
}

int
test128_compare(const char *function_name, int trial, mpfr_t expected,
                mpfr_t actual)
{
	mpfr_t diff, tolerance;
	int mismatch;

	if (mpfr_nan_p(expected) || mpfr_nan_p(actual)) {
		mismatch = !(mpfr_nan_p(expected) && mpfr_nan_p(actual));
	} else if (mpfr_zero_p(expected) || mpfr_zero_p(actual)) {
		mismatch = !(mpfr_zero_p(expected) && mpfr_zero_p(actual));
	} else {
		/*
		 * Relative error tolerance: 2^-110 leaves ~13 bits of
		 * slack below takum128's ~123-bit worst-case mantissa,
		 * enough to absorb legitimate double rounding between the
		 * 256-bit oracle and the 192-bit (TAKUM128_MPFR_PREC)
		 * implementation, without masking a real bug.
		 */
		mpfr_inits2(TEST128_REFERENCE_PREC, diff, tolerance,
		            (mpfr_ptr)0);
		mpfr_sub(diff, actual, expected, MPFR_RNDN);
		mpfr_div(diff, diff, expected, MPFR_RNDN);
		mpfr_abs(diff, diff, MPFR_RNDN);
		mpfr_set_ui_2exp(tolerance, 1, -110, MPFR_RNDN);
		mismatch = mpfr_cmp(diff, tolerance) > 0;
		mpfr_clears(diff, tolerance, (mpfr_ptr)0);
	}

	if (mismatch) {
		mpfr_fprintf(stderr,
		             "%s: %s: trial %d: mismatch: expected=%.40Rg "
		             "actual=%.40Rg\n",
		             argv0, function_name, trial, expected, actual);
	}

	return mismatch;
}

int
test128_compare_saturating(const char *function_name, int trial,
                           mpfr_t expected_value, __int128 actual_result,
                           int is_log)
{
	mpfr_t expected_decoded, actual_decoded;
	int mismatch;

	mpfr_inits2(TEST128_REFERENCE_PREC, expected_decoded, actual_decoded,
	            (mpfr_ptr)0);

	test128_decode(expected_decoded, test128_encode(expected_value, is_log),
	               is_log);
	test128_decode(actual_decoded, actual_result, is_log);
	mismatch = test128_compare(function_name, trial, expected_decoded,
	                           actual_decoded);

	mpfr_clears(expected_decoded, actual_decoded, (mpfr_ptr)0);

	return mismatch;
}

int
test128_report(const char *function_name, uint64_t trials, uint64_t failures)
{
	fprintf(stderr, "%s: %s: %llu/%llu passed\n", argv0, function_name,
	        (unsigned long long)(trials - failures),
	        (unsigned long long)trials);

	return failures > 0;
}
