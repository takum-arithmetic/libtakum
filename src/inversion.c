/* See LICENSE file for copyright and license details. */
#include "../takum.h"

#include "util.h"

/* no need to fix the result, as inv(0)=inf yields NaR without our doing */
#define RESULT_FIXER_MACRO(arg, res) (res)

static long double
inversionl(long double f)
{
	return 1.0l / f;
}

static double
inversion(double f)
{
	return (double)inversionl((long double)f);
}

UTIL_UNARY_FLOAT_TAKUM_WRAPPER(inversion, inversion, RESULT_FIXER_MACRO)

takum_log8
takum_log8_inversion(takum_log8 t)
{
	union util_takum8_union out = {
		.value = t,
	};

	out.bits = (out.bits ^ UINT8_C(0x7f)) + 1;

	return (t == TAKUM_LOG8_NAR) ? TAKUM_LOG8_NAR : out.value;
}

takum_log16
takum_log16_inversion(takum_log16 t)
{
	union util_takum16_union out = {
		.value = t,
	};

	out.bits = (out.bits ^ UINT16_C(0x7fff)) + 1;

	return (t == TAKUM_LOG16_NAR) ? TAKUM_LOG16_NAR : out.value;
}

takum_log32
takum_log32_inversion(takum_log32 t)
{
	union util_takum32_union out = {
		.value = t,
	};

	out.bits = (out.bits ^ UINT32_C(0x7fffffff)) + 1;

	return (t == TAKUM_LOG32_NAR) ? TAKUM_LOG32_NAR : out.value;
}

takum_log64
takum_log64_inversion(takum_log64 t)
{
	union util_takum64_union out = {
		.value = t,
	};

	out.bits = (out.bits ^ UINT64_C(0x7fffffffffffffff)) + 1;

	return (t == TAKUM_LOG64_NAR) ? TAKUM_LOG64_NAR : out.value;
}
