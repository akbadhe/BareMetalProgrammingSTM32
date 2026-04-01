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
    uint8_t AHB_Prescaler;
    uint8_t APB1_Prescaler;
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
#define BIT_SHIFT_HPRE          4
#define BIT_SHIFT_PPRE1         8

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

//AHB Prescaler values
#define SYSCLK_by_2         0x8
#define SYSCLK_by_4         0x9
#define SYSCLK_by_8         0xA
#define SYSCLK_by_16        0xB
#define SYSCLK_by_64        0xC
#define SYSCLK_by_128       0xD
#define SYSCLK_by_256       0xE
#define SYSCLK_by_512       0xF

//APB1 Low speed Prescaler values
#define HCLK_by_2         0x4
#define HCLK_by_4         0x5
#define HCLK_by_8         0x6
#define HCLK_by_16        0x7

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

//APB1 peripheral clock enable bits
#define TIM2_EN             0
#define TIM3_EN             1
#define TIM4_EN             2
#define TIM5_EN             3
#define TIM6_EN             4
#define TIM7_EN             5
#define WWDG_EN             11
#define SPI2_EN             14
#define SPI3_EN             15
#define USART2_EN           17
#define USART3_EN           18
#define UART4_EN            19
#define UART5_EN            20
#define I2C1_EN             21
#define I2C2_EN             22
#define USB_EN              23
#define CAN_EN              25
#define BKP_EN              27
#define PWR_EN              28
#define DAC_EN              29

//Hal Functions
void HAL_RCC_Init(RCC_Config_t *cfg );
void HAL_RCC_APB2_PeripheralClockEnable(uint16_t peripheral);
void HAL_RCC_APB1_PeripheralClockEnable(uint16_t peripheral);