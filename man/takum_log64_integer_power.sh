export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the integral power of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="\n.Va a\nraised to the power of\n.Va b "
export FUNCTION_NAME="integer_power"
export NAN_CONDITION="\n.Va a\nis zero and\n.Va b\nis less than or equal to zero"
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE="int64_t"
export SEE_ALSO="power"

$SH man/template/math_function.sh
