export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_linear64"; fi)
export COMPUTE_DESCRIPTION="the natural logarithm of one plus a linear takum"
export COMPUTE_LONG_DESCRIPTION="the natural, i.e. base e, logarithm of one plus\n.Va a "
export FUNCTION_NAME="ln_1_plus"
export NAN_CONDITION="\n.Va a\nis smaller than or equal to minus one"
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="ln"

$SH man/template/math_function.sh
