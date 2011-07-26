LIB_TARGET = $(OBJDIR)/libgba.a
LIB_ASOBJECTS = $(LIB_ASOURCES:%.s=$(OBJDIR)/lib-%.o)
LIB_ASOBJECTS_ARM = $(filter %.arm.o,$(LIB_ASOBJECTS))
LIB_ASOBJECTS_THUMB = $(filter-out %.arm.o,$(LIB_ASOBJECTS))
LIB_COBJECTS = $(LIB_CSOURCES:%.c=$(OBJDIR)/lib-%.o)
LIB_COBJECTS_ARM = $(filter %arm.o,$(LIB_COBJECTS))
LIB_COBJECTS_THUMB = $(filter-out %.arm.o,$(LIB_COBJECTS))
LIB_OBJECTS = $(LIB_COBJECTS) $(LIB_ASOBJECTS)
LIB_TAGS = $(LIBDIR)/$(TAGSFILE)

$(LIB_TARGET) : $(LIB_OBJECTS)
	$(AR) $@ $^

$(LIB_ASOBJECTS_ARM) : $(OBJDIR)/lib-%.arm.o : $(LIBDIR)/%.arm.s
	$(AS) $(ASFLAGS) $(ARCH) $< -o $@

$(LIB_ASOBJECTS_THUMB) : $(OBJDIR)/lib-%.o : $(LIBDIR)/%.s
	$(AS) $(ASFLAGS) $(ARCH) $< -o $@

$(LIB_COBJECTS_ARM) : $(OBJDIR)/lib-%.arm.o : $(LIBDIR)/%.arm.c
	$(CC) $(CFLAGS) $(ARCH_ARM) -c $< -o $@

$(LIB_COBJECTS_THUMB) : $(OBJDIR)/lib-%.o : $(LIBDIR)/%.c
	$(CC) $(CFLAGS) $(ARCH_THUMB) -c $< -o $@

$(LIB_TAGS) ::
	$(TAGSCMD) $(TAGSFLAGS) -o $@ $(LIBDIR)/*.c $(LIBDIR)/*.h $(INCDIR)/*.h 2>/dev/null
