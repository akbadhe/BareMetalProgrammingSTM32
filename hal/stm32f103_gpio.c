#include "stm32f103_gpio.h"

void HAL_GPIO_Init(GPIO_Registers_t* gpiox, GPIO_Config_t* cfg){
    
    if(cfg->pinNumber < 8){                  //Use CRL for pin 0-7

        //Clear the configuration for pinNumber
        gpiox->CRL &= ~(0xF << (cfg->pinNumber * 4));

        //Set the mode and configuration
        gpiox->CRL |= ((cfg->mode | cfg->config) << (cfg->pinNumber * 4));
    }else{                                  //Use CRH for pin 8-15

        //Reset the pinNumber as per CRH
        cfg->pinNumber = cfg->pinNumber - 8;  

        //Clear the configuration for pinNumber
        gpiox->CRH &= ~(0xF << (cfg->pinNumber * 4));

        //Set the mode and configuration
        gpiox->CRH |= ((cfg->mode | cfg->config) << (cfg->pinNumber * 4));
    }
}

void HAL_GPIO_Write(GPIO_Registers_t* gpiox, uint8_t pin, uint8_t state){
    if(state){
        gpiox->ODR &= ~(1 << pin); 
    }else{
        gpiox->ODR |= (1 << pin);
    }
}