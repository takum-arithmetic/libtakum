export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the sum of two logarithmic takums"
export COMPUTE_LONG_DESCRIPTION="the sum of \n.Va a\nand\n.Va b "
export FUNCTION_NAME="addition"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=$(if [ -n "$SECOND_ARGUMENT_TYPE" ]; then printf "$SECOND_ARGUMENT_TYPE"; else printf "takum_log64"; fi)
export SEE_ALSO=""

$SH man/template/math_function.sh
