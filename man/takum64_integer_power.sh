export BIT_COUNT=$(if [ -n "$BIT_COUNT" ]; then printf "$BIT_COUNT"; else printf "64"; fi)
export COMPUTE_DESCRIPTION="the integral power of a takum"
export COMPUTE_LONG_DESCRIPTION="\n.Va a\nraised to the power of\n.Va b "
export FUNCTION_NAME="integer_power"
export NAN_CONDITION="\n.Va a\nis zero and\n.Va b\nis less than or equal to zero"
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE="int64_t"
export SEE_ALSO="power"

$SH man/template/math_function.sh