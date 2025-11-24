export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the sine of π times a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the sine of π times \n.Va a "
export FUNCTION_NAME="sin_pi_times"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="sin"

$SH man/template/math_function.sh
