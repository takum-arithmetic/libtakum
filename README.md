# libtakum

This ISO C99 library is a reference implementation of
[takum arithmetic](https://arxiv.org/abs/2404.18603), a new tapered
precision machine number format.

Eight data types are defined, namely `takum8`, `takum16`, `takum32`,
`takum64` for the (floating-point) takums and `takum_log8`,
`takum_log16`, `takum_log32` and `takum_log64` for the
logarithmic takums, a logarithmic number system.

A wide range of functions is implemented, including a full set of
trigonometric functions and a selection of constants. Please refer to
libtakum(7) for an overview.

Using this package one is able to evaluate takums for real-world applications
in terms of precision. Given it is a software implementation the performance
is overall worse than the respective usual IEEE 754 floating-point hardware
implementations, but it is sufficient to evaluate the formats for reasonably
sized numerical benchmarks.

## Getting started

You can automatically configure and install libtakum (including manuals)
via

```sh
./configure
make -j install
```

The `-j` flag is optional and enables the parallel processing of the make
rules, yielding a significant speedup. You can also specify it as `-j N`
(where N is, for example, the number of CPU threads) for more fine-grained
control.

The suite of unit tests is run with

```sh
make -j test
```

The manual pages are accessed via man(1). Every function is fully
documented.

```sh
man libtakum
man takum16_from_float64
man takum_log32_csch
```

The library also comes with examples. One example is a full-fledged
multi-precision RPN calculator which is run via

```sh
make -j example
./example/calculator
```

## Example

As follows a simple example is given:

```C
#include <stdio.h>
#include <takum.h>

int
main(void)
{
	takum16 a, b;

	a = takum16_from_float64(4.5);
	b = takum16_from_float64(6.5);

	printf("4.5 + 6.5 = %f\n",
	       takum16_to_float64(takum16_addition(a, b)));

	return 0;
}
```

The example is compiled and run with

```sh
cc -o example example.c -ltakum
./example
```

## Optional: takum128

`takum128`/`takum_log128` (in `takum128.h`) are an experimental, **opt-in**
extension providing 128-bit takums, built entirely separately from the rest
of this library -- building or installing libtakum never builds, links
against, or otherwise depends on any of this.

The reason it's separate: a takum128's mantissa can be up to 123 bits wide,
far beyond what any hardware `float`/`double`/`long double` can hold, which
is how every other width in this library implements its arithmetic (decode
to the widest native float, call libm, re-encode). Getting genuine
128-bit-quality results instead requires arbitrary-precision arithmetic, so
`takum128`'s implementation is backed by [MPFR](https://www.mpfr.org/)
(and GMP) -- both LGPL, unlike the rest of this ISC-licensed, otherwise
dependency-free (just `libm`) library. Treat that dependency as a deliberate
choice you're opting into, not a transitive requirement of libtakum itself.

Implements the full function set from libtakum.h: arithmetic (`absolute`,
`sign`, `precision`, `addition`, `subtraction`, `multiplication`,
`division`, `square_root`, `hypotenuse`, `inversion`, `integer_power`,
`root`), conversions to/from `float32`/`float64`/extended float, to/from
every other takum/takum_log width, and between `takum128` and
`takum_log128`, exponentials/logarithms/`power` (`exp`, `exp_minus_1`,
`2_raised`, `2_raised_minus_1`, `10_raised`, `10_raised_minus_1`, `lb`,
`lb_1_plus`, `lg`, `lg_1_plus`, `ln`, `ln_1_plus`, `power`), the full
trigonometric/hyperbolic family (`sin`/`cos`/`tan`/`cot`/`sec`/`csc` and
their hyperbolic and inverse forms, the `_pi_times`/`_over_pi` variants,
and `arctan2`/`arctan2_over_pi`), and the named-constant table (2pi, pi,
gamma, phi, sqrt(2), lb(e), ...) -- almost all backed directly by MPFR's
own correctly-rounded primitives (MPFR &ge; 4.2, for `mpfr_exp2m1`,
`mpfr_log2p1`, `mpfr_sinpi`, `mpfr_atanpi` and friends), with a handful
of small documented composites (`arccot`, `arcsec`, `arccsc`, `arcoth`,
`arsech`, `arcsch`, and the `_pi_times` forms of `cot`/`sec`/`csc`) where
MPFR has no direct equivalent. Manual pages are in `takum128/man`
(`man takum128/man/libtakum128.7` before installing, or `man libtakum128`
after); per-function semantics are documented once, on the corresponding
`takum64_*`/`takum_log64_*` page, since they don't otherwise differ by
width.

One consequence of the fixed (not width-scaling) characteristic field takum
uses for its regime/exponent: `takum128`'s dynamic range is the *same* as
every other width (up to roughly ±2^255) -- only precision grows with width,
not range. `takum128` is precision-only headroom over `takum64`, not a
bigger-range replacement for it.

Build and test it with:

```sh
cd takum128
$(EDITOR) config.mk   # point at your MPFR/GMP install if not on the default path
make -j
make -j test
```

## Author and License

libtakum is developed by Laslo Hunhold and licensed under the ISC
license. See LICENSE for copyright and license details.
