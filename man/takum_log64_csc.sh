export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the cosecant of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the cosecant of\n.Va a "
export FUNCTION_NAME="csc"
export NAN_CONDITION="" # multiples of π are not exactly representable in any takum type
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="csc_pi_times"

$SH man/template/math_function.sh
