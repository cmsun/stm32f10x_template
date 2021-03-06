#ifndef SM_TIM4_H
#define SM_TIM4_H

#include "Sm_TIM.h"

//定时器4有外部时钟源功能，可以对外部脉冲进行计数
#define EXTRA_CLOCK_MODE2

extern Sm::CALLBACK TIM4_Callback;   
extern void TIM4_PWM_DefPin_Init(Sm::PWM_Channel);
extern void TIM4_PWM_Remap_Init(Sm::PWM_Channel);
extern void TIM4_Encoder_DefPin_Init(uint16_t);
extern void TIM4_Encoder_Remap_Init(uint16_t);
extern void TIM4_ETR_DefPin_Init(void);

typedef Sm_TIM<TIM4_BASE,
        RCC_APB1PeriphClockCmd,
        RCC_APB1Periph_TIM4,
        TIM4_PWM_DefPin_Init,
        TIM4_Encoder_DefPin_Init,
        TIM4_ETR_DefPin_Init,
        TIM4_IRQn,
        &TIM4_Callback> Sm_TIM4;

typedef Sm_TIM<TIM4_BASE,
        RCC_APB1PeriphClockCmd,
        RCC_APB1Periph_TIM4,
        TIM4_PWM_Remap_Init,
        TIM4_Encoder_Remap_Init,
        TIM4_ETR_DefPin_Init,
        TIM4_IRQn,
        &TIM4_Callback> Sm_TIM4_Remap;

#undef EXTRA_CLOCK_MODE2

#endif
