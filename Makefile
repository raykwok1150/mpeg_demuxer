# use pkg-config for getting CFLAGS and LDLIBS
FFMPEG_LIBS = 	libavformat							\
				libavcodec							\
				libavutil							\

CFLAGS += -Wall -g
CFLAGS := $(shell pkg-config --cflags $(FFMPEG_LIBS)) $(CFLAGS)
LDLIBS := $(shell pkg-config --libs $(FFMPEG_LIBS)) $(LDLIBS)

DEMUXER = 	mpeg_demuxer 							\
			remuxing								\

OBJ = $(addsuffix .o, $(DEMUXER))
#remuxing : LDLIBS += lm

.phony: all clean

all: $(OBJ) $(DEMUXER)

clean:
	$(RM) $(DEMUXER) $(OBJ)
