export BIT_COUNT=$(if [ -n "$BIT_COUNT" ]; then printf "$BIT_COUNT"; else printf "64"; fi)
export COMPUTE_DESCRIPTION="the inverse of a takum"
export COMPUTE_LONG_DESCRIPTION="the inverse of\n.Va a "
export FUNCTION_NAME="inversion"
export NAN_CONDITION="\n.Va a\nis zero"
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO=""

$SH man/template/math_function.sh