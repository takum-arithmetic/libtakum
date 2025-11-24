export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export COMPUTE_DESCRIPTION="the integral root of a logarithmic takum"
export COMPUTE_LONG_DESCRIPTION="the\n.Va b\nth root of\n.Va a "
export FUNCTION_NAME="root"
export NAN_CONDITION="\n.Va a\nand\n.Va b\nare zero, or\n.Va a\nis smaller than zero and\n.Va b\nis even"
export RETURN_TYPE_OVERRIDE=""
export SECOND_ARGUMENT_TYPE="int64_t"
export SEE_ALSO="square_root"

$SH man/template/math_function.sh
