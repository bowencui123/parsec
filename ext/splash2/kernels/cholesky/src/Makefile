CC      = gcc
CFLAGS  = -O3 -Wall -Wextra -std=gnu89
TARGET  = cholesky

MACROS = ../../../null_macros/c.m4.null

SRCS = amal.C assign.C bfac.C bksolve.C block2.C fo.C mf.C numLL.C        parts.C seg.C solve.C tree.C util.C malloc.C
OBJS = $(SRCS:.C=.o)

.RECIPEPREFIX := >

.SUFFIXES:

all: $(TARGET)

%.c: %.C matrix.h
>m4 $(MACROS) $< > $@

%.o: %.c
>$(CC) $(CFLAGS) -c -o $@ $<

matrix.h: matrix.H
>m4 $(MACROS) $< > $@

$(TARGET): $(OBJS)
>$(CC) $(CFLAGS) -o $@ $(OBJS) -lm

clean:
>rm -f $(TARGET) $(OBJS) $(SRCS:.C=.c) matrix.h

.PHONY: all clean
