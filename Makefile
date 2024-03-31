CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

CFLAGS += -std=c99
CFLAGS += -Og
CFLAGS += -g
CFLAGS += -fno-common
CFLAGS += -mcpu=cortex-m0plus
CFLAGS += -Wall -Wextra
CFLAGS += -ffreestanding

LDFLAGS += -nostdlib
LDFLAGS += -Xlinker --print-memory-usage
LDFLAGS += -Xlinker --print-map

.PHONY: all
all: main.bin

OBJECTS=main.o

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

%.elf: main.o link.ld
	$(CC) -Tlink.ld $(LDFLAGS) $< -o $@

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) main.elf main.bin

.PHONY: flash
flash: main.bin
	st-flash --connect-under-reset write ./main.bin 0x8000000

.PRECIOUS: $(OBJECTS) main.elf
