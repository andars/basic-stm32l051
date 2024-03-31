MEMORY {
    flash : ORIGIN = 0x8000000, LENGTH = 32K
    ram : ORIGIN = 0x20000000, LENGTH = 8K
}
SECTIONS {
    .text : {
        *(.vector_table)
        *(.text*)
    } > flash
    .bss : {
        bss_vma = .;
        *(.bss)
        *(COMMON)
        bss_vma_end = .;
    } > ram
}
stack_start = ORIGIN(ram) + LENGTH(ram);
