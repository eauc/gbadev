TESTS = $(addprefix test-,$(TEST))
TESTS_RUN = $(addprefix run-,$(TESTS))

.PHONY : $(TESTS_RUN)
$(TESTS_RUN) : run-% : $(OBJDIR)/%.gba
	$(EMU) $<

.PHONY : $(TESTS)
$(TESTS) : % : $(OBJDIR)/%.gba

.SECONDEXPANSION:
$(OBJDIR)/test-%.elf : $(OBJDIR)/test-$$*-$$(subst .c,.o,$$(test_$$*_CSOURCES)) $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

.SECONDEXPANSION:
$(OBJDIR)/test-%.o : $(TESTDIR)/$$(subst -,/,$$*.c)
	$(CC) $(CFLAGS) -c $< -o $@
