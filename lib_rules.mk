LIB_TARGET = $(OBJDIR)/libgba.a
LIB_OBJECTS = $(LIB_CSOURCES:%.c=$(OBJDIR)/lib-%.o)
LIB_TAGS = $(LIBDIR)/$(TAGSFILE)

$(LIB_TARGET) : $(LIB_OBJECTS)
	$(AR) $@ $^

$(LIB_OBJECTS): $(OBJDIR)/lib-%.o : $(LIBDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_TAGS) ::
	$(TAGSCMD) $(TAGSFLAGS) -o $@ $(LIBDIR)/*.c $(LIBDIR)/*.h $(INCDIR)/*.h 2>/dev/null
