include ../../make_config

CFLAGS=-std=c11 -Wpedantic -pedantic-errors -Wall -Wextra
#-ggdb -O1 
#-pg for profiling 

INCLUDEDIR=-I.

SRC=dl_list.c

LIBNAME=libdl_list.a
OBJS=dl_list.o

TESTSRC=test_dl_list.c
TESTBIN=test_dl_list.exe
TESTLIB=-ldl_list
TESTLIBDIR=-L$(BUILDPATH)

all: createdir $(BUILDPATH)$(LIBNAME) 

$(BUILDPATH)$(LIBNAME): $(BUILDPATH)$(OBJS)
	$(AR) $(ARFLAGS) $(BUILDPATH)$(LIBNAME) $(BUILDPATH)$(OBJS)

$(BUILDPATH)$(OBJS): dl_list.h
	$(CC) $(CFLAGS) -c $(SRC) -o $(BUILDPATH)$(OBJS) $(INCLUDEDIR)  $(debug)
	
$(BUILDPATH)$(TESTBIN):
	$(CC) $(CFLAGS) $(TESTSRC) -o $(BUILDPATH)$(TESTBIN) $(INCLUDEDIR)  $(TESTLIBDIR) $(TESTLIB) $(debug)

.PHONY: clean createdir test

test: $(BUILDPATH)$(TESTBIN)
	./$(BUILDPATH)$(TESTBIN)

createdir:
	mkdir -p $(BUILDDIR)

clean:
	-rm -dr $(BUILDROOT)
	