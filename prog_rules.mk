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
