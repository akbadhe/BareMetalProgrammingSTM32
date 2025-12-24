/* 1. Define the entry point for the debugger */
ENTRY(Reset_Handler)

/* 2. Physical Memory Definition (stm32f103c6t6A) */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 32K
    RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 10K
}

/* 3. Calculate top of RAM for the stack. Stack will grow downwards*/
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* 4. Section Placement */
SECTIONS
{
    /* Code and Vector Table stay in Flash */
    .text :
    {
        KEEP(*(.isr_vector))  /* Don't delete the vector table! */
        *(.text*)             /* All compiled code */
        *(.rodata*)           /* Read-only constants */
        _etext = .;           /* Mark the end of Flash data */
    } > FLASH

    /* Variables with initial values (e.g., int x = 5;) */
    /* Stored in Flash (AT > _etext) but live in RAM */
    .data : AT(_etext)
    {
        _sdata = .;           /* RAM start address */
        *(.data*)
        _edata = .;           /* RAM end address */
    } > RAM

    /* Variables initialized to zero (e.g., int y;) */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        _ebss = .;
    } > RAM
}