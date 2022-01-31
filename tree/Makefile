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

BIT_SUFFIX=

ifeq ($(M32),1)
	CFLAGS+=-m32
	BIT_SUFFIX+=32
endif

CFLAGS+=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb -O1 
#-pg for profiling 

INCLUDEDIR=-I/c/dev/include/ -I.

NAME=tree

SRC=$(NAME).c

LIBNAME=lib$(NAME).a
LIB=$(BUILDPATH)$(LIBNAME)
OBJS=$(NAME).o

TESTSRC=test_$(NAME).c
TESTBIN=$(BUILDPATH)test_$(NAME).exe
TESTLIB=-l$(NAME) -llinked_list -ldata
TESTLIBDIR=-L$(BUILDPATH) -L/c/dev/lib/


all: createdir $(LIB) $(TESTBIN)

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(OBJS): $(NAME).h
	$(CC) $(CFLAGS) -c $(SRC) -o $@ $(INCLUDEDIR) $(debug)
	
$(TESTBIN): $(LIB)
	$(CC) $(CFLAGS) $(TESTSRC) -o $@ $(INCLUDEDIR) $(TESTLIBDIR) $(TESTLIB) $(debug)

.PHONY: clean createdir test

test:
	./$(TESTBIN)

createdir:
	-mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)
	