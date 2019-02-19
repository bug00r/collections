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
	export debug=-Ddebug=1
	export isdebug=1
endif

ifeq ($(ANALYSIS),1)
	export analysis=-Danalysis=1
	export isanalysis=1
endif

ifeq ($(DEBUG),2)
	export debug=-Ddebug=2
	export isdebug=1
endif

ifeq ($(DEBUG),3)
	export debug=-Ddebug=3
	export isdebug=1
endif

ifeq ($(OUTPUT),1)
	export outimg=-Doutput=1
endif

CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra -ggdb
#-ggdb -O1 
#-pg for profiling 

INCLUDEDIR=-I./../linked_list -I./../../data -I.

SRC=tree.c

LIBNAME=libtree.a
OBJS=tree.o

TESTSRC=test_tree.c
TESTBIN=test_tree.exe
TESTLIB=-ltree -llinked_list -ldata
TESTLIBDIR=-L$(BUILDPATH) -L./../linked_list/$(BUILDDIR) -L./../../data/$(BUILDDIR)


all: createdir $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(TESTBIN) test

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS): tree.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS) $(INCLUDEDIR) $(debug)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB) $(debug)

.PHONY: clean createdir test

test:
	./$(BUILDPATH)$(TESTBIN)

createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)
	