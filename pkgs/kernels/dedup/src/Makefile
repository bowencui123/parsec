CC ?= gcc
CFLAGS ?= -O2 -Wall -fno-strict-aliasing -D_XOPEN_SOURCE=600 -DENABLE_GZIP_COMPRESSION
LDFLAGS ?=
LIBS ?= -lm -lz

SRC = hashtable.c util.c dedup.c rabin.c encoder.c decoder.c mbuffer.c sha.c
OBJ = $(SRC:.c=.o)
TARGET = dedup

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
