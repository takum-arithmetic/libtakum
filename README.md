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

## Author and License

libtakum is developed by Laslo Hunhold and licensed under the ISC
license. See LICENSE for copyright and license details.
