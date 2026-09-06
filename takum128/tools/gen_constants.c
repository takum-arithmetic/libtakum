/* See LICENSE file for copyright and license details. */
/*
 * One-shot generator for the named-constant table in ../../takum128.h
 * (mirroring the constants ../../takum.h carries for widths 8/16/32/64).
 * Computes each constant at TAKUM128_MPFR_PREC-plus-guard-bits precision
 * via MPFR, encodes it through the same codec128 entry points the
 * library itself uses, and prints ready-to-paste #define lines.
 *
 * Not part of the build: run manually (see the Makefile's `constants`
 * target) whenever the constant table needs (re)generating.
 */
#include <mpfr.h>
#include <stdio.h>

#include "../../takum128.h"

#include "../src/codec128.h"
#include "../src/util128.h"

/* extra margin over TAKUM128_MPFR_PREC so these one-shot values are not
 * themselves the precision bottleneck */
#define GEN_PREC (TAKUM128_MPFR_PREC + 64)

static void
print_pair(const char *name, mpfr_t value)
{
	mpfr_t l;
	takum128 t128;
	takum_log128 tlog128;
	unsigned __int128 bits;

	mpfr_init2(l, TAKUM128_MPFR_PREC);
	codec128_linear_l_from_value(l, value);
	t128 = codec128_log_from_s_and_l(mpfr_sgn(value) < 0, l);
	mpfr_clear(l);

	tlog128 = codec128_log_from_value(value);

	bits = (unsigned __int128)t128;
	printf("#define TAKUM128_%-16s TAKUM128_C(0x%016llxULL, "
	       "0x%016llxULL)\n",
	       name, (unsigned long long)(bits >> 64),
	       (unsigned long long)bits);

	bits = (unsigned __int128)tlog128;
	printf("#define TAKUM_LOG128_%-16s TAKUM_LOG128_C(0x%016llxULL, "
	       "0x%016llxULL)\n",
	       name, (unsigned long long)(bits >> 64),
	       (unsigned long long)bits);
}

int
main(void)
{
	mpfr_t pi, gamma, phi, ln2, ln10, lb10, lbe, lg2, lge;
	mpfr_t sqrt2, sqrt3, sqrt5, sqrt6;
	mpfr_t tmp, five;

	mpfr_inits2(GEN_PREC, pi, gamma, phi, ln2, ln10, lb10, lbe, lg2, lge,
	            sqrt2, sqrt3, sqrt5, sqrt6, tmp, five, (mpfr_ptr)0);

	mpfr_const_pi(pi, MPFR_RNDN);
	mpfr_const_euler(gamma, MPFR_RNDN);
	mpfr_const_log2(ln2, MPFR_RNDN); /* ln(2) */

	mpfr_set_ui(tmp, 10, MPFR_RNDN);
	mpfr_log(ln10, tmp, MPFR_RNDN);  /* ln(10) */
	mpfr_log2(lb10, tmp, MPFR_RNDN); /* lb(10) */

	mpfr_ui_div(lbe, 1, ln2, MPFR_RNDN);  /* lb(e) = 1/ln(2) */
	mpfr_ui_div(lge, 1, ln10, MPFR_RNDN); /* lg(e) = 1/ln(10) */

	mpfr_set_ui(tmp, 2, MPFR_RNDN);
	mpfr_log10(lg2, tmp, MPFR_RNDN); /* lg(2) */

	mpfr_set_ui(five, 5, MPFR_RNDN);
	mpfr_sqrt(sqrt5, five, MPFR_RNDN);
	mpfr_add_ui(phi, sqrt5, 1, MPFR_RNDN);
	mpfr_div_ui(phi, phi, 2, MPFR_RNDN); /* (1+sqrt(5))/2 */

	mpfr_sqrt_ui(sqrt2, 2, MPFR_RNDN);
	mpfr_sqrt_ui(sqrt3, 3, MPFR_RNDN);
	mpfr_sqrt_ui(sqrt6, 6, MPFR_RNDN);

	/* pi and its small-integer multiples/fractions */
	print_pair("PI", pi);
	mpfr_div_ui(tmp, pi, 2, MPFR_RNDN);
	print_pair("PI_OVER_2", tmp);
	mpfr_div_ui(tmp, pi, 3, MPFR_RNDN);
	print_pair("PI_OVER_3", tmp);
	mpfr_div_ui(tmp, pi, 4, MPFR_RNDN);
	print_pair("PI_OVER_4", tmp);
	mpfr_div_ui(tmp, pi, 5, MPFR_RNDN);
	print_pair("PI_OVER_5", tmp);
	mpfr_div_ui(tmp, pi, 6, MPFR_RNDN);
	print_pair("PI_OVER_6", tmp);

	mpfr_mul_ui(tmp, pi, 2, MPFR_RNDN);
	print_pair("2_PI", tmp);
	mpfr_mul_ui(tmp, pi, 2, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 3, MPFR_RNDN);
	print_pair("2_PI_OVER_3", tmp);
	mpfr_mul_ui(tmp, pi, 2, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 5, MPFR_RNDN);
	print_pair("2_PI_OVER_5", tmp);

	mpfr_mul_ui(tmp, pi, 3, MPFR_RNDN);
	print_pair("3_PI", tmp);
	mpfr_mul_ui(tmp, pi, 3, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 2, MPFR_RNDN);
	print_pair("3_PI_OVER_2", tmp);
	mpfr_mul_ui(tmp, pi, 3, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 4, MPFR_RNDN);
	print_pair("3_PI_OVER_4", tmp);
	mpfr_mul_ui(tmp, pi, 3, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 5, MPFR_RNDN);
	print_pair("3_PI_OVER_5", tmp);

	mpfr_mul_ui(tmp, pi, 4, MPFR_RNDN);
	print_pair("4_PI", tmp);
	mpfr_mul_ui(tmp, pi, 4, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 3, MPFR_RNDN);
	print_pair("4_PI_OVER_3", tmp);
	mpfr_mul_ui(tmp, pi, 4, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 5, MPFR_RNDN);
	print_pair("4_PI_OVER_5", tmp);

	mpfr_mul_ui(tmp, pi, 5, MPFR_RNDN);
	print_pair("5_PI", tmp);
	mpfr_mul_ui(tmp, pi, 5, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 2, MPFR_RNDN);
	print_pair("5_PI_OVER_2", tmp);
	mpfr_mul_ui(tmp, pi, 5, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 3, MPFR_RNDN);
	print_pair("5_PI_OVER_3", tmp);
	mpfr_mul_ui(tmp, pi, 5, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 4, MPFR_RNDN);
	print_pair("5_PI_OVER_4", tmp);
	mpfr_mul_ui(tmp, pi, 5, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 6, MPFR_RNDN);
	print_pair("5_PI_OVER_6", tmp);

	mpfr_mul_ui(tmp, pi, 6, MPFR_RNDN);
	print_pair("6_PI", tmp);
	mpfr_mul_ui(tmp, pi, 6, MPFR_RNDN);
	mpfr_div_ui(tmp, tmp, 5, MPFR_RNDN);
	print_pair("6_PI_OVER_5", tmp);

	print_pair("GAMMA", gamma);
	print_pair("LB_10", lb10);
	print_pair("LB_E", lbe);
	print_pair("LG_2", lg2);
	print_pair("LG_E", lge);
	print_pair("LN_10", ln10);
	print_pair("LN_2", ln2);
	print_pair("PHI", phi);
	print_pair("SQUARE_ROOT_2", sqrt2);
	print_pair("SQUARE_ROOT_3", sqrt3);
	print_pair("SQUARE_ROOT_5", sqrt5);
	print_pair("SQUARE_ROOT_6", sqrt6);

	mpfr_clears(pi, gamma, phi, ln2, ln10, lb10, lbe, lg2, lge, sqrt2,
	            sqrt3, sqrt5, sqrt6, tmp, five, (mpfr_ptr)0);

	return 0;
}
