LIB_TARGET = $(OBJDIR)/libgba.a
LIB_OBJECTS = $(LIB_CSOURCES:%.c=$(OBJDIR)/lib-%.o)
LIB_TAGS = $(LIBDIR)/$(TAGSFILE)

$(LIB_TARGET) : $(LIB_OBJECTS)
	$(AR) $@ $^

$(OBJDIR)/lib-%.arm.o : $(LIBDIR)/%.arm.c
	$(CC) $(CFLAGS) $(ARCH_ARM) -c $< -o $@

$(OBJDIR)/lib-%.o : $(LIBDIR)/%.c
	$(CC) $(CFLAGS) $(ARCH_THUMB) -c $< -o $@

$(LIB_TAGS) ::
	$(TAGSCMD) $(TAGSFLAGS) -o $@ $(LIBDIR)/*.c $(LIBDIR)/*.h $(INCDIR)/*.h 2>/dev/null
