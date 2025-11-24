export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the area hyperbolic cosine of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the area hyperbolic cosine of\n.Va a "
export FUNCTION_NAME="arcosh"
export NAN_CONDITION="\n.Va a\nis smaller than one"
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO=""

$SH man/template/math_function.sh
