#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"
#include "cstring"
#include "stdio.h"

//PIN DECLARATIONS

//speed control pins
#define EN_L_PIN                GPIO_PIN_0  
#define EN_R_PIN                GPIO_PIN_1  

//polarity (direction that each wheel moves) control pins
#define POL_L_PIN               GPIO_PIN_2  
#define POL_R_PIN               GPIO_PIN_3

//channel definitions.
#define CH1_PIN                 GPIO_PIN_4  //speed control
#define CH2_PIN                 GPIO_PIN_5  //steering control
#define CH3_PIN                 GPIO_PIN_6  //enter advanced steering state 
#define CH4_PIN                 GPIO_PIN_7  //enter test state if held down 

//PORT DECLARATIONS
#define EN_GPIO_PORT            GPIOB       //PWM output pins
#define POL_GPIO_PORT           GPIOC       //Digital output pins
#define CH_GPIO_PORT            GPIOA       //PWM input pins

//CLOCK DEFINITION
#define EN_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define POL_CLK_ENABLE()        __HAL_RCC_GPIOC_CLK_ENABLE()
#define CH_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()

void GPIO_INIT(void);

#endif