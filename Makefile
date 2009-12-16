#
#   Copyright 2009, Harry Li <harry.li AT pagefreedom.org>
#   Copyright 2009, Yuan Ye <yuanyelele@gmail.com>
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

GCCPATH = /home/symbian/csl-gcc

SYSINCPATH = $(EPOCROOT)/epoc32/include
VARIANT = $(SYSINCPATH)/variant
OS_HRH = $(VARIANT)/symbian_os_v9.1.hrh
CERT = ~/cert_dev.cer
KEY = ~/cert_dev.key
LANG_MACRO = LANGUAGE_SC

include config.mk

check:
	@echo 'EPOCROOT is' $(EPOCROOT)
	@echo 'GCCPATH is ' $(GCCPATH)
	@echo 'PATH is ' $(PATH)
	@echo '==============================================================='

CXX = arm-none-symbianelf-g++ # GNU project C and C++ compiler
LD  = arm-none-symbianelf-ld  # The GNU linker

ARMV5URELPATH = $(EPOCROOT)/epoc32/release/armv5/urel
ARMV5LIBPATH = $(EPOCROOT)/epoc32/release/armv5/lib

CXXFLAGS += -fexceptions -march=armv5t -mapcs -pipe -nostdinc -c -msoft-float \
	-MD -include $(EPOCROOT)/epoc32/include/gcce/gcce.h \
	-D__SYMBIAN32__ -D__EPOC32__ -D__SERIES60_30__ -D__SERIES60_3X__ \
	-D__GCCE__ -D__MARM__ -D__MARM_ARMV5__ -D__EABI__ \
	-D__SUPPORT_CPP_EXCEPTIONS__ -D__EXE__ -DNDEBUG -D_UNICODE \
	-Wall -Wno-unknown-pragmas \
	-D__PRODUCT_INCLUDE__="$(OS_HRH)" -Isrc -I$(VARIANT) \
	-Iinc -I$(SYSINCPATH) \
	-I$(GCCPATH)/lib/gcc/arm-none-symbianelf/3.4.3/include \
	-Wno-ctor-dtor-privacy -x c++

LDFLAGS = \
	--entry _E32Startup -soname $(PROJECT){000a0000}[$(UID3)].$(TARGETTYPE) \
	--library-path $(GCCPATH)/arm-none-symbianelf/lib --library supc++ \
	--library-path $(GCCPATH)/lib/gcc/arm-none-symbianelf/3.4.3 --library gcc \
	--output dist/$(PROJECT).elf --undefined _E32Startup \
	--no-undefined --default-symver -nostdlib -shared \
	-Tdata 0x400000 -Ttext 0x8000 --target1-abs \
	$(ARMV5URELPATH)/eexe.lib $(ARMV5URELPATH)/usrt2_2.lib \
	$(ARMV5LIBPATH)/dfpaeabi.dso $(ARMV5LIBPATH)/dfprvct2_2.dso \
	$(ARMV5LIBPATH)/drtaeabi.dso $(ARMV5LIBPATH)/drtrvct2_2.dso \
	$(ARMV5LIBPATH)/scppnwdl.dso

OBJS = $(patsubst %.cpp,src/%.o,$(SRCFILES))

clean: check
	rm -rfv dist/*
	rm -fv $(OBJS)
	rm -fv $(patsubst %.o,%.d,$(OBJS))
	rm -fv inc/$(PROJECT)help.hrh
	rm -fv inc/$(PROJECT).mbg
	rm -fv inc/*.rsg

$(OBJS): src/%.o : src/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

dist/$(PROJECT).elf: $(OBJS)
	$(LD) $^ $(LDFLAGS) \
		$(addprefix $(ARMV5URELPATH)/,$(STATICLIBRARY)) \
		$(patsubst %.lib,$(ARMV5LIBPATH)/%.dso,$(LIBRARY))

dist/$(PROJECT)_$(UID3).$(TARGETTYPE): dist/$(PROJECT).elf
	elf2e32 --elfinput $^ --output $@ --targettype $(TARGETTYPE) \
		--linkas $(PROJECT){000a0000}[$(UID3)].$(TARGETTYPE) \
		--uid1 0x1000007a --uid2 0x$(UID2) --uid3 0x$(UID3) \
		--sid 0x$(SECUREID) --vid 0x$(VENDORID) --stack $(EPOCSTACKSIZE) \
		--capability $(subst $(NULL) $(NULL),+,$(CAPABILITY)) \
		--libpath $(ARMV5LIBPATH) --fpu=softvfp

bin: check dist/$(PROJECT)_$(UID3).$(TARGETTYPE)

$(RSSTARGET): dist/%_$(UID3).rsc : rss/%.rss
	epocrc.pl -Iinc -I- -I$(SYSINCPATH) \
		-D$(LANG_MACRO) -u -v \
		$< -o$@ -hinc/$(basename $(notdir $<))_$(UID3).rsg

resource: check $(RSSTARGET)

build: check resource bin

pack: build sis/$(PROJECT).pkg $(CERT) $(KEY)
	makesis -v sis/$(PROJECT).pkg sis/$(PROJECT).sis
	signsis -v sis/$(PROJECT).sis sis/$(PROJECT).sisx $(CERT) $(KEY)

