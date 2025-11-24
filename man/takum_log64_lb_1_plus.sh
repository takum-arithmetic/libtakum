export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the binary logarithm of one plus a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the binary, i.e. base 2, logarithm of one plus\n.Va a "
export FUNCTION_NAME="lb_1_plus"
export NAN_CONDITION="\n.Va a\nis smaller than or equal to minus one"
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE=""
export SEE_ALSO="lb"

$SH man/template/math_function.sh
