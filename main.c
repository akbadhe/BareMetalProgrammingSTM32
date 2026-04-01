#include "stm32f103_gpio.h"
#include "stm32f103_rcc.h"
#include "stm32f103_timer.h"

#define ON    1
#define OFF   0

//Simple delay loop for count seconds
void delay(volatile uint32_t count) {
    //Set the auto reload value upto which the counter will count
    HAL_TIMER_SetARR(TIMER2, 1953);

    //Enable/start the counter
    HAL_TIMER_Enable(TIMER2);

    //Loop for count times to generate delay of count seconds
    for(int i=0; i<count;i++){
        //Loop in while till counter overflow
        while(!HAL_TIMER_CheckUpdateInterruptFlag(TIMER2));
    }

    //Disable/Stop counter
    HAL_TIMER_Disable(TIMER2);
}

int main(void){

    //Select configuration for clock source
    RCC_Config_t rccConfig;
    rccConfig.clkSrc         = PLL_SYSCLK;      //Select clock source(HSI, HSE, PLL)
    rccConfig.PLL_Multiplier = PLLx2;           //Select PLL multiplier
    rccConfig.AHB_Prescaler  = SYSCLK_by_64;    //Select AHB prescaler
    rccConfig.APB1_Prescaler = HCLK_by_2;       //Select APB1 prescaler

    //Initialize PLL as system clock with multiplier
    HAL_RCC_Init(&rccConfig);

    //Enable the clock for GPIOC peripheral
    HAL_RCC_APB2_PeripheralClockEnable(IOPC_EN);

    //Enable the clock for TIM2 peripheral
    HAL_RCC_APB1_PeripheralClockEnable(TIM2_EN);

    //Select the mode and configurations using GPIO HAL
    GPIO_Config_t gpioConfig;
    gpioConfig.pinNumber = 13;
    gpioConfig.mode      = GPIO_MODE_OUTPUT_10MHz;
    gpioConfig.config    = GPIO_CNF_OUT_PUSH_PULL;

    //Initialize the GPIOC port with above config and mode
    HAL_GPIO_Init(GPIOC, &gpioConfig);

    //Configure timer
    Timer_Config_t timerConfig;
    timerConfig.arpEnable     = ARP_ENABLE;
    timerConfig.direction     = UP_COUNTER;
    timerConfig.updateDisable = UEV_ENABLED;
    timerConfig.prescaler     = 1;

    //Timer2 initialization
    HAL_TIMER_Init(TIMER2, &timerConfig);

    while (1) {
        //Turn LED ON
        HAL_GPIO_Write(GPIOC, 13, ON);
        delay(2);

        //Turn LED OFF
        HAL_GPIO_Write(GPIOC, 13, OFF);
        delay(2);
    }

    return 0;
}
