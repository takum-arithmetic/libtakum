export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the arctangent of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the arctangent of\n.Va a "
export FUNCTION_NAME="arctan"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="arctan_over_pi"

$SH man/template/math_function.sh
