cat << EOF
.Dd ${MAN_DATE}
.Dt LIBTAKUM 7
.Os libtakum
.Sh NAME
.Nm libtakum
.Nd takum arithmetic library
.Sh SYNOPSIS
.In takum.h

.Fd #typedef takum8
.Fd #typedef takum16
.Fd #typedef takum32
.Fd #typedef takum64
.Fd #typedef takum_log8
.Fd #typedef takum_log16
.Fd #typedef takum_log32
.Fd #typedef takum_log64

.Fd #define TAKUM{,_LOG}{8,16,32,64}_NAR /* NaR (Not a Real) */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_POSITIVE_MINIMUM /* Smallest Pos. */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_POSITIVE_MAXIMUM /* Largest Pos. */

.Fd #define TAKUM{,_LOG}{8,16,32,64}_2_PI /* 2π */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_2_PI_OVER_3 /* 2π/3 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_2_PI_OVER_5 /* 2π/5 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_3_PI /* 3π */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_3_PI_OVER_2 /* 3π/2 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_3_PI_OVER_4 /* 3π/4 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_3_PI_OVER_5 /* 3π/5 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_4_PI /* 4π */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_4_PI_OVER_3 /* 4π/3 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_4_PI_OVER_5 /* 4π/5 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_5_PI /* 5π */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_5_PI_OVER_2 /* 5π/2 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_5_PI_OVER_3 /* 5π/3 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_5_PI_OVER_4 /* 5π/4 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_5_PI_OVER_6 /* 5π/6 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_6_PI /* 6π */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_6_PI_OVER_5 /* 6π/5 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_GAMMA /* Euler-Mascheroni const. γ */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_LB_10 /* lb(10) */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_LB_E /* lb(e) */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_LG_2 /* lg(2) */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_LG_E /* lg(e) */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_LN_10 /* ln(10) */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_LN_2 /* ln(2) */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_ONE /* 1 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_PHI /* Golden ratio φ */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_PI /* π */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_PI_OVER_2 /* π/2 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_PI_OVER_3 /* π/3 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_PI_OVER_4 /* π/4 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_PI_OVER_5 /* π/5 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_PI_OVER_6 /* π/6 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_SQUARE_ROOT_2 /* √2 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_SQUARE_ROOT_3 /* √3 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_SQUARE_ROOT_5 /* √5 */
.Fd #define TAKUM{,_LOG}{8,16,32,64}_SQUARE_ROOT_6 /* √6 */
.Sh DESCRIPTION
The
.Nm
library is an ISO C99 implementation of takum arithmetic, an alternative machine number format to IEEE 754 floating-point numbers. The functions contained in this library allow proper conversion from and to IEEE 754 floating-point types and facilitate the computation with takums.
.Pp
The library defines the four types
.Vt takum8 , takum16 , takum32
and
.Vt takum64
representing (floating-point) takums and
.Vt takum_log8 , takum_log16 , takum_log32
and
.Vt takum_log64
representing logarithmic takums for the respective 8-, 16-, 32- and 64-bit precisions. Negation negates the represented number. Comparisons (==, <, <=, >=, >) are also well-defined for two takums of the same type. The literal 0 represents zero and can be directly used for assignments and comparisons.
.Pp
Each type has a unique not-a-number type called NaR (not a real), which is
defined as
.Dv TAKUM8_NAR , TAKUM16_NAR , TAKUM32_NAR , TAKUM64_NAR, TAKUM_LOG8_NAR , TAKUM_LOG16_NAR , TAKUM_LOG32_NAR , TAKUM_LOG64_NAR
respectively. NaR is equal to itself and smaller than any other takum. If any argument of a function is NaR the result is NaR by convention. There is no dedicated symbol for infinity and NaR is also used to represent infinity.
.Pp
Also defined are the smallest and largest positive representable numbers for each type as
.Dv TAKUM8_POSITIVE_MINIMUM , TAKUM16_POSITIVE_MINIMUM , TAKUM32_POSITIVE_MINIMUM , TAKUM64_POSITIVE_MINIMUM, TAKUM_LOG8_POSITIVE_MINIMUM , TAKUM_LOG16_POSITIVE_MINIMUM , TAKUM_LOG32_POSITIVE_MINIMUM , TAKUM_LOG64_POSITIVE_MINIMUM
and
.Dv TAKUM8_POSITIVE_MAXIMUM , TAKUM16_POSITIVE_MAXIMUM , TAKUM32_POSITIVE_MAXIMUM , TAKUM64_POSITIVE_MAXIMUM, TAKUM_LOG8_POSITIVE_MAXIMUM , TAKUM_LOG16_POSITIVE_MAXIMUM , TAKUM_LOG32_POSITIVE_MAXIMUM , TAKUM_LOG64_POSITIVE_MAXIMUM
respectively. Given the set of takums is symmetric under negation, the smallest and largest representable negative numbers are obtained via negation, e.g. for
.Vt takum8
as
.Dv -TAKUM8_POSITIVE_MAXIMUM
and
.Dv -TAKUM8_POSITIVE_MINIMUM .
.Pp
For numerical purposes
.Nm
defines a range of useful numerical constants, including the Euler-Mascheroni constant γ as
.Dv TAKUM8_GAMMA , TAKUM16_GAMMA , TAKUM32_GAMMA , TAKUM64_GAMMA , TAKUM_LOG8_GAMMA , TAKUM_LOG16_GAMMA , TAKUM_LOG32_GAMMA , TAKUM_LOG64_GAMMA ,
the golden ratio φ as
.Dv TAKUM8_PHI , TAKUM16_PHI , TAKUM32_PHI , TAKUM64_PHI , TAKUM_LOG8_PHI , TAKUM_LOG16_PHI , TAKUM_LOG32_PHI , TAKUM_LOG64_PHI ,
the square root of 2 as
.Dv TAKUM8_SQUARE_ROOT_2 , TAKUM16_SQUARE_ROOT_2 , TAKUM32_SQUARE_ROOT_2 , TAKUM64_SQUARE_ROOT_2 , TAKUM_LOG8_SQUARE_ROOT_2 , TAKUM_LOG16_SQUARE_ROOT_2 , TAKUM_LOG32_SQUARE_ROOT_2 , TAKUM_LOG64_SQUARE_ROOT_2 ,
the square root of 3 as
.Dv TAKUM8_SQUARE_ROOT_3 , TAKUM16_SQUARE_ROOT_3 , TAKUM32_SQUARE_ROOT_3 , TAKUM64_SQUARE_ROOT_3 , TAKUM_LOG8_SQUARE_ROOT_3 , TAKUM_LOG16_SQUARE_ROOT_3 , TAKUM_LOG32_SQUARE_ROOT_3 , TAKUM_LOG64_SQUARE_ROOT_3 ,
the square root of 5 as
.Dv TAKUM8_SQUARE_ROOT_5 , TAKUM16_SQUARE_ROOT_5 , TAKUM32_SQUARE_ROOT_5 , TAKUM64_SQUARE_ROOT_5 , TAKUM_LOG8_SQUARE_ROOT_5 , TAKUM_LOG16_SQUARE_ROOT_5 , TAKUM_LOG32_SQUARE_ROOT_5 , TAKUM_LOG64_SQUARE_ROOT_5 ,
the square root of 6 as
.Dv TAKUM8_SQUARE_ROOT_6 , TAKUM16_SQUARE_ROOT_6 , TAKUM32_SQUARE_ROOT_6 , TAKUM64_SQUARE_ROOT_6, TAKUM_LOG8_SQUARE_ROOT_6 , TAKUM_LOG16_SQUARE_ROOT_6 , TAKUM_LOG32_SQUARE_ROOT_6 , TAKUM_LOG64_SQUARE_ROOT_6
and one as
.Dv TAKUM8_ONE , TAKUM16_ONE , TAKUM32_ONE , TAKUM64_ONE , TAKUM_LOG8_ONE , TAKUM_LOG16_ONE , TAKUM_LOG32_ONE , TAKUM_LOG64_ONE
respectively.
.Pp
To faciliate conversion between logarithms the conversion factors are defined as well, explicitly the binary logarithm of 10 as
.Dv TAKUM8_LB_10 , TAKUM16_LB_10 , TAKUM32_LB_10 , TAKUM64_LB_10 , TAKUM_LOG8_LB_10 , TAKUM_LOG16_LB_10 , TAKUM_LOG32_LB_10 , TAKUM_LOG64_LB_10 ,
the binary logarithm of e as
.Dv TAKUM8_LB_E , TAKUM16_LB_E , TAKUM32_LB_E , TAKUM64_LB_E , TAKUM_LOG8_LB_E , TAKUM_LOG16_LB_E , TAKUM_LOG32_LB_E , TAKUM_LOG64_LB_E ,
the decadic logarithm of 2 as
.Dv TAKUM8_LG_2 , TAKUM16_LG_2 , TAKUM32_LG_2 , TAKUM64_LG_2 , TAKUM_LOG8_LG_2 , TAKUM_LOG16_LG_2 , TAKUM_LOG32_LG_2 , TAKUM_LOG64_LG_2 ,
the decadic logarithm of e as
.Dv TAKUM8_LG_E , TAKUM16_LG_E , TAKUM32_LG_E , TAKUM64_LG_E , TAKUM_LOG8_LG_E , TAKUM_LOG16_LG_E , TAKUM_LOG32_LG_E , TAKUM_LOG64_LG_E ,
the natural logarithm of 10 as
.Dv TAKUM8_LN_10 , TAKUM16_LN_10 , TAKUM32_LN_10 , TAKUM64_LN_10 , TAKUM_LOG8_LN_10 , TAKUM_LOG16_LN_10 , TAKUM_LOG32_LN_10 , TAKUM_LOG64_LN_10
and the natural logarithm of 2 as
.Dv TAKUM8_LN_2 , TAKUM16_LN_2 , TAKUM32_LN_2 , TAKUM64_LN_2 , TAKUM_LOG8_LN_2 , TAKUM_LOG16_LN_2 , TAKUM_LOG32_LN_2 , TAKUM_LOG64_LN_2
respectively.
.Pp
Given the many uses of the constant π
.Nm
specifies all reduced fractions aπ/b with a and b in {1,...,6} (which includes π,...,6π) as
.Dv TAKUM8_2_PI , TAKUM8_2_PI_OVER_3 , TAKUM8_2_PI_OVER_5 , TAKUM8_3_PI , TAKUM8_3_PI_OVER_2 , TAKUM8_3_PI_OVER_4 , TAKUM8_3_PI_OVER_5 , TAKUM8_4_PI , TAKUM8_4_PI_OVER_3 , TAKUM8_4_PI_OVER_5 , TAKUM8_5_PI , TAKUM8_5_PI_OVER_2 , TAKUM8_5_PI_OVER_3 , TAKUM8_5_PI_OVER_4 , TAKUM8_5_PI_OVER_6 , TAKUM8_6_PI , TAKUM8_6_PI_OVER_5 , TAKUM8_PI , TAKUM8_PI_OVER_2, TAKUM8_PI_OVER_3 , TAKUM8_PI_OVER_4 , TAKUM8_PI_OVER_5 , TAKUM8_PI_OVER_6 , TAKUM_LOG8_2_PI , TAKUM_LOG8_2_PI_OVER_3 , TAKUM_LOG8_2_PI_OVER_5 , TAKUM_LOG8_3_PI , TAKUM_LOG8_3_PI_OVER_2 , TAKUM_LOG8_3_PI_OVER_4 , TAKUM_LOG8_3_PI_OVER_5 , TAKUM_LOG8_4_PI , TAKUM_LOG8_4_PI_OVER_3 , TAKUM_LOG8_4_PI_OVER_5 , TAKUM_LOG8_5_PI , TAKUM_LOG8_5_PI_OVER_2 , TAKUM_LOG8_5_PI_OVER_3 , TAKUM_LOG8_5_PI_OVER_4 , TAKUM_LOG8_5_PI_OVER_6 , TAKUM_LOG8_6_PI , TAKUM_LOG8_6_PI_OVER_5 , TAKUM_LOG8_PI , TAKUM_LOG8_PI_OVER_2, TAKUM_LOG8_PI_OVER_3 , TAKUM_LOG8_PI_OVER_4 , TAKUM_LOG8_PI_OVER_5 , TAKUM_LOG8_PI_OVER_6
for
.Vt takum8 ,
.Dv TAKUM16_2_PI , TAKUM16_2_PI_OVER_3 , TAKUM16_2_PI_OVER_5 , TAKUM16_3_PI , TAKUM16_3_PI_OVER_2 , TAKUM16_3_PI_OVER_4 , TAKUM16_3_PI_OVER_5 , TAKUM16_4_PI , TAKUM16_4_PI_OVER_3 , TAKUM16_4_PI_OVER_5 , TAKUM16_5_PI , TAKUM16_5_PI_OVER_2 , TAKUM16_5_PI_OVER_3 , TAKUM16_5_PI_OVER_4 , TAKUM16_5_PI_OVER_6 , TAKUM16_6_PI , TAKUM16_6_PI_OVER_5 , TAKUM16_PI , TAKUM16_PI_OVER_2, TAKUM16_PI_OVER_3 , TAKUM16_PI_OVER_4 , TAKUM16_PI_OVER_5 , TAKUM16_PI_OVER_6 , TAKUM_LOG16_2_PI , TAKUM_LOG16_2_PI_OVER_3 , TAKUM_LOG16_2_PI_OVER_5 , TAKUM_LOG16_3_PI , TAKUM_LOG16_3_PI_OVER_2 , TAKUM_LOG16_3_PI_OVER_4 , TAKUM_LOG16_3_PI_OVER_5 , TAKUM_LOG16_4_PI , TAKUM_LOG16_4_PI_OVER_3 , TAKUM_LOG16_4_PI_OVER_5 , TAKUM_LOG16_5_PI , TAKUM_LOG16_5_PI_OVER_2 , TAKUM_LOG16_5_PI_OVER_3 , TAKUM_LOG16_5_PI_OVER_4 , TAKUM_LOG16_5_PI_OVER_6 , TAKUM_LOG16_6_PI , TAKUM_LOG16_6_PI_OVER_5 , TAKUM_LOG16_PI , TAKUM_LOG16_PI_OVER_2, TAKUM_LOG16_PI_OVER_3 , TAKUM_LOG16_PI_OVER_4 , TAKUM_LOG16_PI_OVER_5 , TAKUM_LOG16_PI_OVER_6
for
.Vt takum16 ,
.Dv TAKUM32_2_PI , TAKUM32_2_PI_OVER_3 , TAKUM32_2_PI_OVER_5 , TAKUM32_3_PI , TAKUM32_3_PI_OVER_2 , TAKUM32_3_PI_OVER_4 , TAKUM32_3_PI_OVER_5 , TAKUM32_4_PI , TAKUM32_4_PI_OVER_3 , TAKUM32_4_PI_OVER_5 , TAKUM32_5_PI , TAKUM32_5_PI_OVER_2 , TAKUM32_5_PI_OVER_3 , TAKUM32_5_PI_OVER_4 , TAKUM32_5_PI_OVER_6 , TAKUM32_6_PI , TAKUM32_6_PI_OVER_5 , TAKUM32_PI , TAKUM32_PI_OVER_2, TAKUM32_PI_OVER_3 , TAKUM32_PI_OVER_4 , TAKUM32_PI_OVER_5 , TAKUM32_PI_OVER_6 , TAKUM_LOG32_2_PI , TAKUM_LOG32_2_PI_OVER_3 , TAKUM_LOG32_2_PI_OVER_5 , TAKUM_LOG32_3_PI , TAKUM_LOG32_3_PI_OVER_2 , TAKUM_LOG32_3_PI_OVER_4 , TAKUM_LOG32_3_PI_OVER_5 , TAKUM_LOG32_4_PI , TAKUM_LOG32_4_PI_OVER_3 , TAKUM_LOG32_4_PI_OVER_5 , TAKUM_LOG32_5_PI , TAKUM_LOG32_5_PI_OVER_2 , TAKUM_LOG32_5_PI_OVER_3 , TAKUM_LOG32_5_PI_OVER_4 , TAKUM_LOG32_5_PI_OVER_6 , TAKUM_LOG32_6_PI , TAKUM_LOG32_6_PI_OVER_5 , TAKUM_LOG32_PI , TAKUM_LOG32_PI_OVER_2, TAKUM_LOG32_PI_OVER_3 , TAKUM_LOG32_PI_OVER_4 , TAKUM_LOG32_PI_OVER_5 , TAKUM_LOG32_PI_OVER_6
for
.Vt takum32
and
.Dv TAKUM64_2_PI , TAKUM64_2_PI_OVER_3 , TAKUM64_2_PI_OVER_5 , TAKUM64_3_PI , TAKUM64_3_PI_OVER_2 , TAKUM64_3_PI_OVER_4 , TAKUM64_3_PI_OVER_5 , TAKUM64_4_PI , TAKUM64_4_PI_OVER_3 , TAKUM64_4_PI_OVER_5 , TAKUM64_5_PI , TAKUM64_5_PI_OVER_2 , TAKUM64_5_PI_OVER_3 , TAKUM64_5_PI_OVER_4 , TAKUM64_5_PI_OVER_6 , TAKUM64_6_PI , TAKUM64_6_PI_OVER_5 , TAKUM64_PI , TAKUM64_PI_OVER_2, TAKUM64_PI_OVER_3 , TAKUM64_PI_OVER_4 , TAKUM64_PI_OVER_5 , TAKUM64_PI_OVER_6 , TAKUM_LOG64_2_PI , TAKUM_LOG64_2_PI_OVER_3 , TAKUM_LOG64_2_PI_OVER_5 , TAKUM_LOG64_3_PI , TAKUM_LOG64_3_PI_OVER_2 , TAKUM_LOG64_3_PI_OVER_4 , TAKUM_LOG64_3_PI_OVER_5 , TAKUM_LOG64_4_PI , TAKUM_LOG64_4_PI_OVER_3 , TAKUM_LOG64_4_PI_OVER_5 , TAKUM_LOG64_5_PI , TAKUM_LOG64_5_PI_OVER_2 , TAKUM_LOG64_5_PI_OVER_3 , TAKUM_LOG64_5_PI_OVER_4 , TAKUM_LOG64_5_PI_OVER_6 , TAKUM_LOG64_6_PI , TAKUM_LOG64_6_PI_OVER_5 , TAKUM_LOG64_PI , TAKUM_LOG64_PI_OVER_2, TAKUM_LOG64_PI_OVER_3 , TAKUM_LOG64_PI_OVER_4 , TAKUM_LOG64_PI_OVER_5 , TAKUM_LOG64_PI_OVER_6
for
.Vt takum64.
As inversion is a lossless operation for logarithmic takums, one can invert the constants to also
obtain all reduced fractions b/(aπ) with a and b in {1,...,6}.
.Sh SEE ALSO
EOF

# list all manual pages, using a phase-shift to omit a comma for the last entry
LAST_MAN3=""
for man3 in $MAN3_LIST; do
	if [ ! -z $LAST_MAN3 ]; then
		printf ".Xr $man3 3 ,\n"
	fi
	LAST_MAN3=$man3
done
if [ ! -z $LAST_MAN3 ]; then
	printf ".Xr $LAST_MAN3 3\n"
fi

cat << EOF
.Sh AUTHORS
.An Laslo Hunhold Aq Mt laslo@hunhold.de
EOF
