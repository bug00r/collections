MAKE?=mingw32-make
AR?=ar
ARFLAGS?=rcs
PATHSEP?=/
CC=gcc
BUILDROOT?=build

ifeq ($(CLANG),1)
	export CC=clang
endif

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

ifeq ($(DEBUG),1)
	export debug=-Ddebug=1 -ggdb
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-Ddebug=2 -ggdb
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-Ddebug=3 -ggdb
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg=-Doutput=1
endif

all: createdir
	$(MAKE) -f Makefile_array
	$(MAKE) -f Makefile_farray

.PHONY: clean createdir

createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)
