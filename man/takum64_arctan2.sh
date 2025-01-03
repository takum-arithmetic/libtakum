export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "64"; fi)
export COMPUTE_DESCRIPTION="the 2-argument arctangent of two takums"
export COMPUTE_LONG_DESCRIPTION="the 2-argument arctangent of\n.Va a\n and\n.Va b "
export FUNCTION_NAME="arctan2"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=$(if [ -n "$SECOND_ARGUMENT_TYPE" ]; then printf "$SECOND_ARGUMENT_TYPE"; else printf "takum64"; fi)
export SEE_ALSO="arctan2_over_pi"

$SH man/template/math_function.sh
