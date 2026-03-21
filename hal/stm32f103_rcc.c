#include "stm32f103_rcc.h"

void HAL_RCC_Init(RCC_Config_t *cfg ){

    if(cfg->clkSrc == PLL_SYSCLK){
        uint8_t multiplier;
        switch(cfg->PLL_Multiplier){
            case 2:
                    multiplier = PLLx2;
                    break;
            case 3:
                    multiplier = PLLx3;
                    break;
            case 4:
                    multiplier = PLLx4;
                    break;
            case 5:
                    multiplier = PLLx5;
                    break;
            case 6:
                    multiplier = PLLx6;
                    break;
            case 7:
                    multiplier = PLLx7;
                    break;
            case 8:
                    multiplier = PLLx8;
                    break;
            case 9:
                    multiplier = PLLx9;
                    break;
            case 10:
                    multiplier = PLLx10;
                    break;
            case 11:
                    multiplier = PLLx11;
                    break;
            case 12:
                    multiplier = PLLx12;
                    break;
            case 13:
                    multiplier = PLLx13;
                    break;
            case 14:
                    multiplier = PLLx14;
                    break;
            case 15:
                    multiplier = PLLx15;
                    break;
            case 16:
                    multiplier = PLLx16;
                    break;
            default:
                    multiplier = PLLx2;
        }

        // 1. Configuration: Select PLL as system clock and select PLL multiplier
        RCC->CFGR |= ((PLL_SYSCLK << BIT_SHIFT_SW) | (multiplier << BIT_SHIFT_PLLMUL));

        // 2. Enable: enable PLL after configuration only
        RCC->CR   |= (1 << BIT_SHIFT_PLLON);

    }//need to add for HSI and HSE later
}


void HAL_RCC_APB2_PeripheralClockEnable(uint16_t peripheral){

    //Enable the peripheral
    RCC->APB2ENR |= (1 << peripheral);
}