TESTS = $(addprefix test-,$(TEST))
TESTS_RUN = $(addprefix run-,$(TESTS))
TEST_TAGS = $(addsuffix /$(TAGSFILE),$(TESTDIRS))

.PHONY : $(TESTS_RUN)
$(TESTS_RUN) : run-% : $(OBJDIR)/%.gba
	$(EMU) $<

.PHONY : $(TESTS)
$(TESTS) : % : $(OBJDIR)/%.gba

.SECONDEXPANSION:
$(OBJDIR)/test-%.elf : $$(addprefix $(OBJDIR)/test-$$*-,$$(subst .c,.o,$$(test_$$*_CSOURCES))) $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

.SECONDEXPANSION:
$(OBJDIR)/test-%.arm.o : $(TESTDIR)/$$(subst -,/,$$*.arm.c)
	$(CC) $(CFLAGS) $(ARCH_ARM) -c $< -o $@

.SECONDEXPANSION:
$(OBJDIR)/test-%.o : $(TESTDIR)/$$(subst -,/,$$*.c)
	$(CC) $(CFLAGS) $(ARCH_THUMB) -c $< -o $@

$(TEST_TAGS) :: %/TAGS :
	$(TAGSCMD) $(TAGSFLAGS) -i $(CURDIR)/$(LIB_TAGS) -o $@ $*/*.c $*/*.h 2>/dev/null
