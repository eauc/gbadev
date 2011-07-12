DEVKITPRO = /opt/devkitpro
DEVKITARM = $(DEVKITPRO)/devkitARM

EMU_PATH  = /opt/vba
EMU       = $(EMU_PATH)/VisualBoyAdvance
EMU_OPT   = 

PATH      := $(DEVKITARM)/bin:$(PATH)

PREFIX    = arm-eabi-

CC        = $(PREFIX)gcc
AS        = $(PREFIX)as
LD        = $(PREFIX)gcc
AR        = $(PREFIX)ar rcs
OBJCOPY   = $(PREFIX)objcopy
GBAFIX    = gbafix

ARCH      = -mthumb -mthumb-interwork

CFLAGS    = -Wall -Wextra -O2\
	    -mcpu=arm7tdmi -mtune=arm7tdmi\
	    -fno-strict-aliasing\
	    $(ARCH) \
            -I$(INCDIR)
ASFLAGS   = $(ARCH)
LDFLAGS   = $(ARCH) -specs=gba.specs
