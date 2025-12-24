#include <stdint.h>

/* Register Addresses for STM32F103C6 */
/* Reset and Clock Control (RCC) */
#define RCC_BASE     0x40021000
#define RCC_APB2ENR  (*(volatile uint32_t *)(RCC_BASE + 0x18/*offset*/))

/* GPIO PORTC */
#define GPIOC_BASE 0x40011000
#define GPIOC_CRH  (*(volatile uint32_t *)(GPIOC_BASE + 0x04/*offset*/))
#define GPIOC_ODR  (*(volatile uint32_t *)(GPIOC_BASE + 0x0C/*offset*/))

/*Bit definitions*/
#define RCC_IOPCEN  (1 << 4)    // IO Port C clock enable
#define PC13        (1 << 13)

/**
 * Simple delay loop
 * 'volatile' prevents the compiler from optimizing the loop away
 */
void delay(volatile uint32_t count) {
    while (count--) {
        __asm("nop"); 
    }
}

int main(void){

    /* 1. Enable the clock for GPIOC peripheral */
    RCC_APB2ENR |= RCC_IOPCEN;

    /* 2. Configure PC13 as Output Push-Pull (2MHz)
     * Each pin in CRH takes 4 bits. PC13 is bits [23:20]
     * Clear bits 20-23 and set them to 0x2 (Output mode, max speed 2MHz)
     */
    GPIOC_CRH &= ~(0xF << 20); // Clear configuration for Pin 13
    GPIOC_CRH |=  (0x2 << 20); // Set Pin 13 as General purpose output push-pull

    while (1) {
        /* 3. Toggle the LED */
        GPIOC_ODR ^= PC13;

        /* 4. Wait */
        delay(600000);
    }

    return 0;
}