export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the arccotangent of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the arccotangent of\n.Va a "
export FUNCTION_NAME="arccot"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="arccot_over_pi"

$SH man/template/math_function.sh
