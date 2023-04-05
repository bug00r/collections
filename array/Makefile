PATHSEP?=/
BUILDROOT?=build

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

all: createdir
	$(MAKE) -f Makefile_array 
	$(MAKE) -f Makefile_farray

.PHONY: clean createdir test

createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)

test: createdir
	$(MAKE) -f Makefile_array test
	$(MAKE) -f Makefile_farray test

install:
	$(MAKE) -f Makefile_array install
	$(MAKE) -f Makefile_farray install

