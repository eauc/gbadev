# DEBUG_PREFIX = @echo ++

DEVKITPRO = /opt/devkitpro
DEVKITARM = $(DEVKITPRO)/devkitARM

EMU_PATH  = /opt/vba
EMU_CMD   = $(EMU_PATH)/VisualBoyAdvance
EMU_OPT   = 

TAGSFILE = TAGS

PATH      := $(DEVKITARM)/bin:$(PATH)

PREFIX    = arm-eabi-

CC        = $(PREFIX)gcc
AS        = $(PREFIX)as
LD        = $(PREFIX)gcc
AR        = $(PREFIX)ar rcs
OBJCOPY   = $(PREFIX)objcopy
GBAFIX    = $(DEBUG_PREFIX) gbafix
EMU       = $(DEBUG_PREFIX) $(EMU_CMD)
TAGSCMD   = etags

ARCH      = -mthumb -mthumb-interwork

CFLAGS    = -Wall -Wextra -O2\
	    -mcpu=arm7tdmi -mtune=arm7tdmi\
	    -fno-strict-aliasing\
	    $(ARCH) \
            -I$(INCDIR) \
	    -I$(dir $<) \
	    -MMD -MP -MT $@
# CFLAGS    = -Wall -Wextra -O2\
# 	    -fno-strict-aliasing\
# 	    $(ARCH) \
#             -I$(INCDIR) \
# 	    -I$(dir $<) \
# 	    -MMD -MP -MT $@
ASFLAGS   = $(ARCH)
LDFLAGS   = $(ARCH) -specs=gba.specs
# LDFLAGS   = $(ARCH)
TAGSFLAGS = --declarations
