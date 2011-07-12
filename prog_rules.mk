PROG_RUN = $(addprefix run-,$(PROG))
PROG_TAGS = $(addsuffix /$(TAGSFILE),$(PROGDIRS))

.PHONY : $(PROG_RUN)
$(PROG_RUN) : run-% : $(OBJDIR)/%.gba
	$(EMU) $<

.PHONY : $(PROG)
$(PROG) : % : $(OBJDIR)/%.gba

$(OBJDIR)/%.gba : $(OBJDIR)/%.elf
	$(OBJCOPY) -v -O binary $< $@
	$(GBAFIX) $@

.SECONDEXPANSION:
$(OBJDIR)/%.elf : $(OBJDIR)/$$*-$$(subst .c,.o,$$($$*_CSOURCES)) $(LIB_OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

.SECONDEXPANSION:
$(OBJDIR)/%.o : $(PROGDIR)/$$(subst -,/,$$*.c)
	$(CC) $(CFLAGS) -c $< -o $@

$(PROG_TAGS) :: %/TAGS :
	$(TAGSCMD) $(TAGSFLAGS) -i $(CURDIR)/$(LIB_TAGS) -o $@ $*/*.c $*/*.h 2>/dev/null
