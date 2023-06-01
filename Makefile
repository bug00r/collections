_CFLAGS:=$(CFLAGS)
CFLAGS:=$(_CFLAGS)
_LDFLAGS:=$(LDFLAGS)
LDFLAGS:=$(_LDFLAGS)

ARFLAGS?=rcs
PATHSEP?=/
BUILDROOT?=build

BUILDDIR?=$(BUILDROOT)$(PATHSEP)$(CC)
BUILDPATH?=$(BUILDDIR)$(PATHSEP)

ifndef PREFIX
	INSTALL_ROOT=$(BUILDPATH)
else
	INSTALL_ROOT=$(PREFIX)$(PATHSEP)
	ifeq ($(INSTALL_ROOT),/)
	INSTALL_ROOT=$(BUILDPATH)
	endif
endif

ifdef DEBUG
	CFLAGS+=-ggdb
	ifeq ($(DEBUG),)
	CFLAGS+=-Ddebug=1
	else 
	CFLAGS+=-Ddebug=$(DEBUG)
	endif
endif

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

COLLECTIONS_PROJ_ROOT:=$(shell pwd)
COLLECTIONS_PROJ_BUILD:=$(COLLECTIONS_PROJ_ROOT)$(PATHSEP)$(BUILDPATH)

COLLECTION_MODULES:=array linked_list dl_list tree

all: $(patsubst %, build_%, $(COLLECTION_MODULES)) 

build_array:
	$(MAKE) -C array
	$(MAKE) -C array install PREFIX=$(COLLECTIONS_PROJ_BUILD)

build_linked_list:
	$(MAKE) -C linked_list CFLAGS="$(CFLAGS) -I$(COLLECTIONS_PROJ_BUILD)include"
	$(MAKE) -C linked_list install PREFIX=$(COLLECTIONS_PROJ_BUILD)

build_dl_list:
	$(MAKE) -C dl_list CFLAGS="$(CFLAGS) -I$(COLLECTIONS_PROJ_BUILD)include"
	$(MAKE) -C dl_list install PREFIX=$(COLLECTIONS_PROJ_BUILD)

build_tree:
	$(MAKE) -C tree CFLAGS="$(CFLAGS) -I$(COLLECTIONS_PROJ_BUILD)include"
	$(MAKE) -C tree install PREFIX=$(COLLECTIONS_PROJ_BUILD)

.PHONY: clean createdir	test

test: createdir
	$(MAKE) -C array test CFLAGS="$(CFLAGS) -I$(COLLECTIONS_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(COLLECTIONS_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C linked_list test CFLAGS="$(CFLAGS) -I$(COLLECTIONS_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(COLLECTIONS_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C dl_list test CFLAGS="$(CFLAGS) -I$(COLLECTIONS_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(COLLECTIONS_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"
	$(MAKE) -C tree test CFLAGS="$(CFLAGS) -I$(COLLECTIONS_PROJ_BUILD)include" LDFLAGS="$(LDFLAGS) -L$(COLLECTIONS_PROJ_BUILD)lib$(BIT_SUFFIX)$(PATHSEP)"

createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)
	$(MAKE) -C array clean
	$(MAKE) -C linked_list clean
	$(MAKE) -C dl_list clean
	$(MAKE) -C tree clean

install:
	$(info install at: $(INSTALL_ROOT))
	mkdir -p $(INSTALL_ROOT)include
	mkdir -p $(INSTALL_ROOT)lib$(BIT_SUFFIX)
	cp $(BUILDPATH)include/*.h $(INSTALL_ROOT)include
	cp $(BUILDPATH)lib$(BIT_SUFFIX)/*.a $(INSTALL_ROOT)lib$(BIT_SUFFIX)


#all:
#	$(MAKE) -C array
#	$(MAKE) -C linked_list
#	$(MAKE) -C dl_list
#	#$(MAKE) -C tree

#.PHONY: clean install test
#clean:
#	$(MAKE) -C array clean
#	$(MAKE) -C linked_list clean
#	$(MAKE) -C dl_list clean
#	#$(MAKE) -C tree clean

#test:
#	$(MAKE) -C array test
#	$(MAKE) -C linked_list test
#	$(MAKE) -C dl_list test
#	#$(MAKE) -C tree test

#install:
#	$(MAKE) -C array install
#	$(MAKE) -C linked_list install
#	$(MAKE) -C dl_list install
#	#$(MAKE) -C tree clean
