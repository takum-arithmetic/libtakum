export TAKUM_TYPE_SUFFIX=$(if [ -n "$TAKUM_TYPE_SUFFIX" ]; then printf "$TAKUM_TYPE_SUFFIX"; else printf "_log64"; fi)
export FLOAT_LONG_NAME="an IEEE 754 double-precision floating-point number"
export FLOAT_NAME="float64"
export FLOAT_TYPE="double"

$SH man/template/conversion_from_float.sh
