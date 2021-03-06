#include "Sm_TIM1.h"
#include "Sm_GPIOA.h"

Sm::CALLBACK TIM1_Callback;   

extern "C"
{

void TIM1_UP_IRQHandler(void)
{
#ifdef Sm_UCOS_Support 
    OSIntEnter();
#endif

    if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
    {
        if(TIM1_Callback.pfun)
            TIM1_Callback.pfun(TIM1_Callback.arg);
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }

#ifdef Sm_UCOS_Support 
    OSIntExit();
#endif
}

void TIM1_BRK_IRQHandler(void)      //tim1的暂停中断
{}
void TIM1_CC_IRQHandler(void)       //tim1的捕获比较中断
{}
void TIM1_TRG_COM_IRQHandler(void)  //tim1的触发
{}

}

void TIM1_PWM_DefPin_Init(Sm::PWM_Channel chl)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    if(chl == Sm::PWM_Channel_2) //关闭USART1的RCC时钟，否则PA9不能输出PWM
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, DISABLE);

    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = (uint16_t)(1 << (chl+8));
    gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
}

void TIM1_PWM_FullRemap_Init(Sm::PWM_Channel chl)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE); 
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);

    uint16_t GPIO_Pin_x;
    if(chl == Sm::PWM_Channel_1)
        GPIO_Pin_x = GPIO_Pin_9;
    else if(chl == Sm::PWM_Channel_2)
        GPIO_Pin_x = GPIO_Pin_11;
    else if(chl == Sm::PWM_Channel_3)
        GPIO_Pin_x = GPIO_Pin_13;
    else /* if(chl == Sm::PWM_Channel_4) */
        GPIO_Pin_x =GPIO_Pin_14;

    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = GPIO_Pin_x;
    gpio_init.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
}

void TIM1_Encoder_DefPin_Init(uint16_t TIM_EncoderMode_x)
{
    if(TIM_EncoderMode_x == TIM_EncoderMode_TI1)
        Sm_GPIOA::init_IO(GPIO_Pin_8, GPIO_Mode_IN_FLOATING);
    else if(TIM_EncoderMode_x == TIM_EncoderMode_TI2)
        Sm_GPIOA::init_IO(GPIO_Pin_9, GPIO_Mode_IN_FLOATING);
    else
        Sm_GPIOA::init_IO(GPIO_Pin_8|GPIO_Pin_9, GPIO_Mode_IN_FLOATING);
}

void TIM1_Encoder_FullRemapPin_Init(uint16_t TIM_EncoderMode_x)
{
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);

    if(TIM_EncoderMode_x == TIM_EncoderMode_TI1)
        Sm_GPIOA::init_IO(GPIO_Pin_9, GPIO_Mode_IN_FLOATING);
    else if(TIM_EncoderMode_x == TIM_EncoderMode_TI2)
        Sm_GPIOA::init_IO(GPIO_Pin_11, GPIO_Mode_IN_FLOATING);
    else
        Sm_GPIOA::init_IO(GPIO_Pin_9|GPIO_Pin_11, GPIO_Mode_IN_FLOATING);
}

void TIM1_ETR_DefPin_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = GPIO_Pin_12;
    gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_init);
}

void TIM1_ETR_FullRemap_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO, ENABLE); 
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE);

    GPIO_InitTypeDef gpio_init;
    gpio_init.GPIO_Pin = GPIO_Pin_7;
    gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &gpio_init);
}
