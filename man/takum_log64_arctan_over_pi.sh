export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the arctangent of a logarithmic takum, divided by π"
export COMPUTE_LONG_DESCRIPTION="the arctangent of\n.Va a ,\ndivided by π"
export FUNCTION_NAME="arctan_over_pi"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="arctan"

$SH man/template/math_function.sh
