#include "common.h"

//GPIO registers structure
typedef struct{
   volatile uint32_t CRL;   // Configuration Register Low (Pins 0-7)
   volatile uint32_t CRH;   // Configuration Register High (Pins 8-15)
   volatile uint32_t IDR;   // Input Data Register
   volatile uint32_t ODR;   // Output Data Register
   volatile uint32_t BSRR;  // Bit Set/Reset Register
   volatile uint32_t BRR;   // Bit Reset Register
   volatile uint32_t LCKR;  // Configuration Lock Register
}GPIO_Registers_t;

//GPIO ports base addresses from memory map
#define GPIOA_BASE    0x40010800
#define GPIOB_BASE    0x40010C00
#define GPIOC_BASE    0x40011000
#define GPIOD_BASE    0x40011400
#define GPIOE_BASE    0x40011800
#define GPIOF_BASE    0x40011C00
#define GPIOG_BASE    0x40012000

//Pointer definitions
#define GPIOA         ((GPIO_Registers_t *)GPIOA_BASE)
#define GPIOB         ((GPIO_Registers_t *)GPIOB_BASE)
#define GPIOC         ((GPIO_Registers_t *)GPIOC_BASE)
#define GPIOD         ((GPIO_Registers_t *)GPIOD_BASE)
#define GPIOE         ((GPIO_Registers_t *)GPIOE_BASE)
#define GPIOF         ((GPIO_Registers_t *)GPIOF_BASE)
#define GPIOG         ((GPIO_Registers_t *)GPIOG_BASE)

//GPIO Configuration structure (TODO:use bit fields to optimize memory)
typedef struct{
    uint8_t pinNumber;
    uint8_t mode;
    uint8_t config;
}GPIO_Config_t;

//Mode selection macros for GPIO
#define GPIO_MODE_INPUT              0x0
#define GPIO_MODE_OUTPUT_2MHz        0x2
#define GPIO_MODE_OUTPUT_10MHz       0x1
#define GPIO_MODE_OUTPUT_50MHz       0x3

//Configuration selection macros for GPIO
#define GPIO_CNF_IN_ANALOG           0x0
#define GPIO_CNF_IN_FLOATING         0x4
#define GPIO_CNF_IN_PULL_UP_DOWN     0x8

#define GPIO_CNF_OUT_PUSH_PULL       0x0
#define GPIO_CNF_OUT_OPEN_DRAIN      0x4
#define GPIO_CNF_OUT_ALT_PUSH_PULL   0x8
#define GPIO_CNF_OUT_ALT_OPEN_DRAIN  0xc

//HAL Functions
void HAL_GPIO_Init(GPIO_Registers_t* gpiox, GPIO_Config_t* cfg);
void HAL_GPIO_Write(GPIO_Registers_t* gpiox, uint8_t pin, uint8_t state);