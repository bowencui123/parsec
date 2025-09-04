CC      = gcc
CFLAGS  = -O3 -Wall -Wextra -std=gnu89
TARGET  = radix

MACROS = ../../../null_macros/c.m4.null

SRCS = radix.C
OBJS = $(SRCS:.C=.o)

.RECIPEPREFIX := >

.SUFFIXES:

all: $(TARGET)

%.c: %.C
>m4 $(MACROS) $< > $@

%.o: %.c
>$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
>$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

clean:
>rm -f $(TARGET) $(OBJS) $(SRCS:.C=.c)

.PHONY: all clean
