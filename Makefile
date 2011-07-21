PROG = essai
TEST =  default \
	bckgnd  \
	bgdaff  \
	bios    \
	dma     \
	effects \
	input   \
	interrupt \
	objaff  \
	object  \
	plot    \
	timer

INCDIR  = inc
LIBDIR  = lib
OBJDIR  = obj
PROGDIR = prog
TESTDIR = test

PROGDIRS = $(addprefix $(PROGDIR)/,$(PROG))
TESTDIRS = $(addprefix $(TESTDIR)/,$(TEST))

include $(LIBDIR)/Makefile
-include $(PROGDIRS:=/Makefile)
-include $(TESTDIRS:=/Makefile)

include toolchain.mk
include lib_rules.mk
include test_rules.mk
include prog_rules.mk

-include $(OBJDIR)/*.d

.PHONY : TAGS
TAGS : $(PROG_TAGS) $(TEST_TAGS) $(LIB_TAGS)

.PHONY : clean_all
clean_all : clean
	rm -fv $(OBJDIR)/*

.PHONY : clean
clean :
	rm -fv $(OBJDIR)/*.o
