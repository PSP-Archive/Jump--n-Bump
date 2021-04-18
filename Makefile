TARGET = jnbpsp
OBJS = gfx.o interrpt.o sound.o input.o fireworks.o main.o menu.o filter.o
 
BUILD_PRX = 1
 
CFLAGS = -O2 -G0 -Wall -w -g -Wextra -DUSE_SDL 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -fno-builtin-printf
ASFLAGS = $(CFLAGS)
 
LIBDIR =
LIBS = -L/usr/local/pspsdk/lib
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Jump n Bump
PSP_EBOOT_ICON = ../Resource/ICON0.png
 
PSPSDK=$(shell psp-config --pspsdk-path)
PSPBIN = $(PSPSDK)/../bin
CFLAGS += -I/usr/local/pspdev/psp/include/SDL
LIBS += $(shell $(PSPBIN)/freetype-config --libs)
LIBS += -lSDL_mixer
LIBS += -L/usr/local/pspdev/psp/lib -lSDL -lm -lpspvfpu -L/usr/local/pspdev/psp/sdk/lib -lpspdebug -lpspgu -lpspctrl -lpspge -lpspdisplay -lpsphprm -lpspsdk -lpsprtc -lpspaudio -lc -lpspuser -lpsputility -lpspkernel -lpspnet_inet -lpsppower
LIBS += -lSDL_ttf -lfreetype
LIBS += -lpng -ljpeg -lz -lm -lpsppower -lmad -lpspaudio -lpspaudiolib
include $(PSPSDK)/lib/build.mak
