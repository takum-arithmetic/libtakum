/* See LICENSE file for copyright and license details. */
#include "../../takum128.h"

takum128
takum128_sign(takum128 t)
{
	return (t == TAKUM128_NAR) ? TAKUM128_NAR :
	       (t < 0)             ? -TAKUM128_ONE :
	       (t > 0)             ? TAKUM128_ONE :
	                             0;
}

takum_log128
takum_log128_sign(takum_log128 t)
{
	return (t == TAKUM_LOG128_NAR) ? TAKUM_LOG128_NAR :
	       (t < 0)                 ? -TAKUM_LOG128_ONE :
	       (t > 0)                 ? TAKUM_LOG128_ONE :
	                                 0;
}
