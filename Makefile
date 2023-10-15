CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS += -std=c99
CFLAGS += -Og
CFLAGS += -g
CFLAGS += -mcpu=cortex-m0plus
CFLAGS += -Wall -Wextra

LDFLAGS += -nostdlib

.PHONY: all
all: main.bin

OBJECTS=main.o

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

%.elf: main.o
	$(CC) -Tlink.ld $(LDFLAGS) $< -o $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) main.elf main.bin

.PRECIOUS: $(OBJECTS) main.elf
