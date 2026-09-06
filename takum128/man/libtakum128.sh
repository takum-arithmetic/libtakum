cat << EOF
.Dd ${MAN_DATE}
.Dt LIBTAKUM128 7
.Os libtakum128
.Sh NAME
.Nm libtakum128
.Nd 128-bit takum arithmetic extension for libtakum
.Sh SYNOPSIS
.In takum128.h

.Fd #typedef takum128
.Fd #typedef takum_log128

.Fd #define TAKUM{,_LOG}128_NAR /* NaR (Not a Real) */
.Fd #define TAKUM{,_LOG}128_POSITIVE_MINIMUM /* Smallest Pos. */
.Fd #define TAKUM{,_LOG}128_POSITIVE_MAXIMUM /* Largest Pos. */
.Fd #define TAKUM{,_LOG}128_ONE /* 1 */

.Fd #define TAKUM{,_LOG}128_2_PI /* 2π */
.Fd #define TAKUM{,_LOG}128_2_PI_OVER_3 /* 2π/3 */
.Fd #define TAKUM{,_LOG}128_2_PI_OVER_5 /* 2π/5 */
.Fd #define TAKUM{,_LOG}128_3_PI /* 3π */
.Fd #define TAKUM{,_LOG}128_3_PI_OVER_2 /* 3π/2 */
.Fd #define TAKUM{,_LOG}128_3_PI_OVER_4 /* 3π/4 */
.Fd #define TAKUM{,_LOG}128_3_PI_OVER_5 /* 3π/5 */
.Fd #define TAKUM{,_LOG}128_4_PI /* 4π */
.Fd #define TAKUM{,_LOG}128_4_PI_OVER_3 /* 4π/3 */
.Fd #define TAKUM{,_LOG}128_4_PI_OVER_5 /* 4π/5 */
.Fd #define TAKUM{,_LOG}128_5_PI /* 5π */
.Fd #define TAKUM{,_LOG}128_5_PI_OVER_2 /* 5π/2 */
.Fd #define TAKUM{,_LOG}128_5_PI_OVER_3 /* 5π/3 */
.Fd #define TAKUM{,_LOG}128_5_PI_OVER_4 /* 5π/4 */
.Fd #define TAKUM{,_LOG}128_5_PI_OVER_6 /* 5π/6 */
.Fd #define TAKUM{,_LOG}128_6_PI /* 6π */
.Fd #define TAKUM{,_LOG}128_6_PI_OVER_5 /* 6π/5 */
.Fd #define TAKUM{,_LOG}128_GAMMA /* Euler-Mascheroni const. γ */
.Fd #define TAKUM{,_LOG}128_LB_10 /* lb(10) */
.Fd #define TAKUM{,_LOG}128_LB_E /* lb(e) */
.Fd #define TAKUM{,_LOG}128_LG_2 /* lg(2) */
.Fd #define TAKUM{,_LOG}128_LG_E /* lg(e) */
.Fd #define TAKUM{,_LOG}128_LN_10 /* ln(10) */
.Fd #define TAKUM{,_LOG}128_LN_2 /* ln(2) */
.Fd #define TAKUM{,_LOG}128_PHI /* Golden ratio φ */
.Fd #define TAKUM{,_LOG}128_PI /* π */
.Fd #define TAKUM{,_LOG}128_PI_OVER_2 /* π/2 */
.Fd #define TAKUM{,_LOG}128_PI_OVER_3 /* π/3 */
.Fd #define TAKUM{,_LOG}128_PI_OVER_4 /* π/4 */
.Fd #define TAKUM{,_LOG}128_PI_OVER_5 /* π/5 */
.Fd #define TAKUM{,_LOG}128_PI_OVER_6 /* π/6 */
.Fd #define TAKUM{,_LOG}128_SQUARE_ROOT_2 /* √2 */
.Fd #define TAKUM{,_LOG}128_SQUARE_ROOT_3 /* √3 */
.Fd #define TAKUM{,_LOG}128_SQUARE_ROOT_5 /* √5 */
.Fd #define TAKUM{,_LOG}128_SQUARE_ROOT_6 /* √6 */
.Sh DESCRIPTION
The
.Nm
extension adds
.Vt takum128
and
.Vt takum_log128 ,
128-bit takum and logarithmic takum types, to
.Xr libtakum 7 .
It is built and installed separately (see
.Pa takum128/README
in the source distribution): unlike every other width, which implements
its arithmetic by decoding to the widest native hardware floating-point
type, calling libm, and re-encoding, a
.Vt takum128 Ns 's
mantissa can be up to 123 bits wide, far beyond what any hardware
.Vt float , double
or
.Vt "long double"
can hold. Getting genuine 128-bit-quality results instead requires
arbitrary-precision arithmetic, so this extension is backed by MPFR and
GMP (both LGPL, unlike the ISC-licensed, otherwise dependency-free rest
of
.Xr libtakum 7 ) .
.Pp
Every function
.Xr libtakum 7
defines for
.Vt takum64
and
.Vt takum_log64
has a
.Vt takum128 / Vt takum_log128
counterpart of the same name, with the same NaR/zero/sign conventions;
see the corresponding
.Vt takum64
manual page (e.g.
.Xr takum64_addition 3
for
.Fn takum128_addition )
for the semantics of each function, which do not otherwise differ by
width. Conversion functions follow the naming scheme of
.Xr libtakum 7 Ns 's
own conversions between widths, e.g.
.Fn takum128_from_takum64 ,
.Fn takum64_from_takum128 ,
.Fn takum128_from_float64
and
.Fn takum128_to_float64 .
.Pp
One consequence of the takum format's characteristic (regime/exponent)
field not growing with bit width, only its mantissa field: a
.Vt takum128 Ns 's
dynamic range is the
.Em same
as every other width (up to roughly ±2^255) -- only precision grows with
width, not range.
.Vt takum128
is precision-only headroom over
.Vt takum64 ,
not a bigger-range replacement for it.
.Sh SEE ALSO
.Xr libtakum 7 ,
EOF

# list all function base names once (both takum128_NAME and
# takum_log128_NAME share the same NAME manual page reference below,
# since behaviour is documented once per function, not per type), cross
# referencing the takum64 manual page that documents their semantics.
LAST_NAME=""
for name in $MAN3_BASE_NAMES; do
	if [ ! -z "$LAST_NAME" ]; then
		printf ".Xr takum64_$LAST_NAME 3 ,\n"
	fi
	LAST_NAME=$name
done
if [ ! -z "$LAST_NAME" ]; then
	printf ".Xr takum64_$LAST_NAME 3\n"
fi

cat << EOF
.Sh AUTHORS
.An Laslo Hunhold Aq Mt laslo@hunhold.de
EOF
