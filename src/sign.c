/* See LICENSE file for copyright and license details. */
#include "../takum.h"

#include "util.h"

takum8
takum8_sign(takum8 t)
{
	return (t == TAKUM8_NAR) ? TAKUM8_NAR :
	       (t < 0)           ? -TAKUM8_ONE :
	       (t > 0)           ? TAKUM8_ONE :
	                           0;
}

takum16
takum16_sign(takum16 t)
{
	return (t == TAKUM16_NAR) ? TAKUM16_NAR :
	       (t < 0)            ? -TAKUM16_ONE :
	       (t > 0)            ? TAKUM16_ONE :
	                            0;
}

takum32
takum32_sign(takum32 t)
{
	return (t == TAKUM32_NAR) ? TAKUM32_NAR :
	       (t < 0)            ? -TAKUM32_ONE :
	       (t > 0)            ? TAKUM32_ONE :
	                            0;
}

takum64
takum64_sign(takum64 t)
{
	return (t == TAKUM64_NAR) ? TAKUM64_NAR :
	       (t < 0)            ? -TAKUM64_ONE :
	       (t > 0)            ? TAKUM64_ONE :
	                            0;
}

takum_log8
takum_log8_sign(takum_log8 t)
{
	return (t == TAKUM_LOG8_NAR) ? TAKUM_LOG8_NAR :
	       (t < 0)               ? -TAKUM_LOG8_ONE :
	       (t > 0)               ? TAKUM_LOG8_ONE :
	                               0;
}

takum_log16
takum_log16_sign(takum_log16 t)
{
	return (t == TAKUM_LOG16_NAR) ? TAKUM_LOG16_NAR :
	       (t < 0)                ? -TAKUM_LOG16_ONE :
	       (t > 0)                ? TAKUM_LOG16_ONE :
	                                0;
}

takum_log32
takum_log32_sign(takum_log32 t)
{
	return (t == TAKUM_LOG32_NAR) ? TAKUM_LOG32_NAR :
	       (t < 0)                ? -TAKUM_LOG32_ONE :
	       (t > 0)                ? TAKUM_LOG32_ONE :
	                                0;
}

takum_log64
takum_log64_sign(takum_log64 t)
{
	return (t == TAKUM_LOG64_NAR) ? TAKUM_LOG64_NAR :
	       (t < 0)                ? -TAKUM_LOG64_ONE :
	       (t > 0)                ? TAKUM_LOG64_ONE :
	                                0;
}
