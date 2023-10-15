void reset_handler(void) {
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
