CC ?= gcc
CFLAGS ?= -fPIC -Wall
DEBUG_MODE ?= -g
LD_FLAGS = -lavcodec -lavformat -lavutil $(DEBUG_MODE)

all: mpeg_demuxer remuxing

.PHONY: all

mpeg_demuxer: mpeg_demuxer.o
	$(CC) -o $@ $< $(LD_FLAGS)

remuxing: remuxing.o
	$(CC) -o $@ $< $(LD_FLAGS)

%.o: %.c
	$(CC) -c -o $@ $<

clean:
	rm -fr *.o *.ivf mpeg_demuxer remuxing
