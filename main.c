#include <stdint.h>

#define RCC_BASE 0x40021000
#define RCC_CR 0x00
#define RCC_CFGR 0x0C
#define RCC_IOPENR 0x2C

#define GPIO_BASE_A 0x50000000
#define GPIO_MODER 0x00
#define GPIO_BSRR 0x18

void gpio_init() {
    // Reset & clock control, GPIO clock enable register
    volatile uint32_t *rcc_iopenr = (volatile uint32_t *)(RCC_BASE + RCC_IOPENR);

    // Enable GPIO port A clock
    *rcc_iopenr = 0x1;
}

int main() {
    gpio_init();

    // Set HSI16ON to enable the 16 MHz internal clock
    volatile uint32_t *rcc_cr = (volatile uint32_t *)(RCC_BASE + RCC_CR);
    *rcc_cr = *rcc_cr | 0x1;

    // Update CFGR.SW to switch SYSCLK from 2 MHz MSI to 16 MHz HSI
    volatile uint32_t *rcc_cfgr = (volatile uint32_t *)(RCC_BASE + RCC_CFGR);
    *rcc_cfgr = 0x01;

    // GPIO port A mode register
    volatile uint32_t *gpio_a_moder = (volatile uint32_t *)(GPIO_BASE_A + GPIO_MODER);

    // configure PA12 as an output
    uint32_t gpio_a_mode = 0xE9FFFCFF;
    *gpio_a_moder = gpio_a_mode;

    // GPIO port A bit set/reset register
    volatile uint32_t *gpio_a_bsrr = (volatile uint32_t *)(GPIO_BASE_A + GPIO_BSRR);

    const int iterations_on = 100000;
    const int iterations_off = 100000;

    // Blink LED on port A 12 on and off
    while (1) {
        // Set GPIO PA12
        *gpio_a_bsrr = (1 << 12);
        for (int i = 0; i < iterations_on; i++) {
            __asm__ volatile ("" ::: "memory");
        }

        // Reset GPIO PA12
        *gpio_a_bsrr = (1 << 28);
        for (int i = 0; i < iterations_off; i++) {
            __asm__ volatile ("" ::: "memory");
        }
    }
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
