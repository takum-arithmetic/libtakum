/* See LICENSE file for copyright and license details. */
#include "../../takum128.h"

takum128
takum128_absolute(takum128 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}

takum_log128
takum_log128_absolute(takum_log128 t)
{
	return (t < 0) * (-t) + (t >= 0) * t;
}
