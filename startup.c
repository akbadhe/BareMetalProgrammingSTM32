#include <stdint.h>

/* Symbols from Linker Script */
extern uint32_t _etext, _sdata, _edata, _sbss, _ebss, _estack;

/* Function Prototypes */
void main(void);
void Reset_Handler(void);

/* 1. The Vector Table 
   Placed at the very start of Flash via the attribute */
__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)&_estack,     /* 0x00: Initial SP */
    (uint32_t *)Reset_Handler /* 0x04: Reset Vector */
};

/* 2. The Reset Handler 
   The first code the CPU actually runs */
void Reset_Handler(void) {
    // A. Copy .data from Flash (LMA) to RAM (VMA)
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    volatile uint8_t *pDst = (uint8_t *)&_sdata; // RAM
    volatile uint8_t *pSrc = (uint8_t *)&_etext; // FLASH
    
    for (uint32_t i = 0; i < size; i++) {
        pDst[i] = pSrc[i];
    }

    // B. Initialize .bss to Zero
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pDst = (uint8_t *)&_sbss;
    for (uint32_t i = 0; i < size; i++) {
        pDst[i] = 0;
    }

    // C. (Optional) Call System Clock Init
    // SystemInit();

    // D. Jump to Main
    main();

    // E. Infinite loop if main returns
    while(1);
}