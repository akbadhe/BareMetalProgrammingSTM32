#include "stm32f103_timer.h"

void HAL_TIMER_Init(Timer_Registers_t *timx, Timer_Config_t* cfg){
    timx->CR1 |= ((cfg->arpEnable << BIT_SHIFT_ARPE)    | 
                  (cfg->direction << BIT_SHIFT_DIR)     | 
                  (cfg->updateDisable << BIT_SHIFT_UDIS)
                 );
    
    //Set the prescaler for counter clock
    //counter clock freq = input freq / (PSC+1)
    timx->PSC |= cfg->prescaler;
}

void HAL_TIMER_SetARR(Timer_Registers_t *timx, uint16_t arrVal){
    //Set the auto reload value
    timx->ARR |= arrVal;
}

void HAL_TIMER_Enable(Timer_Registers_t *timx){
    //Start the counter
    timx->CR1 |= (1 << BIT_SHIFT_CEN);
}

void HAL_TIMER_Disable(Timer_Registers_t *timx){
    //Stop the counter
    timx->CR1 &= ~(1 << BIT_SHIFT_CEN);
}

bool HAL_TIMER_CheckUpdateInterruptFlag(Timer_Registers_t *timx){
    //Return true if UIF bit is set
    if(timx->SR & (1 << BIT_SHIFT_UIF)){
        timx->SR &= ~(1 <<BIT_SHIFT_UIF);        //Clear UIF bit for next event
        return true;
    }else{
        return false;
    }
}