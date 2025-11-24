/* See LICENSE file for copyright and license details. */
#include <inttypes.h>
#include <stdio.h>

#include "../takum.h"
#include "util.h"

struct {
	const char *name;
	long double value;
	takum8 takum8_value;
	takum16 takum16_value;
	takum32 takum32_value;
	takum64 takum64_value;
	takum_log8 takum_log8_value;
	takum_log16 takum_log16_value;
	takum_log32 takum_log32_value;
	takum_log64 takum_log64_value;
} constant_tests[] = {
	{
		.name = "2π",
		.value = 6.2831853071795864769252867665590057683943L,
		.takum8_value = TAKUM8_2_PI,
		.takum16_value = TAKUM16_2_PI,
		.takum32_value = TAKUM32_2_PI,
		.takum64_value = TAKUM64_2_PI,
		.takum_log8_value = TAKUM_LOG8_2_PI,
		.takum_log16_value = TAKUM_LOG16_2_PI,
		.takum_log32_value = TAKUM_LOG32_2_PI,
		.takum_log64_value = TAKUM_LOG64_2_PI,
	},
	{
		.name = "2π/3",
		.value = 2.0943951023931954923084289221863352561314L,
		.takum8_value = TAKUM8_2_PI_OVER_3,
		.takum16_value = TAKUM16_2_PI_OVER_3,
		.takum32_value = TAKUM32_2_PI_OVER_3,
		.takum64_value = TAKUM64_2_PI_OVER_3,
		.takum_log8_value = TAKUM_LOG8_2_PI_OVER_3,
		.takum_log16_value = TAKUM_LOG16_2_PI_OVER_3,
		.takum_log32_value = TAKUM_LOG32_2_PI_OVER_3,
		.takum_log64_value = TAKUM_LOG64_2_PI_OVER_3,
	},
	{
		.name = "2π/5",
		.value = 1.2566370614359172953850573533118011536789L,
		.takum8_value = TAKUM8_2_PI_OVER_5,
		.takum16_value = TAKUM16_2_PI_OVER_5,
		.takum32_value = TAKUM32_2_PI_OVER_5,
		.takum64_value = TAKUM64_2_PI_OVER_5,
		.takum_log8_value = TAKUM_LOG8_2_PI_OVER_5,
		.takum_log16_value = TAKUM_LOG16_2_PI_OVER_5,
		.takum_log32_value = TAKUM_LOG32_2_PI_OVER_5,
		.takum_log64_value = TAKUM_LOG64_2_PI_OVER_5,
	},
	{
		.name = "3π",
		.value = 9.4247779607693797153879301498385086525915L,
		.takum8_value = TAKUM8_3_PI,
		.takum16_value = TAKUM16_3_PI,
		.takum32_value = TAKUM32_3_PI,
		.takum64_value = TAKUM64_3_PI,
		.takum_log8_value = TAKUM_LOG8_3_PI,
		.takum_log16_value = TAKUM_LOG16_3_PI,
		.takum_log32_value = TAKUM_LOG32_3_PI,
		.takum_log64_value = TAKUM_LOG64_3_PI,
	},
	{
		.name = "3π/2",
		.value = 4.7123889803846898576939650749192543262958L,
		.takum8_value = TAKUM8_3_PI_OVER_2,
		.takum16_value = TAKUM16_3_PI_OVER_2,
		.takum32_value = TAKUM32_3_PI_OVER_2,
		.takum64_value = TAKUM64_3_PI_OVER_2,
		.takum_log8_value = TAKUM_LOG8_3_PI_OVER_2,
		.takum_log16_value = TAKUM_LOG16_3_PI_OVER_2,
		.takum_log32_value = TAKUM_LOG32_3_PI_OVER_2,
		.takum_log64_value = TAKUM_LOG64_3_PI_OVER_2,
	},
	{
		.name = "3π/4",
		.value = 2.3561944901923449288469825374596271631479L,
		.takum8_value = TAKUM8_3_PI_OVER_4,
		.takum16_value = TAKUM16_3_PI_OVER_4,
		.takum32_value = TAKUM32_3_PI_OVER_4,
		.takum64_value = TAKUM64_3_PI_OVER_4,
		.takum_log8_value = TAKUM_LOG8_3_PI_OVER_4,
		.takum_log16_value = TAKUM_LOG16_3_PI_OVER_4,
		.takum_log32_value = TAKUM_LOG32_3_PI_OVER_4,
		.takum_log64_value = TAKUM_LOG64_3_PI_OVER_4,
	},
	{
		.name = "3π/5",
		.value = 1.8849555921538759430775860299677017305183L,
		.takum8_value = TAKUM8_3_PI_OVER_5,
		.takum16_value = TAKUM16_3_PI_OVER_5,
		.takum32_value = TAKUM32_3_PI_OVER_5,
		.takum64_value = TAKUM64_3_PI_OVER_5,
		.takum_log8_value = TAKUM_LOG8_3_PI_OVER_5,
		.takum_log16_value = TAKUM_LOG16_3_PI_OVER_5,
		.takum_log32_value = TAKUM_LOG32_3_PI_OVER_5,
		.takum_log64_value = TAKUM_LOG64_3_PI_OVER_5,
	},
	{
		.name = "4π",
		.value = 12.566370614359172953850573533118011536789L,
		.takum8_value = TAKUM8_4_PI,
		.takum16_value = TAKUM16_4_PI,
		.takum32_value = TAKUM32_4_PI,
		.takum64_value = TAKUM64_4_PI,
		.takum_log8_value = TAKUM_LOG8_4_PI,
		.takum_log16_value = TAKUM_LOG16_4_PI,
		.takum_log32_value = TAKUM_LOG32_4_PI,
		.takum_log64_value = TAKUM_LOG64_4_PI,
	},
	{
		.name = "4π/3",
		.value = 4.1887902047863909846168578443726705122629L,
		.takum8_value = TAKUM8_4_PI_OVER_3,
		.takum16_value = TAKUM16_4_PI_OVER_3,
		.takum32_value = TAKUM32_4_PI_OVER_3,
		.takum64_value = TAKUM64_4_PI_OVER_3,
		.takum_log8_value = TAKUM_LOG8_4_PI_OVER_3,
		.takum_log16_value = TAKUM_LOG16_4_PI_OVER_3,
		.takum_log32_value = TAKUM_LOG32_4_PI_OVER_3,
		.takum_log64_value = TAKUM_LOG64_4_PI_OVER_3,
	},
	{
		.name = "4π/5",
		.value = 2.5132741228718345907701147066236023073577L,
		.takum8_value = TAKUM8_4_PI_OVER_5,
		.takum16_value = TAKUM16_4_PI_OVER_5,
		.takum32_value = TAKUM32_4_PI_OVER_5,
		.takum64_value = TAKUM64_4_PI_OVER_5,
		.takum_log8_value = TAKUM_LOG8_4_PI_OVER_5,
		.takum_log16_value = TAKUM_LOG16_4_PI_OVER_5,
		.takum_log32_value = TAKUM_LOG32_4_PI_OVER_5,
		.takum_log64_value = TAKUM_LOG64_4_PI_OVER_5,
	},
	{
		.name = "5π",
		.value = 15.707963267948966192313216916397514420986L,
		.takum8_value = TAKUM8_5_PI,
		.takum16_value = TAKUM16_5_PI,
		.takum32_value = TAKUM32_5_PI,
		.takum64_value = TAKUM64_5_PI,
		.takum_log8_value = TAKUM_LOG8_5_PI,
		.takum_log16_value = TAKUM_LOG16_5_PI,
		.takum_log32_value = TAKUM_LOG32_5_PI,
		.takum_log64_value = TAKUM_LOG64_5_PI,
	},
	{
		.name = "5π/2",
		.value = 7.8539816339744830961566084581987572104929L,
		.takum8_value = TAKUM8_5_PI_OVER_2,
		.takum16_value = TAKUM16_5_PI_OVER_2,
		.takum32_value = TAKUM32_5_PI_OVER_2,
		.takum64_value = TAKUM64_5_PI_OVER_2,
		.takum_log8_value = TAKUM_LOG8_5_PI_OVER_2,
		.takum_log16_value = TAKUM_LOG16_5_PI_OVER_2,
		.takum_log32_value = TAKUM_LOG32_5_PI_OVER_2,
		.takum_log64_value = TAKUM_LOG64_5_PI_OVER_2,
	},
	{
		.name = "5π/3",
		.value = 5.2359877559829887307710723054658381403286L,
		.takum8_value = TAKUM8_5_PI_OVER_3,
		.takum16_value = TAKUM16_5_PI_OVER_3,
		.takum32_value = TAKUM32_5_PI_OVER_3,
		.takum64_value = TAKUM64_5_PI_OVER_3,
		.takum_log8_value = TAKUM_LOG8_5_PI_OVER_3,
		.takum_log16_value = TAKUM_LOG16_5_PI_OVER_3,
		.takum_log32_value = TAKUM_LOG32_5_PI_OVER_3,
		.takum_log64_value = TAKUM_LOG64_5_PI_OVER_3,
	},
	{
		.name = "5π/4",
		.value = 3.9269908169872415480783042290993786052465L,
		.takum8_value = TAKUM8_5_PI_OVER_4,
		.takum16_value = TAKUM16_5_PI_OVER_4,
		.takum32_value = TAKUM32_5_PI_OVER_4,
		.takum64_value = TAKUM64_5_PI_OVER_4,
		.takum_log8_value = TAKUM_LOG8_5_PI_OVER_4,
		.takum_log16_value = TAKUM_LOG16_5_PI_OVER_4,
		.takum_log32_value = TAKUM_LOG32_5_PI_OVER_4,
		.takum_log64_value = TAKUM_LOG64_5_PI_OVER_4,
	},
	{
		.name = "5π/6",
		.value = 2.6179938779914943653855361527329190701643L,
		.takum8_value = TAKUM8_5_PI_OVER_6,
		.takum16_value = TAKUM16_5_PI_OVER_6,
		.takum32_value = TAKUM32_5_PI_OVER_6,
		.takum64_value = TAKUM64_5_PI_OVER_6,
		.takum_log8_value = TAKUM_LOG8_5_PI_OVER_6,
		.takum_log16_value = TAKUM_LOG16_5_PI_OVER_6,
		.takum_log32_value = TAKUM_LOG32_5_PI_OVER_6,
		.takum_log64_value = TAKUM_LOG64_5_PI_OVER_6,
	},
	{
		.name = "6π",
		.value = 18.849555921538759430775860299677017305183L,
		.takum8_value = TAKUM8_6_PI,
		.takum16_value = TAKUM16_6_PI,
		.takum32_value = TAKUM32_6_PI,
		.takum64_value = TAKUM64_6_PI,
		.takum_log8_value = TAKUM_LOG8_6_PI,
		.takum_log16_value = TAKUM_LOG16_6_PI,
		.takum_log32_value = TAKUM_LOG32_6_PI,
		.takum_log64_value = TAKUM_LOG64_6_PI,
	},
	{
		.name = "6π/5",
		.value = 3.7699111843077518861551720599354034610366L,
		.takum8_value = TAKUM8_6_PI_OVER_5,
		.takum16_value = TAKUM16_6_PI_OVER_5,
		.takum32_value = TAKUM32_6_PI_OVER_5,
		.takum64_value = TAKUM64_6_PI_OVER_5,
		.takum_log8_value = TAKUM_LOG8_6_PI_OVER_5,
		.takum_log16_value = TAKUM_LOG16_6_PI_OVER_5,
		.takum_log32_value = TAKUM_LOG32_6_PI_OVER_5,
		.takum_log64_value = TAKUM_LOG64_6_PI_OVER_5,
	},
	{
		.name = "γ",
		.value = 0.5772156649015328606065120900824024310422L,
		.takum8_value = TAKUM8_GAMMA,
		.takum16_value = TAKUM16_GAMMA,
		.takum32_value = TAKUM32_GAMMA,
		.takum64_value = TAKUM64_GAMMA,
		.takum_log8_value = TAKUM_LOG8_GAMMA,
		.takum_log16_value = TAKUM_LOG16_GAMMA,
		.takum_log32_value = TAKUM_LOG32_GAMMA,
		.takum_log64_value = TAKUM_LOG64_GAMMA,
	},
	{
		.name = "lb(10)",
		.value = 3.3219280948873623478703194294893901758648L,
		.takum8_value = TAKUM8_LB_10,
		.takum16_value = TAKUM16_LB_10,
		.takum32_value = TAKUM32_LB_10,
		.takum64_value = TAKUM64_LB_10,
		.takum_log8_value = TAKUM_LOG8_LB_10,
		.takum_log16_value = TAKUM_LOG16_LB_10,
		.takum_log32_value = TAKUM_LOG32_LB_10,
		.takum_log64_value = TAKUM_LOG64_LB_10,
	},
	{
		.name = "lb(e)",
		.value = 1.4426950408889634073599246810018921374266L,
		.takum8_value = TAKUM8_LB_E,
		.takum16_value = TAKUM16_LB_E,
		.takum32_value = TAKUM32_LB_E,
		.takum64_value = TAKUM64_LB_E,
		.takum_log8_value = TAKUM_LOG8_LB_E,
		.takum_log16_value = TAKUM_LOG16_LB_E,
		.takum_log32_value = TAKUM_LOG32_LB_E,
		.takum_log64_value = TAKUM_LOG64_LB_E,
	},
	{
		.name = "lg(2)",
		.value = 0.3010299956639811952137388947244930267682L,
		.takum8_value = TAKUM8_LG_2,
		.takum16_value = TAKUM16_LG_2,
		.takum32_value = TAKUM32_LG_2,
		.takum64_value = TAKUM64_LG_2,
		.takum_log8_value = TAKUM_LOG8_LG_2,
		.takum_log16_value = TAKUM_LOG16_LG_2,
		.takum_log32_value = TAKUM_LOG32_LG_2,
		.takum_log64_value = TAKUM_LOG64_LG_2,
	},
	{
		.name = "lg(e)",
		.value = 0.4342944819032518276511289189166050822944L,
		.takum8_value = TAKUM8_LG_E,
		.takum16_value = TAKUM16_LG_E,
		.takum32_value = TAKUM32_LG_E,
		.takum64_value = TAKUM64_LG_E,
		.takum_log8_value = TAKUM_LOG8_LG_E,
		.takum_log16_value = TAKUM_LOG16_LG_E,
		.takum_log32_value = TAKUM_LOG32_LG_E,
		.takum_log64_value = TAKUM_LOG64_LG_E,
	},
	{
		.name = "ln(10)",
		.value = 2.3025850929940456840179914546843642076011L,
		.takum8_value = TAKUM8_LN_10,
		.takum16_value = TAKUM16_LN_10,
		.takum32_value = TAKUM32_LN_10,
		.takum64_value = TAKUM64_LN_10,
		.takum_log8_value = TAKUM_LOG8_LN_10,
		.takum_log16_value = TAKUM_LOG16_LN_10,
		.takum_log32_value = TAKUM_LOG32_LN_10,
		.takum_log64_value = TAKUM_LOG64_LN_10,
	},
	{
		.name = "ln(2)",
		.value = 0.6931471805599453094172321214581765680755L,
		.takum8_value = TAKUM8_LN_2,
		.takum16_value = TAKUM16_LN_2,
		.takum32_value = TAKUM32_LN_2,
		.takum64_value = TAKUM64_LN_2,
		.takum_log8_value = TAKUM_LOG8_LN_2,
		.takum_log16_value = TAKUM_LOG16_LN_2,
		.takum_log32_value = TAKUM_LOG32_LN_2,
		.takum_log64_value = TAKUM_LOG64_LN_2,
	},
	{
		.name = "1",
		.value = 1.0L,
		.takum8_value = TAKUM8_ONE,
		.takum16_value = TAKUM16_ONE,
		.takum32_value = TAKUM32_ONE,
		.takum64_value = TAKUM64_ONE,
		.takum_log8_value = TAKUM_LOG8_ONE,
		.takum_log16_value = TAKUM_LOG16_ONE,
		.takum_log32_value = TAKUM_LOG32_ONE,
		.takum_log64_value = TAKUM_LOG64_ONE,
	},
	{
		.name = "φ",
		.value = 1.6180339887498948482045868343656381177203L,
		.takum8_value = TAKUM8_PHI,
		.takum16_value = TAKUM16_PHI,
		.takum32_value = TAKUM32_PHI,
		.takum64_value = TAKUM64_PHI,
		.takum_log8_value = TAKUM_LOG8_PHI,
		.takum_log16_value = TAKUM_LOG16_PHI,
		.takum_log32_value = TAKUM_LOG32_PHI,
		.takum_log64_value = TAKUM_LOG64_PHI,
	},
	{
		.name = "π",
		.value = 3.1415926535897932384626433832795028841972L,
		.takum8_value = TAKUM8_PI,
		.takum16_value = TAKUM16_PI,
		.takum32_value = TAKUM32_PI,
		.takum64_value = TAKUM64_PI,
		.takum_log8_value = TAKUM_LOG8_PI,
		.takum_log16_value = TAKUM_LOG16_PI,
		.takum_log32_value = TAKUM_LOG32_PI,
		.takum_log64_value = TAKUM_LOG64_PI,
	},
	{
		.name = "π/2",
		.value = 1.5707963267948966192313216916397514420986L,
		.takum8_value = TAKUM8_PI_OVER_2,
		.takum16_value = TAKUM16_PI_OVER_2,
		.takum32_value = TAKUM32_PI_OVER_2,
		.takum64_value = TAKUM64_PI_OVER_2,
		.takum_log8_value = TAKUM_LOG8_PI_OVER_2,
		.takum_log16_value = TAKUM_LOG16_PI_OVER_2,
		.takum_log32_value = TAKUM_LOG32_PI_OVER_2,
		.takum_log64_value = TAKUM_LOG64_PI_OVER_2,
	},
	{
		.name = "π/3",
		.value = 1.0471975511965977461542144610931676280657L,
		.takum8_value = TAKUM8_PI_OVER_3,
		.takum16_value = TAKUM16_PI_OVER_3,
		.takum32_value = TAKUM32_PI_OVER_3,
		.takum64_value = TAKUM64_PI_OVER_3,
		.takum_log8_value = TAKUM_LOG8_PI_OVER_3,
		.takum_log16_value = TAKUM_LOG16_PI_OVER_3,
		.takum_log32_value = TAKUM_LOG32_PI_OVER_3,
		.takum_log64_value = TAKUM_LOG64_PI_OVER_3,
	},
	{
		.name = "π/4",
		.value = 0.78539816339744830961566084581987572104929L,
		.takum8_value = TAKUM8_PI_OVER_4,
		.takum16_value = TAKUM16_PI_OVER_4,
		.takum32_value = TAKUM32_PI_OVER_4,
		.takum64_value = TAKUM64_PI_OVER_4,
		.takum_log8_value = TAKUM_LOG8_PI_OVER_4,
		.takum_log16_value = TAKUM_LOG16_PI_OVER_4,
		.takum_log32_value = TAKUM_LOG32_PI_OVER_4,
		.takum_log64_value = TAKUM_LOG64_PI_OVER_4,
	},
	{
		.name = "π/5",
		.value = 0.62831853071795864769252867665590057683943L,
		.takum8_value = TAKUM8_PI_OVER_5,
		.takum16_value = TAKUM16_PI_OVER_5,
		.takum32_value = TAKUM32_PI_OVER_5,
		.takum64_value = TAKUM64_PI_OVER_5,
		.takum_log8_value = TAKUM_LOG8_PI_OVER_5,
		.takum_log16_value = TAKUM_LOG16_PI_OVER_5,
		.takum_log32_value = TAKUM_LOG32_PI_OVER_5,
		.takum_log64_value = TAKUM_LOG64_PI_OVER_5,
	},
	{
		.name = "π/6",
		.value = 0.52359877559829887307710723054658381403286L,
		.takum8_value = TAKUM8_PI_OVER_6,
		.takum16_value = TAKUM16_PI_OVER_6,
		.takum32_value = TAKUM32_PI_OVER_6,
		.takum64_value = TAKUM64_PI_OVER_6,
		.takum_log8_value = TAKUM_LOG8_PI_OVER_6,
		.takum_log16_value = TAKUM_LOG16_PI_OVER_6,
		.takum_log32_value = TAKUM_LOG32_PI_OVER_6,
		.takum_log64_value = TAKUM_LOG64_PI_OVER_6,
	},
	{
		.name = "√2",
		.value = 1.4142135623730950488016887242096980785697L,
		.takum8_value = TAKUM8_SQUARE_ROOT_2,
		.takum16_value = TAKUM16_SQUARE_ROOT_2,
		.takum32_value = TAKUM32_SQUARE_ROOT_2,
		.takum64_value = TAKUM64_SQUARE_ROOT_2,
		.takum_log8_value = TAKUM_LOG8_SQUARE_ROOT_2,
		.takum_log16_value = TAKUM_LOG16_SQUARE_ROOT_2,
		.takum_log32_value = TAKUM_LOG32_SQUARE_ROOT_2,
		.takum_log64_value = TAKUM_LOG64_SQUARE_ROOT_2,
	},
	{
		.name = "√3",
		.value = 1.7320508075688772935274463415058723669428L,
		.takum8_value = TAKUM8_SQUARE_ROOT_3,
		.takum16_value = TAKUM16_SQUARE_ROOT_3,
		.takum32_value = TAKUM32_SQUARE_ROOT_3,
		.takum64_value = TAKUM64_SQUARE_ROOT_3,
		.takum_log8_value = TAKUM_LOG8_SQUARE_ROOT_3,
		.takum_log16_value = TAKUM_LOG16_SQUARE_ROOT_3,
		.takum_log32_value = TAKUM_LOG32_SQUARE_ROOT_3,
		.takum_log64_value = TAKUM_LOG64_SQUARE_ROOT_3,
	},
	{
		.name = "√5",
		.value = 2.2360679774997896964091736687312762354406L,
		.takum8_value = TAKUM8_SQUARE_ROOT_5,
		.takum16_value = TAKUM16_SQUARE_ROOT_5,
		.takum32_value = TAKUM32_SQUARE_ROOT_5,
		.takum64_value = TAKUM64_SQUARE_ROOT_5,
		.takum_log8_value = TAKUM_LOG8_SQUARE_ROOT_5,
		.takum_log16_value = TAKUM_LOG16_SQUARE_ROOT_5,
		.takum_log32_value = TAKUM_LOG32_SQUARE_ROOT_5,
		.takum_log64_value = TAKUM_LOG64_SQUARE_ROOT_5,
	},
	{
		.name = "√6",
		.value = 2.4494897427831780981972840747058913919659L,
		.takum8_value = TAKUM8_SQUARE_ROOT_6,
		.takum16_value = TAKUM16_SQUARE_ROOT_6,
		.takum32_value = TAKUM32_SQUARE_ROOT_6,
		.takum64_value = TAKUM64_SQUARE_ROOT_6,
		.takum_log8_value = TAKUM_LOG8_SQUARE_ROOT_6,
		.takum_log16_value = TAKUM_LOG16_SQUARE_ROOT_6,
		.takum_log32_value = TAKUM_LOG32_SQUARE_ROOT_6,
		.takum_log64_value = TAKUM_LOG64_SQUARE_ROOT_6,
	},
};

int
main(int argc, char *argv[])
{
	size_t i, failed_count;
	takum8 takum8_reference_value;
	takum16 takum16_reference_value;
	takum32 takum32_reference_value;
	takum64 takum64_reference_value;
	takum_log8 takum_log8_reference_value;
	takum_log16 takum_log16_reference_value;
	takum_log32 takum_log32_reference_value;
	takum_log64 takum_log64_reference_value;

	(void)argc;
	argv0 = argv[0];

	for (i = 0, failed_count = 0; i < LEN(constant_tests); i++) {
		takum8_reference_value =
			takum8_from_extended_float(constant_tests[i].value);

		if (constant_tests[i].takum8_value != takum8_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum8 unit test "
			        "(constant wrongly defined as %" PRIi8
			        " instead of %" PRIi8 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum8_value,
			        takum8_reference_value);
			failed_count++;
		}

		takum16_reference_value =
			takum16_from_extended_float(constant_tests[i].value);

		if (constant_tests[i].takum16_value !=
		    takum16_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum16 unit test "
			        "(constant wrongly defined as %" PRIi16
			        " instead of %" PRIi16 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum16_value,
			        takum16_reference_value);
			failed_count++;
		}

		takum32_reference_value =
			takum32_from_extended_float(constant_tests[i].value);

		if (constant_tests[i].takum32_value !=
		    takum32_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum32 unit test "
			        "(constant wrongly defined as %" PRIi32
			        " instead of %" PRIi32 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum32_value,
			        takum32_reference_value);
			failed_count++;
		}

		takum64_reference_value =
			takum64_from_extended_float(constant_tests[i].value);

		if (constant_tests[i].takum64_value !=
		    takum64_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum64 unit test "
			        "(constant wrongly defined as %" PRIi64
			        " instead of %" PRIi64 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum64_value,
			        takum64_reference_value);
			failed_count++;
		}

		takum_log8_reference_value =
			takum_log8_from_extended_float(constant_tests[i].value);

		if (constant_tests[i].takum_log8_value !=
		    takum_log8_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum_log8 unit test "
			        "(constant wrongly defined as %" PRIi8
			        " instead of %" PRIi8 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum_log8_value,
			        takum_log8_reference_value);
			failed_count++;
		}

		takum_log16_reference_value = takum_log16_from_extended_float(
			constant_tests[i].value);

		if (constant_tests[i].takum_log16_value !=
		    takum_log16_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum_log16 unit test "
			        "(constant wrongly defined as %" PRIi16
			        " instead of %" PRIi16 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum_log16_value,
			        takum_log16_reference_value);
			failed_count++;
		}

		takum_log32_reference_value = takum_log32_from_extended_float(
			constant_tests[i].value);

		if (constant_tests[i].takum_log32_value !=
		    takum_log32_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum_log32 unit test "
			        "(constant wrongly defined as %" PRIi32
			        " instead of %" PRIi32 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum_log32_value,
			        takum_log32_reference_value);
			failed_count++;
		}

		takum_log64_reference_value = takum_log64_from_extended_float(
			constant_tests[i].value);

		if (constant_tests[i].takum_log64_value !=
		    takum_log64_reference_value) {
			fprintf(stderr,
			        "%s: %s: Failed takum_log64 unit test "
			        "(constant wrongly defined as %" PRIi64
			        " instead of %" PRIi64 ")\n",
			        argv0, constant_tests[i].name,
			        constant_tests[i].takum_log64_value,
			        takum_log64_reference_value);
			failed_count++;
		}
	}

	printf("%s: %zu/%zu unit tests passed.\n", argv0,
	       8 * LEN(constant_tests) - failed_count, 8 * LEN(constant_tests));

	return failed_count;
}
