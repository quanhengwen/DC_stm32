#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 				  
////////////////////////////////////////////////////////////////////////////////// 
extern TIM_HandleTypeDef TIM1_Handler;              //��ʱ��1��� 
extern TIM_Encoder_InitTypeDef TIM1_Encoder_Config; //1�������ӿ�

extern TIM_HandleTypeDef TIM2_Handler;              //��ʱ��2��� 
extern TIM_Encoder_InitTypeDef TIM2_Encoder_Config; //2�������ӿ�

extern TIM_HandleTypeDef TIM3_Handler;              //��ʱ��3��� 
extern TIM_Encoder_InitTypeDef TIM3_Encoder_Config; //3�������ӿ�

extern TIM_HandleTypeDef TIM4_Handler;              //��ʱ��4��� 
extern TIM_Encoder_InitTypeDef TIM4_Encoder_Config; //4�������ӿ�

extern TIM_HandleTypeDef TIM5_Handler;              //��ʱ��5��� 
extern TIM_Encoder_InitTypeDef TIM5_Encoder_Config; //5�������ӿ�


extern TIM_HandleTypeDef TIM8_Handler;         //��ʱ��8���
extern TIM_OC_InitTypeDef TIM8_CH1Handler;     //��ʱ��8ͨ��1���
extern TIM_OC_InitTypeDef TIM8_CH2Handler;     //��ʱ��8ͨ��2���
extern TIM_OC_InitTypeDef TIM8_CH3Handler;     //��ʱ��8ͨ��3���
extern TIM_OC_InitTypeDef TIM8_CH4Handler;     //��ʱ��8ͨ��4���

extern TIM_HandleTypeDef TIM9_Handler;      //��ʱ��9PWM��� 
extern TIM_OC_InitTypeDef TIM9_CH1Handler;  //��ʱ��9ͨ��1���

extern TIM_HandleTypeDef TIM10_Handler;         //��ʱ��10��� 
extern TIM_OC_InitTypeDef TIM10_CH1Handler;     //��ʱ��10ͨ��1���

void TIM1_Encoder_Init(u16 arr,u16 psc);
void TIM2_Encoder_Init(u32 arr,u16 psc);
void TIM3_Encoder_Init(u16 arr,u16 psc);
void TIM4_Encoder_Init(u16 arr,u16 psc);
void TIM5_Encoder_Init(u32 arr,u16 psc);

void TIM8_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM8Compare1(u16 compare);
void TIM_SetTIM8Compare2(u16 compare);
void TIM_SetTIM8Compare3(u16 compare);
void TIM_SetTIM8Compare4(u16 compare);

void TIM9_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM9Compare1(u16 compare);

void TIM10_PWM_Init(u16 arr,u16 psc);
void SendPulse(u8 distance);
volatile static u16 PU = 0;
volatile static u16 RePU = 0;
#endif

