# See LICENSE file for copyright and license details
# takum128 - optional 128-bit takum/takum_log extension for libtakum,
# backed by MPFR/GMP. See ../README.md for why this is a separate,
# opt-in build rather than part of the root Makefile.
.POSIX:
.SUFFIXES:

VERSION_MAJOR = 0
VERSION_MINOR = 3
VERSION_PATCH = 0
MAN_DATE = 2026-09-05

include config.mk

VERSION = $(VERSION_MAJOR).$(VERSION_MINOR).$(VERSION_PATCH)

# every implemented function's base name (shared by both takum128_NAME
# and takum_log128_NAME, and by the takum64_NAME manual page that
# documents their semantics -- see man/libtakum128.sh)
MAN3_BASE_NAMES =\
	10_raised 10_raised_minus_1 2_raised 2_raised_minus_1 absolute\
	addition arccos arccos_over_pi arccot arccot_over_pi arccsc\
	arccsc_over_pi arcosh arcoth arcsch arcsec arcsec_over_pi arcsin\
	arcsin_over_pi arctan arctan2 arctan2_over_pi arctan_over_pi arsech\
	arsinh artanh cos cosh cos_pi_times cot coth cot_pi_times csc csch\
	csc_pi_times division exp exp_minus_1 hypotenuse integer_power\
	inversion lb lb_1_plus lg lg_1_plus ln ln_1_plus multiplication power\
	precision root sec sech sec_pi_times sign sin sinh sin_pi_times\
	square_root subtraction tan tanh tan_pi_times

MAN7 = man/libtakum128

SRC =\
	src/10_raised\
	src/2_raised\
	src/absolute\
	src/addition\
	src/arccos\
	src/arccot\
	src/arccsc\
	src/arcosh\
	src/arcoth\
	src/arcsch\
	src/arcsec\
	src/arcsin\
	src/arctan\
	src/arctan2\
	src/arsech\
	src/arsinh\
	src/artanh\
	src/codec128\
	src/conversion128\
	src/cos\
	src/cosh\
	src/cot\
	src/coth\
	src/csc\
	src/csch\
	src/division\
	src/exp\
	src/hypotenuse\
	src/integer_power\
	src/inversion\
	src/lb\
	src/lg\
	src/ln\
	src/multiplication\
	src/power\
	src/precision\
	src/root\
	src/sec\
	src/sech\
	src/sign\
	src/sin\
	src/sinh\
	src/square_root\
	src/subtraction\
	src/tan\
	src/tanh\
	src/util128\

TEST =\
	test/absolute\
	test/addition\
	test/constants\
	test/conversion\
	test/division\
	test/hypotenuse\
	test/integer_power\
	test/inversion\
	test/multiplication\
	test/precision\
	test/root\
	test/sign\
	test/square_root\
	test/subtraction\
	test/transcendental\

all: $(ANAME) $(SONAME) $(MAN7:=.7)

man/libtakum128.7: man/libtakum128.sh Makefile config.mk

src/10_raised.o: src/10_raised.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/2_raised.o: src/2_raised.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/absolute.o: src/absolute.c Makefile config.mk ../takum128.h
src/addition.o: src/addition.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arccos.o: src/arccos.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arccot.o: src/arccot.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arccsc.o: src/arccsc.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arcosh.o: src/arcosh.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arcoth.o: src/arcoth.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arcsch.o: src/arcsch.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arcsec.o: src/arcsec.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arcsin.o: src/arcsin.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arctan.o: src/arctan.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arctan2.o: src/arctan2.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arsech.o: src/arsech.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/arsinh.o: src/arsinh.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/artanh.o: src/artanh.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/codec128.o: src/codec128.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/conversion128.o: src/conversion128.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/cos.o: src/cos.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/cosh.o: src/cosh.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/cot.o: src/cot.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/coth.o: src/coth.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/csc.o: src/csc.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/csch.o: src/csch.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/division.o: src/division.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/exp.o: src/exp.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/hypotenuse.o: src/hypotenuse.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/integer_power.o: src/integer_power.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/inversion.o: src/inversion.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/lb.o: src/lb.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/lg.o: src/lg.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/ln.o: src/ln.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/multiplication.o: src/multiplication.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/power.o: src/power.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/precision.o: src/precision.c Makefile config.mk ../takum128.h src/util128.h
src/root.o: src/root.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/sec.o: src/sec.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/sech.o: src/sech.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/sign.o: src/sign.c Makefile config.mk ../takum128.h
src/sin.o: src/sin.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/sinh.o: src/sinh.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/square_root.o: src/square_root.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/subtraction.o: src/subtraction.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/tan.o: src/tan.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/tanh.o: src/tanh.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
src/util128.o: src/util128.c Makefile config.mk src/util128.h

test/util128.o: test/util128.c Makefile config.mk ../takum128.h test/util128.h src/codec128.h src/util128.h
test/absolute.o: test/absolute.c Makefile config.mk ../takum128.h test/util128.h
test/addition.o: test/addition.c Makefile config.mk ../takum128.h test/util128.h
test/constants.o: test/constants.c Makefile config.mk ../takum128.h test/util128.h
test/conversion.o: test/conversion.c Makefile config.mk ../takum128.h test/util128.h
test/division.o: test/division.c Makefile config.mk ../takum128.h test/util128.h
test/hypotenuse.o: test/hypotenuse.c Makefile config.mk ../takum128.h test/util128.h
test/integer_power.o: test/integer_power.c Makefile config.mk ../takum128.h test/util128.h
test/inversion.o: test/inversion.c Makefile config.mk ../takum128.h test/util128.h
test/multiplication.o: test/multiplication.c Makefile config.mk ../takum128.h test/util128.h
test/precision.o: test/precision.c Makefile config.mk ../takum128.h test/util128.h
test/root.o: test/root.c Makefile config.mk ../takum128.h test/util128.h
test/sign.o: test/sign.c Makefile config.mk ../takum128.h test/util128.h
test/square_root.o: test/square_root.c Makefile config.mk ../takum128.h test/util128.h
test/subtraction.o: test/subtraction.c Makefile config.mk ../takum128.h test/util128.h
test/transcendental.o: test/transcendental.c Makefile config.mk ../takum128.h test/util128.h

test/absolute$(BINSUFFIX): test/absolute.o test/util128.o $(ANAME)
test/addition$(BINSUFFIX): test/addition.o test/util128.o $(ANAME)
test/constants$(BINSUFFIX): test/constants.o test/util128.o $(ANAME)
test/conversion$(BINSUFFIX): test/conversion.o test/util128.o $(ANAME)
test/division$(BINSUFFIX): test/division.o test/util128.o $(ANAME)
test/hypotenuse$(BINSUFFIX): test/hypotenuse.o test/util128.o $(ANAME)
test/integer_power$(BINSUFFIX): test/integer_power.o test/util128.o $(ANAME)
test/inversion$(BINSUFFIX): test/inversion.o test/util128.o $(ANAME)
test/multiplication$(BINSUFFIX): test/multiplication.o test/util128.o $(ANAME)
test/precision$(BINSUFFIX): test/precision.o test/util128.o $(ANAME)
test/root$(BINSUFFIX): test/root.o test/util128.o $(ANAME)
test/sign$(BINSUFFIX): test/sign.o test/util128.o $(ANAME)
test/square_root$(BINSUFFIX): test/square_root.o test/util128.o $(ANAME)
test/subtraction$(BINSUFFIX): test/subtraction.o test/util128.o $(ANAME)
test/transcendental$(BINSUFFIX): test/transcendental.o test/util128.o $(ANAME)

test/absolute.success: test/absolute$(BINSUFFIX)
test/addition.success: test/addition$(BINSUFFIX)
test/constants.success: test/constants$(BINSUFFIX)
test/conversion.success: test/conversion$(BINSUFFIX)
test/division.success: test/division$(BINSUFFIX)
test/hypotenuse.success: test/hypotenuse$(BINSUFFIX)
test/integer_power.success: test/integer_power$(BINSUFFIX)
test/inversion.success: test/inversion$(BINSUFFIX)
test/multiplication.success: test/multiplication$(BINSUFFIX)
test/precision.success: test/precision$(BINSUFFIX)
test/root.success: test/root$(BINSUFFIX)
test/sign.success: test/sign$(BINSUFFIX)
test/square_root.success: test/square_root$(BINSUFFIX)
test/subtraction.success: test/subtraction$(BINSUFFIX)
test/transcendental.success: test/transcendental$(BINSUFFIX)

$(SRC:=.o):
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $(SHFLAGS) $(@:.o=.c)

$(TEST:=.o) test/util128.o:
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $(@:.o=.c)

$(TEST:=$(BINSUFFIX)):
	$(CC) -o $@ $(LDFLAGS) $(@:$(BINSUFFIX)=.o) test/util128.o $(ANAME) $(LDLIBS)

$(TEST:=.success):
	./$(@:.success=$(BINSUFFIX)) && touch $@

$(ANAME): $(SRC:=.o)
	$(AR) -rc $@ $?
	$(RANLIB) $@

$(SONAME): $(SRC:=.o)
	$(CC) -o $@ $(SOFLAGS) $(LDFLAGS) $(SRC:=.o) $(LDLIBS)

$(MAN7:=.7):
	env -i SH="$(SH)" MAN_DATE="$(MAN_DATE)" MAN3_BASE_NAMES="$(MAN3_BASE_NAMES)" $(SH) $(@:.7=.sh) > $@

check: test

test: $(TEST:=.success)

# Regenerates the named-constant #defines in ../takum128.h; prints to
# stdout, does not edit the header in place -- copy the relevant
# block(s) over by hand (see tools/gen_constants.c).
tools/gen_constants.o: tools/gen_constants.c Makefile config.mk ../takum128.h src/codec128.h src/util128.h
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) $(@:.o=.c)

tools/gen_constants$(BINSUFFIX): tools/gen_constants.o $(ANAME)
	$(CC) -o $@ $(LDFLAGS) $(@:$(BINSUFFIX)=.o) $(ANAME) $(LDLIBS)

constants: tools/gen_constants$(BINSUFFIX)
	./tools/gen_constants$(BINSUFFIX)

install: all
	mkdir -p "$(DESTDIR)$(LIBPREFIX)"
	mkdir -p "$(DESTDIR)$(LICPREFIX)/libtakum128"
	mkdir -p "$(DESTDIR)$(INCPREFIX)"
	mkdir -p "$(DESTDIR)$(MANPREFIX)/man7"
	cp -f ../LICENSE "$(DESTDIR)$(LICPREFIX)/libtakum128"
	cp -f $(ANAME) "$(DESTDIR)$(LIBPREFIX)"
	cp -f $(SONAME) "$(DESTDIR)$(LIBPREFIX)"
	if [ "$(SOSYMLINK)" = "true" ]; then i=0; while [ "$$i" -le $(VERSION_MINOR) ]; do ln -sf "$(SONAME)" "$(DESTDIR)$(LIBPREFIX)/libtakum128.so.$(VERSION_MAJOR).$$i"; i=$$((i+1)); done; fi
	if [ "$(SOSYMLINK)" = "true" ]; then ln -sf "$(SONAME)" "$(DESTDIR)$(LIBPREFIX)/libtakum128.so.$(VERSION_MAJOR)"; fi
	if [ "$(SOSYMLINK)" = "true" ]; then ln -sf "$(SONAME)" "$(DESTDIR)$(LIBPREFIX)/libtakum128.so"; fi
	cp -f ../takum128.h "$(DESTDIR)$(INCPREFIX)"
	cp -f $(MAN7:=.7) "$(DESTDIR)$(MANPREFIX)/man7"
	if ! [ -z "$(LDCONFIG)" ]; then $(SHELL) -c "$(LDCONFIG)"; fi
	if ! [ -z "$(PCPREFIX)" ]; then mkdir -p "$(DESTDIR)$(PCPREFIX)"; printf "Name: libtakum128\nDescription: Optional 128-bit (MPFR-backed) extension for libtakum\nURL: https://takum.org/\nVersion: $(VERSION)\nRequires: libtakum\nCflags: -I$(INCPREFIX)\nLibs: -L$(LIBPREFIX) -ltakum128\nLibs.private: -lmpfr -lgmp -lm\n" > "$(DESTDIR)$(PCPREFIX)/libtakum128.pc"; fi

uninstall:
	rm -f "$(DESTDIR)$(LICPREFIX)/libtakum128/LICENSE"
	rmdir "$(DESTDIR)$(LICPREFIX)/libtakum128"
	rm -f "$(DESTDIR)$(LIBPREFIX)/$(ANAME)"
	rm -f "$(DESTDIR)$(LIBPREFIX)/$(SONAME)"
	if [ "$(SOSYMLINK)" = "true" ]; then i=0; while [ "$$i" -le $(VERSION_MINOR) ]; do rm -f "$(DESTDIR)$(LIBPREFIX)/libtakum128.so.$(VERSION_MAJOR).$$i"; i=$$((i+1)); done; fi
	if [ "$(SOSYMLINK)" = "true" ]; then rm -f "$(DESTDIR)$(LIBPREFIX)/libtakum128.so.$(VERSION_MAJOR)"; fi
	if [ "$(SOSYMLINK)" = "true" ]; then rm -f "$(DESTDIR)$(LIBPREFIX)/libtakum128.so"; fi
	rm -f "$(DESTDIR)$(INCPREFIX)/takum128.h"
	for m in $(MAN7:=.7); do rm -f "$(DESTDIR)$(MANPREFIX)/man7/`basename $$m`"; done
	if ! [ -z "$(LDCONFIG)" ]; then $(SHELL) -c "$(LDCONFIG)"; fi
	if ! [ -z "$(PCPREFIX)" ]; then rm -f "$(DESTDIR)$(PCPREFIX)/libtakum128.pc"; fi

clean:
	rm -f $(SRC:=.o) $(TEST:=.o) test/util128.o $(TEST:=$(BINSUFFIX)) $(TEST:=.success) $(ANAME) $(SONAME) tools/gen_constants.o tools/gen_constants$(BINSUFFIX) $(MAN7:=.7)

.PHONY: all check clean constants install test uninstall
