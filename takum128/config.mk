# Customise below to fit your system.
#
# This is a separate, opt-in build: takum128/takum_log128 need MPFR/GMP
# (LGPL) for genuine 128-bit-quality arithmetic (see ../README.md), so
# building this is a deliberate extra step -- it never happens as a side
# effect of building/installing the root ../libtakum.

# paths (unset $PCPREFIX to not install a pkg-config file); defaults
# match the root ../config.mk so both install under the same prefix
DESTDIR   =
PREFIX    = /usr/local
INCPREFIX = $(PREFIX)/include
LIBPREFIX = $(PREFIX)/lib
LICPREFIX = $(PREFIX)/share/licenses
MANPREFIX = $(PREFIX)/share/man
PCPREFIX  = $(LIBPREFIX)/pkgconfig

# names
ANAME     = libtakum128.a
SONAME    = libtakum128.so.$(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)
BINSUFFIX =

# flags
#
# -std=gnu99 rather than -std=c99: __int128 and MPFR/GMP's headers are
# not strict-C99-clean, so -Wpedantic is dropped too (unlike the root
# library, which stays strict C99).
CPPFLAGS = -D_ISOC99_SOURCE
CFLAGS   = -std=gnu99 -O2 -Wall -Wextra
LDFLAGS  = -s
LDLIBS   = -lmpfr -lgmp -lm

SHFLAGS   = -fPIC
SOFLAGS   = -shared -Wl,--soname=libtakum128.so.$(VERSION_MAJOR).$(VERSION_MINOR)
SOSYMLINK = true

# tools (unset $LDCONFIG to not call ldconfig(1) after install/uninstall)
CC       = cc
AR       = ar
RANLIB   = ranlib
LDCONFIG = ldconfig
SH       = sh
