CC=gcc
CFLAGS=-Wall -pthread

SRC:=$(wildcard *.c)
TARGETS:= $(SRC:.c=)

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)
