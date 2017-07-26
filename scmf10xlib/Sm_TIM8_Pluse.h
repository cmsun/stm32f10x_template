#ifndef SM_TIM8_PLUSE_H
#define SM_TIM8_PLUSE_H

#include "Sm_TIM8.h"
#include "Sm_Pluse.h"
#include "Sm_GPIOC.h"

//方向信号
#define TIM8_PLUSE_DIRECTION_CLASS      Sm_GPIOC
#define TIM8_PLUSE_DIRECTION_PIN        GPIO_Pin_7

//原点信号
#define TIM8_PLUSE_HOME_CLASS           Sm_GPIOC
#define TIM8_PLUSE_HOME_PIN             GPIO_Pin_4
#define TIM8_PLUSE_HOME_PINSOURCE       GPIO_PinSource4

//正限位信号
#define TIM8_PLUSE_FORWARDLIMIT_CLASS   Sm_GPIOC
#define TIM8_PLUSE_FORWARDLIMIT_PIN     GPIO_Pin_5

//负限位信号
#define TIM8_PLUSE_REVERSELIMIT_CLASS   Sm_GPIOC
#define TIM8_PLUSE_REVERSELIMIT_PIN     GPIO_Pin_8

//TIM8 CCR1寄存器
#define TIM8_CR1_ADDR 0x40013400

extern Sm::Pluse_t                      TIM8_Pluse;

//脉冲输出：GPIO PC6
typedef Sm_Pluse<Sm_TIM8, Sm::PWM_Channel1, TIM8_CR1_ADDR,
        RCC_AHBPeriph_DMA2, DMA2_Channel1_BASE, DMA2_Channel1_IRQn,
        TIM8_PLUSE_DIRECTION_CLASS, TIM8_PLUSE_DIRECTION_PIN,
        TIM8_PLUSE_HOME_CLASS, TIM8_PLUSE_HOME_PINSOURCE,
        TIM8_PLUSE_FORWARDLIMIT_CLASS, TIM8_PLUSE_FORWARDLIMIT_PIN,
        TIM8_PLUSE_REVERSELIMIT_CLASS, TIM8_PLUSE_REVERSELIMIT_PIN,
        &TIM8_Pluse> Sm_TIM8_Pluse;

#endif
