#include <stdint.h>
#include "stm32f103_gpio.h"

/* Register Addresses for STM32F103C6 */
/* Reset and Clock Control (RCC) */
#define RCC_BASE     0x40021000
#define RCC_APB2ENR  (*(volatile uint32_t *)(RCC_BASE + 0x18/*offset*/))

/*Bit definitions*/
#define RCC_IOPCEN  (1 << 4)    // IO Port C clock enable

/*Clock Registers definition*/
#define RCC_CFGR (*(volatile uint32_t *)(RCC_BASE + 0x04/*offset*/))
#define RCC_CR   (*(volatile uint32_t *)(RCC_BASE + 0x00/*offset*/))

//PLL selection
#define PLLMUL   (0x07 << 18)    //PLL input*9
#define SW       (1<<1)          //Select PLL as SYSCLK
#define PLLON    (1<<24)

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

    /*Configure the clock source selection*/
    RCC_CFGR |= (PLLMUL | SW );

    /*Enable PLL*/
    RCC_CR |= PLLON;

    /* Enable the clock for GPIOC peripheral */
    RCC_APB2ENR |= RCC_IOPCEN;

    //Select the mode and configurations using GPIO HAL
    GPIO_Config_t myConfig;
    myConfig.pinNumber = 13;
    myConfig.mode      = GPIO_MODE_OUTPUT_10MHz;
    myConfig.config    = GPIO_CNF_OUT_PUSH_PULL;

    //Initialize the GPIOC port with above config and mode
    HAL_GPIO_Init(GPIOC, &myConfig);

    while (1) {

        //Turn LED ON
        HAL_GPIO_Write(GPIOC, 13, 1);
        delay(1000000);

        //Turn LED OFF
        HAL_GPIO_Write(GPIOC, 13, 0);
        delay(200000);
    }

    return 0;
}
