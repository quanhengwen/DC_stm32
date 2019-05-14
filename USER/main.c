#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "exti.h"
/************************************************
 ALIENTEK ������STM32F7������ 
************************************************/

int main(void)
{
		u16 val1 = 0;   //0.68V
		u16 val2 = 0;   //1.33V
		u16 val3 = 0;   //1.99V
		u16 val4 = 0;   //2.64V
		u16 val5 = 0;     //3.30V
		u16 count1 = 0;
		u16 count2 = 0;
		u16 count3 = 0;
		u16 count4 = 0;
		u16 count5 = 0;
    Cache_Enable();                 //��L1-Cache
    HAL_Init();				        //��ʼ��HAL��
    Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
    delay_init(216);                //��ʱ��ʼ��
		uart2_init(115200);		        //����2��ʼ��
    LED_Init();                     //��ʼ��LED	
		EXTI_Init();                    //�ⲿ�жϳ�ʼ��
    TIM8_PWM_Init(100-1,108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
		TIM9_PWM_Init(100-1,108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
		
		// �ؽڱ���������
		TIM1_Encoder_Init(0xFFFF-1,1-1);  //��ʼ��������1 ��ʱ����
		TIM2_Encoder_Init(0xFFFF-1,1-1);	//��ʼ��������2 ��ʱ����
		TIM3_Encoder_Init(0xFFFF-1,1-1);	//��ʼ��������3 ˳ʱ����
		TIM4_Encoder_Init(0xFFFF-1,1-1);	//��ʼ��������4 ˳ʱ����
		TIM5_Encoder_Init(0xFFFF-1,1-1);	//��ʼ��������5 ˳ʱ����
	  
		TIM_SetTIM8Compare1(val1);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM8Compare2(val2);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM8Compare3(val3);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM8Compare4(val4);	//�޸ıȽ�ֵ���޸�ռ�ձ�
		TIM_SetTIM9Compare1(val5);	//�޸ıȽ�ֵ���޸�ռ�ձ�

		
    while(1)
    {
				delay_ms(1000);	 	
				count1=__HAL_TIM_GET_COUNTER(&TIM1_Handler);
				count2=__HAL_TIM_GET_COUNTER(&TIM2_Handler);
				count3=__HAL_TIM_GET_COUNTER(&TIM3_Handler);
				count4=__HAL_TIM_GET_COUNTER(&TIM4_Handler);
				count5=__HAL_TIM_GET_COUNTER(&TIM5_Handler);
				printf("%d   %d   %d   %d    %d\n",count1,count2,count3,count4,count5);	

				
    } 
}
