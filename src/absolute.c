/* See LICENSE file for copyright and license details. */
#include "../takum.h"

#include "util.h"

takum8
takum8_absolute(takum8 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum16
takum16_absolute(takum16 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum32
takum32_absolute(takum32 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum64
takum64_absolute(takum64 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum_log8
takum_log8_absolute(takum_log8 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum_log16
takum_log16_absolute(takum_log16 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum_log32
takum_log32_absolute(takum_log32 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum_log64
takum_log64_absolute(takum_log64 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}
