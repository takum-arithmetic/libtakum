export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the precision of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the precision, i.e. the mantissa bit count (one less than the fraction bit count for floating-point numbers), of \n.Va a "
export FUNCTION_NAME="precision"
export NAN_CONDITION=""
export RETURN_TYPE_OVERRIDE="uint8_t"
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO=""

$SH man/template/math_function.sh
