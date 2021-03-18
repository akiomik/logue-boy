.PHONY: test cleantest

PROJECTDIR = .
BUILDDIR   = $(PROJECTDIR)/build
LIBSDIR    = $(PROJECTDIR)/../../../../libs
SRCDIR     = $(PROJECTDIR)/../../src
TESTDIR    = $(PROJECTDIR)/../../test

CXXC_TEST = g++

CXXOPT_TEST = -std=gnu++11 -fno-rtti -fno-exceptions -fno-non-call-exceptions

DINCDIR_TEST = $(LIBSDIR)/logue-sdk-stub/platform/minilogue-xd/inc \
               $(LIBSDIR)/googletest/googletest/include
INCDIR_TEST := $(patsubst %,-I%,$(DINCDIR_TEST))

DLIBS_TEST = -L$(LIBSDIR)/googletest/build/lib -lgtest -lgtest_main -lpthread
LIBS_TEST := $(DLIBS_TEST)

CXXFLAGS_TEST = $(CXXOPT_TEST)

$(BUILDDIR)/test.out: $(TESTDIR)/noise_test.cpp
	@echo Compiling $(<F)
	@$(CXXC_TEST) $(CXXFLAGS_TEST) -I$(SRCDIR) $(INCDIR_TEST) $< $(LIBS_TEST) -o $@

test: $(BUILDDIR)/test.out
	@echo Testing $(<F)
	@$<

cleantest:
	@echo Cleaning
	@rm -rf $(BUILDDIR)/test.out
