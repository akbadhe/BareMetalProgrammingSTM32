#include "common.h"

//RCC registers structure
typedef struct{
    volatile uint32_t CR;           // Control register
    volatile uint32_t CFGR;         // Configuration register
    volatile uint32_t CIR;          // Interrupt register
    volatile uint32_t APB2RSTR;     // APB2 peripheral reset register
    volatile uint32_t APB1RSTR;     // APB1 peripheral reset register
    volatile uint32_t AHBENR;       // AHB peripheral clock enable register
    volatile uint32_t APB2ENR;      // APB2 peripheral clock enable register
    volatile uint32_t APB1ENR;      // APB1 peripheral clock enable register
    volatile uint32_t BDCR;         // Backup domain control register
    volatile uint32_t CSR;          // Control/Status register
}RCC_Registers_t;

//RCC Configuration structure 
typedef struct{
    uint8_t clkSrc;
    uint8_t PLL_Multiplier;
}RCC_Config_t;

//RCC Base address as per memory map
#define RCC_BASE     0x40021000

//Pointer definition to RCC Base
#define RCC          ((RCC_Registers_t *)RCC_BASE)

//Bit shift definitions for PLL
#define BIT_SHIFT_PLLON         24
#define BIT_SHIFT_PLLSRC        16
#define BIT_SHIFT_SW            0
#define BIT_SHIFT_PLLMUL        18

//Clock source switch(SW)
#define HSI_SYSCLK              0x0
#define HSE_SYSCLK              0x1
#define PLL_SYSCLK              0x2

//PLL multiplier values
#define PLLx2               0x0
#define PLLx3               0x1
#define PLLx4               0x2
#define PLLx5               0x3
#define PLLx6               0x4
#define PLLx7               0x5
#define PLLx8               0x6
#define PLLx9               0x7
#define PLLx10              0x8
#define PLLx11              0x9
#define PLLx12              0xA
#define PLLx13              0xB
#define PLLx14              0xC
#define PLLx15              0xD
#define PLLx16              0xE


//APB2 peripheral clock enable bits
#define AFIO_EN             0
#define IOPA_EN             2
#define IOPB_EN             3
#define IOPC_EN             4
#define IOPD_EN             5
#define IOPE_EN             6
#define IOPF_EN             7
#define IOPG_EN             8
#define ADC1_EN             9
#define ADC2_EN             10
#define TIM1_EN             11
#define SPI1_EN             12
#define TIM8_EN             13
#define USART1_EN           14
#define ADC3_EN             15

//Hal Functions
void HAL_RCC_Init(RCC_Config_t *cfg );
void HAL_RCC_APB2_PeripheralClockEnable(uint16_t peripheral);