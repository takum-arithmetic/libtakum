export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the base 2 exponential function minus 1 of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="2 raised to \n.Va a ,\nminus one"
export FUNCTION_NAME="2_raised_minus_1"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="2_raised"

$SH man/template/math_function.sh
