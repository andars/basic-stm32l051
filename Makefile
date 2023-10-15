CC=arm-none-eabi-gcc

CFLAGS += -std=c99
CFLAGS += -Og
CFLAGS += -g
CFLAGS += -mcpu=cortex-m0plus
CFLAGS += -Wall -Wextra

LDFLAGS += -nostdlib

.PHONY: all
all: main.elf

OBJECTS=main.o

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

%.elf: main.o
	$(CC) -Tlink.ld $(LDFLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) main.elf

.PRECIOUS: $(OBJECTS) main.elf
