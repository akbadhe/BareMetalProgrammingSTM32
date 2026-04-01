#include "common.h"
#include <stdbool.h>

//Timer registers structure
typedef struct{
    volatile uint32_t CR1;     //Control register 1
    volatile uint32_t CR2;     //Control register 2
    volatile uint32_t SMCR;    //Slave mode control register
    volatile uint32_t DIER;    //DMA/Interrupt enable register
    volatile uint32_t SR;      //Status Register
    volatile uint32_t EGR;     //Event generation register
    volatile uint32_t CCMR1;   //Capture/Compare mode register 1
    volatile uint32_t CCMR2;   //Capture/Compare mode register 2
    volatile uint32_t CCER;    //Capture/Compare enable register
    volatile uint32_t CNT;     //Counter
    volatile uint32_t PSC;     //Prescaler
    volatile uint32_t ARR;     //Auto reload register
    volatile uint32_t CCR1;    //Capture/Compare register 1
    volatile uint32_t CCR2;    //Capture/Compare register 2
    volatile uint32_t CCR3;    //Capture/Compare register 3
    volatile uint32_t CCR4;    //Capture/Compare register 4
    volatile uint32_t DCR;     //DMA control register
    volatile uint32_t DMAR;    //DMA address for full transfer
}Timer_Registers_t;

//Timers base addresses from memory map
#define TIMER2_BASE      0x40000000
#define TIMER3_BASE      0x40000400
#define TIMER4_BASE      0x40000800
#define TIMER5_BASE      0x40000C00

//Pointer definitions
#define TIMER2           ((Timer_Registers_t *)TIMER2_BASE)
#define TIMER3           ((Timer_Registers_t *)TIMER3_BASE)
#define TIMER4           ((Timer_Registers_t *)TIMER4_BASE)
#define TIMER5           ((Timer_Registers_t *)TIMER5_BASE)

//Timer Configuration structure
typedef struct{
    uint8_t  arpEnable;
    uint8_t  direction;
    uint8_t  updateDisable;
    uint16_t prescaler;
}Timer_Config_t;

//Auto reload preload enable macro
#define ARP_ENABLE       0x1
#define ARP_DISABLE      0x0

//Direction
#define DOWN_COUNTER      0x1
#define UP_COUNTER        0x0

//Update Disable
#define UEV_DISABLED      0x1
#define UEV_ENABLED       0x0

//Bit shift values for CR1
#define BIT_SHIFT_ARPE    7
#define BIT_SHIFT_DIR     4
#define BIT_SHIFT_UDIS    1
#define BIT_SHIFT_CEN     0

//Bit Shift values for SR
#define BIT_SHIFT_UIF     0

//HAL Functions
void HAL_TIMER_Init(Timer_Registers_t *timx, Timer_Config_t* cfg);
void HAL_TIMER_SetARR(Timer_Registers_t *timx, uint16_t arrVal);
void HAL_TIMER_Enable(Timer_Registers_t *timx);
void HAL_TIMER_Disable(Timer_Registers_t *timx);
bool HAL_TIMER_CheckUpdateInterruptFlag(Timer_Registers_t *timx);