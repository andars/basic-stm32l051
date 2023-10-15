#include <stdint.h>

#define RCC_BASE 0x40021000
#define RCC_IOPENR 0x2C

void gpio_init() {
    // Reset & clock control, GPIO clock enable register
    volatile uint32_t *rcc_iopenr = (volatile uint32_t *)(RCC_BASE + RCC_IOPENR);

    // Enable GPIO port A clock
    *rcc_iopenr = 0x1;
}

int main() {
    gpio_init();
}

void reset_handler(void) {
    main();
}

extern char stack_start[];

__attribute__ ((section(".vector_table")))
void *vector_table[64] = {
    // Reset value of the stack pointer
    stack_start,
    // Reset handler
    reset_handler,
    // Rest of the exception handlers
    // ...
};
