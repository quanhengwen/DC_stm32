#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
#include "timer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F7������
//�ⲿ�ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/11/27
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
u8 v_up=0,v_key0 =0;
//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��
    __HAL_RCC_GPIOC_CLK_ENABLE();               //����GPIOCʱ��
    __HAL_RCC_GPIOH_CLK_ENABLE();               //����GPIOHʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLDOWN;			//����
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_13;               //PC13
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;				//����
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3;     //PH2,3  �½��ش���������
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
    //�ж���0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���2
    HAL_NVIC_SetPriority(EXTI2_IRQn,2,1);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(EXTI2_IRQn);             //ʹ���ж���2
    
    //�ж���3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //ʹ���ж���2
    
    //�ж���13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn,2,3);   //��ռ���ȼ�Ϊ3�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);         //ʹ���ж���13  
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);   //�����жϴ������ú���
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);   //�����жϴ������ú���
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);   //�����жϴ������ú���
}

void EXTI15_10_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);  //�����жϴ������ú���
}

//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static u8 led0sta=1,led1sta=1;
		u16 v12 = 0, v345 = 0;
    delay_ms(50);      //����
    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
            if(WK_UP==1)	//����LED0,LED1�������
            {
//                led1sta=!led1sta;
//                led0sta=!led1sta;
//                LED1(led1sta);
//                LED0(led0sta);
								if (v_up<10)
									v_up++;
								else v_up = 0;
								v12 += v_up * 10;
								TIM_SetTIM8Compare1(v12);	//�޸ıȽ�ֵ���޸�ռ�ձ�
								TIM_SetTIM8Compare2(v12);	//�޸ıȽ�ֵ���޸�ռ�ձ�
								printf("val of joint12: %d",v12);
							
            }
            break;
        case GPIO_PIN_2:
            if(KEY1==0) 	//����LED1��ת	(DR)
            {
                led1sta=!led1sta;
                LED1(led1sta);	
            };
            break;
        case GPIO_PIN_3:
            if(KEY0==0)  	//ͬʱ����LED0,LED1��ת 
            {
//                led1sta=!led1sta;
//                led0sta=!led0sta;
//                LED1(led1sta);
//                LED0(led0sta); 
								if (v_key0<10)
										v_key0++;
								else v_key0 = 0;
								v345 += v_key0 * 10;
								TIM_SetTIM8Compare3(v345);	//�޸ıȽ�ֵ���޸�ռ�ձ�
								TIM_SetTIM8Compare4(v345);	//�޸ıȽ�ֵ���޸�ռ�ձ�
								TIM_SetTIM9Compare1(v345);	//�޸ıȽ�ֵ���޸�ռ�ձ�
								printf("val of joint345: %d",v345);
            }
            break;

        case GPIO_PIN_13:
            if(KEY2==0)  	//����LED0��ת  (PU)
            {
                led0sta=!led0sta;
                LED0(led0sta);
								SendPulse(20);
            }
            break;
    }
}