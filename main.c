#include "stm32f103_gpio.h"
#include "stm32f103_rcc.h"

#define ON    1
#define OFF   0

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

    //Select configuration for clock source(HSI, HSE, PLL) and select PLL multiplier
    RCC_Config_t rccConfig;
    rccConfig.clkSrc         = PLL_SYSCLK;
    rccConfig.PLL_Multiplier = PLLx10;

    //Initialize PLL as system clock with multiplier
    HAL_RCC_Init(&rccConfig);

    //Enable the clock for GPIOC peripheral
    HAL_RCC_APB2_PeripheralClockEnable(IOPC_EN);

    //Select the mode and configurations using GPIO HAL
    GPIO_Config_t gpioConfig;
    gpioConfig.pinNumber = 13;
    gpioConfig.mode      = GPIO_MODE_OUTPUT_10MHz;
    gpioConfig.config    = GPIO_CNF_OUT_PUSH_PULL;

    //Initialize the GPIOC port with above config and mode
    HAL_GPIO_Init(GPIOC, &gpioConfig);

    while (1) {

        //Turn LED ON
        HAL_GPIO_Write(GPIOC, 13, ON);
        delay(200000);

        //Turn LED OFF
        HAL_GPIO_Write(GPIOC, 13, OFF);
        delay(200000);
    }

    return 0;
}
