TARGET = jnbpsp
OBJS = gfx.o interrpt.o sound.o input.o fireworks.o main.o menu.o filter.o

CFLAGS = -O2 -G0 -Wall -w -g -Wextra -DUSE_SDL 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -fno-builtin-printf
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -L/usr/local/pspsdk/lib
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Jump 'n Bump
PSP_EBOOT_ICON = ../Resource/ICON0.png

PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
CFLAGS += $(shell $(PSPBIN)/sdl-config --cflags)
LIBS += $(shell $(PSPBIN)/freetype-config --libs)
LIBS += -lSDL_mixer
LIBS += $(shell $(PSPBIN)/sdl-config --libs)
LIBS += -lSDL_ttf -lfreetype
LIBS += -lpng -ljpeg -lz -lm -lpsppower -lmad -lpspaudio -lpspaudiolib
include $(PSPSDK)/lib/build.mak
