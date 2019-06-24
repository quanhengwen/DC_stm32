#include "timer.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//TIM1-5��CH1��CH2����ȡ�������Ƕ�
//TIM1����AF1��PA8��9
//TIM2����AF1��PA15��PB3
//TIM3����AF2��PB4��5
//TIM4����AF2��PB6\7
//TIM5����AF2��PH10��11

//TIM8��CH1��2��3��4/PC6\7\8\9��TIM9��CH1/PE5����PWM�����źţ�0-3.3V����Ӧռ�ձȣ�0-100%��

//
////////////////////////////////////////////////////////////////////////////////// 	 
TIM_HandleTypeDef TIM1_Handler;              //��ʱ��1��� 
TIM_Encoder_InitTypeDef TIM1_Encoder_Config; //1�������ӿ�

TIM_HandleTypeDef TIM2_Handler;              //��ʱ��2��� 
TIM_Encoder_InitTypeDef TIM2_Encoder_Config; //2�������ӿ�

TIM_HandleTypeDef TIM3_Handler;              //��ʱ��3��� 
TIM_Encoder_InitTypeDef TIM3_Encoder_Config; //3�������ӿ�

TIM_HandleTypeDef TIM4_Handler;              //��ʱ��4��� 
TIM_Encoder_InitTypeDef TIM4_Encoder_Config; //4�������ӿ�

TIM_HandleTypeDef TIM5_Handler;              //��ʱ��5��� 
TIM_Encoder_InitTypeDef TIM5_Encoder_Config; //5�������ӿ�



TIM_HandleTypeDef TIM8_Handler;         //��ʱ��8��� 
TIM_OC_InitTypeDef TIM8_CH1Handler;     //��ʱ��8ͨ��1���
TIM_OC_InitTypeDef TIM8_CH2Handler;     //��ʱ��8ͨ��2���
TIM_OC_InitTypeDef TIM8_CH3Handler;     //��ʱ��8ͨ��3���
TIM_OC_InitTypeDef TIM8_CH4Handler;     //��ʱ��8ͨ��4���

TIM_HandleTypeDef TIM9_Handler;         //��ʱ��9��� 
TIM_OC_InitTypeDef TIM9_CH1Handler;     //��ʱ��9ͨ��1���

TIM_HandleTypeDef TIM10_Handler;         //��ʱ��10��� 
TIM_OC_InitTypeDef TIM10_CH1Handler;     //��ʱ��10ͨ��1���


//TIM1 ������ģʽ��ʼ��
void TIM1_Encoder_Init(u16 arr,u16 psc) 
{	 
		TIM1_Handler.Instance=TIM1;                               //��ʱ��1
    TIM1_Handler.Init.Prescaler=psc;                          //��ʱ����Ƶ
    TIM1_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;         //���ϼ���ģʽ
    TIM1_Handler.Init.Period=arr;                             //�Զ���װ��ֵ
    TIM1_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
		TIM1_Encoder_Config.EncoderMode=TIM_ENCODERMODE_TI12;     //TI1��TI2������
		TIM1_Encoder_Config.IC1Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM1_Encoder_Config.IC1Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
    TIM1_Encoder_Config.IC1Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM1_Encoder_Config.IC1Filter=0;                          //���������˲��������˲�
		TIM1_Encoder_Config.IC2Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM1_Encoder_Config.IC2Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI2��
    TIM1_Encoder_Config.IC2Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM1_Encoder_Config.IC2Filter=0;                          //���������˲��������˲�
    HAL_TIM_Encoder_Init(&TIM1_Handler,&TIM1_Encoder_Config); //��ʼ��TIM1�������ӿ�	
		HAL_TIM_Encoder_Start(&TIM1_Handler,TIM_CHANNEL_ALL);     //��TIM1��ͨ��
}
//TIM2 ������ģʽ��ʼ��
void TIM2_Encoder_Init(u32 arr,u16 psc) 
{	 
		TIM2_Handler.Instance=TIM2;                               //��ʱ��2
    TIM2_Handler.Init.Prescaler=psc;                          //��ʱ����Ƶ
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;         //���ϼ���ģʽ
    TIM2_Handler.Init.Period=arr;                             //�Զ���װ��ֵ
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
		TIM2_Encoder_Config.EncoderMode=TIM_ENCODERMODE_TI12;     //TI1��TI2������
		TIM2_Encoder_Config.IC1Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM2_Encoder_Config.IC1Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
    TIM2_Encoder_Config.IC1Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM2_Encoder_Config.IC1Filter=0;                          //���������˲��������˲�
		TIM2_Encoder_Config.IC2Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM2_Encoder_Config.IC2Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI2��
    TIM2_Encoder_Config.IC2Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM2_Encoder_Config.IC2Filter=0;                          //���������˲��������˲�
    HAL_TIM_Encoder_Init(&TIM2_Handler,&TIM2_Encoder_Config); //��ʼ��TIM2�������ӿ�	
		HAL_TIM_Encoder_Start(&TIM2_Handler,TIM_CHANNEL_ALL);     //��TIM2��ͨ��
}
//TIM3 ������ģʽ��ʼ��
void TIM3_Encoder_Init(u16 arr,u16 psc) 
{	 
		TIM3_Handler.Instance=TIM3;                               //��ʱ��3
    TIM3_Handler.Init.Prescaler=psc;                          //��ʱ����Ƶ
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;         //���ϼ���ģʽ
    TIM3_Handler.Init.Period=arr;                             //�Զ���װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
		TIM3_Encoder_Config.EncoderMode=TIM_ENCODERMODE_TI12;     //TI1��TI2������
		TIM3_Encoder_Config.IC1Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM3_Encoder_Config.IC1Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
    TIM3_Encoder_Config.IC1Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM3_Encoder_Config.IC1Filter=0;                          //���������˲��������˲�
		TIM3_Encoder_Config.IC2Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM3_Encoder_Config.IC2Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI2��
    TIM3_Encoder_Config.IC2Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM3_Encoder_Config.IC2Filter=0;                          //���������˲��������˲�
    HAL_TIM_Encoder_Init(&TIM3_Handler,&TIM3_Encoder_Config); //��ʼ��TIM2�������ӿ�	
		HAL_TIM_Encoder_Start(&TIM3_Handler,TIM_CHANNEL_ALL);     //��TIM2��ͨ��
}
//TIM4 ������ģʽ��ʼ��
void TIM4_Encoder_Init(u16 arr,u16 psc) 
{	 
		TIM4_Handler.Instance=TIM4;                               //��ʱ��4
    TIM4_Handler.Init.Prescaler=psc;                          //��ʱ����Ƶ
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;         //���ϼ���ģʽ
    TIM4_Handler.Init.Period=arr;                             //�Զ���װ��ֵ
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
		TIM4_Encoder_Config.EncoderMode=TIM_ENCODERMODE_TI12;     //TI1��TI2������
		TIM4_Encoder_Config.IC1Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM4_Encoder_Config.IC1Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
    TIM4_Encoder_Config.IC1Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM4_Encoder_Config.IC1Filter=0;                          //���������˲��������˲�
		TIM4_Encoder_Config.IC2Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM4_Encoder_Config.IC2Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI2��
    TIM4_Encoder_Config.IC2Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM4_Encoder_Config.IC2Filter=0;                          //���������˲��������˲�
    HAL_TIM_Encoder_Init(&TIM4_Handler,&TIM4_Encoder_Config); //��ʼ��TIM2�������ӿ�	
		HAL_TIM_Encoder_Start(&TIM4_Handler,TIM_CHANNEL_ALL);     //��TIM2��ͨ��
}

//TIM5 ������ģʽ��ʼ��
void TIM5_Encoder_Init(u32 arr,u16 psc) 
{	 
		TIM5_Handler.Instance=TIM5;                               //��ʱ��5
    TIM5_Handler.Init.Prescaler=psc;                          //��ʱ����Ƶ
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;         //���ϼ���ģʽ
    TIM5_Handler.Init.Period=arr;                             //�Զ���װ��ֵ
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
		TIM5_Encoder_Config.EncoderMode=TIM_ENCODERMODE_TI12;     //TI1��TI2������
		TIM5_Encoder_Config.IC1Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM5_Encoder_Config.IC1Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI1��
    TIM5_Encoder_Config.IC1Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM5_Encoder_Config.IC1Filter=0;                          //���������˲��������˲�
		TIM5_Encoder_Config.IC2Polarity=TIM_ICPOLARITY_FALLING;    //˫���ز���
    TIM5_Encoder_Config.IC2Selection=TIM_ICSELECTION_DIRECTTI;//ӳ�䵽TI2��
    TIM5_Encoder_Config.IC2Prescaler=TIM_ICPSC_DIV1;          //���������Ƶ������Ƶ
    TIM5_Encoder_Config.IC2Filter=0;                          //���������˲��������˲� 
    HAL_TIM_Encoder_Init(&TIM5_Handler,&TIM5_Encoder_Config); //��ʼ��TIM5�������ӿ�	
		HAL_TIM_Encoder_Start(&TIM5_Handler,TIM_CHANNEL_ALL);     //��TIM5��ͨ��
}


//������ģʽ��ʼ���ص�����
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
	
  GPIO_InitTypeDef GPIO_Initure;                  //��ʼ��IO
  if(htim->Instance==TIM1)   
  {
		__HAL_RCC_TIM1_CLK_ENABLE();                  //ʹ�ܶ�ʱ��1
		__HAL_RCC_GPIOA_CLK_ENABLE();		              //����GPIOAʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_8|GPIO_PIN_9;      //PA8\9
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	        //��������
    GPIO_Initure.Pull=GPIO_PULLUP;        		    //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     	    //����
		GPIO_Initure.Alternate=GPIO_AF1_TIM1;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
  }
  else if(htim->Instance==TIM2)   
  {
		__HAL_RCC_TIM2_CLK_ENABLE();                    //ʹ�ܶ�ʱ��2
		__HAL_RCC_GPIOA_CLK_ENABLE();		            //����GPIOAʱ��
		__HAL_RCC_GPIOB_CLK_ENABLE();                   //����GPIOBʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_3;                    //PB3
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	        //��������
    GPIO_Initure.Pull=GPIO_PULLUP;        		    //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     	    //����
		GPIO_Initure.Alternate=GPIO_AF1_TIM2;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	  
		GPIO_Initure.Pin=GPIO_PIN_15;          		    //PA15
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
  }
	else if(htim->Instance==TIM4)   
  {
		__HAL_RCC_TIM4_CLK_ENABLE();                  //ʹ�ܶ�ʱ��4
		__HAL_RCC_GPIOB_CLK_ENABLE();		              //����GPIODʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;     //PB6/7
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	        //��������
    GPIO_Initure.Pull=GPIO_PULLUP;        		    //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     	    //����
		GPIO_Initure.Alternate=GPIO_AF2_TIM4;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
  }
	else if(htim->Instance==TIM3)   
  {
		__HAL_RCC_TIM3_CLK_ENABLE();                  //ʹ�ܶ�ʱ��3
		__HAL_RCC_GPIOB_CLK_ENABLE();		              //����GPIOBʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_4|GPIO_PIN_5;       //PB4/5
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	        //��������
    GPIO_Initure.Pull=GPIO_PULLUP;        		    //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     	    //����
		GPIO_Initure.Alternate=GPIO_AF2_TIM3;
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
  }
	else if(htim->Instance==TIM5)
  {
		__HAL_RCC_TIM5_CLK_ENABLE();                    //ʹ�ܶ�ʱ��5
		__HAL_RCC_GPIOH_CLK_ENABLE();		            //����GPIOHʱ��
	
		GPIO_Initure.Pin=GPIO_PIN_10|GPIO_PIN_11;       //PH10,PH11
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	        //��������
    GPIO_Initure.Pull=GPIO_PULLUP;        		   	//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     		//����
		GPIO_Initure.Alternate=GPIO_AF2_TIM5;			//PH10,11����ΪTIM5_CH1,2
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
  }
}


//TIM8 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM8_PWM_Init(u16 arr,u16 psc)
{ 
	
    TIM8_Handler.Instance=TIM8;            //��ʱ��8
    TIM8_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM8_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM8_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM8_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM8_Handler);       //��ʼ��PWM
    
    TIM8_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM8_CH1Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM8_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //����Ƚϼ���Ϊ��
		TIM8_CH1Handler.OCFastMode = TIM_OCFAST_DISABLE;
		TIM8_CH1Handler.OCIdleState = TIM_OCIDLESTATE_RESET;
		TIM8_CH1Handler.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	
		TIM8_CH2Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM8_CH2Handler.Pulse=arr/3;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ33%
    TIM8_CH2Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //����Ƚϼ���Ϊ��
		TIM8_CH2Handler.OCFastMode = TIM_OCFAST_DISABLE;
		TIM8_CH2Handler.OCIdleState = TIM_OCIDLESTATE_RESET;
		TIM8_CH2Handler.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	
		TIM8_CH3Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM8_CH3Handler.Pulse=arr/4;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ25%
    TIM8_CH3Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //����Ƚϼ���Ϊ��
		TIM8_CH3Handler.OCFastMode = TIM_OCFAST_DISABLE;
		TIM8_CH3Handler.OCIdleState = TIM_OCIDLESTATE_RESET;
		TIM8_CH3Handler.OCNIdleState = TIM_OCNIDLESTATE_RESET;
		
		TIM8_CH4Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM8_CH4Handler.Pulse=arr/5;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ20%
    TIM8_CH4Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //����Ƚϼ���Ϊ��
		TIM8_CH4Handler.OCFastMode = TIM_OCFAST_DISABLE;
		TIM8_CH4Handler.OCIdleState = TIM_OCIDLESTATE_RESET;
		TIM8_CH4Handler.OCNIdleState = TIM_OCNIDLESTATE_RESET;
		
		
    HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH1Handler,TIM_CHANNEL_1);//����TIM8ͨ��1
		HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH2Handler,TIM_CHANNEL_2);//����TIM8ͨ��2
		HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH3Handler,TIM_CHANNEL_3);//����TIM8ͨ��3
		HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH4Handler,TIM_CHANNEL_4);//����TIM8ͨ��4
    HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_1);//����ͨ��1234
		HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_2);//����ͨ��1234
		HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_3);//����ͨ��1234
		HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_4);//����ͨ��1234
			

}
//TIM9 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM9_PWM_Init(u16 arr,u16 psc)
{ 
    TIM9_Handler.Instance=TIM9;            //��ʱ��9
    TIM9_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM9_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM9_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM9_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM9_Handler);       //��ʼ��PWM
    
    TIM9_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM9_CH1Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM9_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //����Ƚϼ���Ϊ�� 
    HAL_TIM_PWM_ConfigChannel(&TIM9_Handler,&TIM9_CH1Handler,TIM_CHANNEL_1);//����TIM9ͨ��1
    HAL_TIM_PWM_Start(&TIM9_Handler,TIM_CHANNEL_1);//����PWMͨ��1
}

//TIM10 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM10_PWM_Init(u16 arr,u16 psc)
{ 
    TIM10_Handler.Instance=TIM10;            //��ʱ��10
    TIM10_Handler.Init.Prescaler=psc;       //��ʱ����Ƶ
    TIM10_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM10_Handler.Init.Period=arr;          //�Զ���װ��ֵ
    TIM10_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM10_Handler);       //��ʼ��TIM10
    
    TIM10_CH1Handler.OCMode=TIM_OCMODE_PWM1; //ģʽѡ��PWM1
    TIM10_CH1Handler.Pulse=arr/2;            //���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                            //Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM10_CH1Handler.OCPolarity=TIM_OCPOLARITY_HIGH; //����Ƚϼ���Ϊhigh
    HAL_TIM_PWM_ConfigChannel(&TIM10_Handler,&TIM10_CH1Handler,TIM_CHANNEL_1);//����TIM10ͨ��1
    HAL_TIM_PWM_Start_IT(&TIM10_Handler,TIM_CHANNEL_1);//����TIM10ͨ��1�ж�ģʽ
}
//  ����������ƺ�����10000����/ת������10mm��
//  ���뵥λmm��ת�ٵ�λ
void SendPulse(u8 distance)
{
	
	PU = distance * 1000 -1;
	TIM10_PWM_Init(1000-1,108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ1000����ôPWMƵ��Ϊ2M/1000=2kHZ
}
	

//��ʱ���ײ�������ʱ��ʹ�ܣ���������
//�˺����ᱻHAL_TIM_PWM_Init()����
//htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
   
		GPIO_InitTypeDef GPIO_Initure;
		
		if(htim->Instance==TIM8)
		{
			__HAL_RCC_TIM8_CLK_ENABLE();			//ʹ�ܶ�ʱ��8
			__HAL_RCC_GPIOC_CLK_ENABLE();			//����GPIOCʱ��
			
			GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;           	//PC6789
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;          //����
			GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
			GPIO_Initure.Alternate=GPIO_AF3_TIM8;	//PC6��7��8��9����ΪTIM8_CH1��2��3��4
			HAL_GPIO_Init(GPIOC,&GPIO_Initure);

		}
		else if(htim->Instance==TIM9)
		{
			__HAL_RCC_TIM9_CLK_ENABLE();			//ʹ�ܶ�ʱ��9
			__HAL_RCC_GPIOE_CLK_ENABLE();			//����GPIOEʱ��
		
			GPIO_Initure.Pin=GPIO_PIN_5;           	//PE5
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
			GPIO_Initure.Pull=GPIO_PULLUP;          //����
			GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
			GPIO_Initure.Alternate=GPIO_AF3_TIM9;	//PE5����ΪTIM9_CH1
			HAL_GPIO_Init(GPIOE,&GPIO_Initure);
		}
		else if(htim->Instance==TIM10)
		{
			__HAL_RCC_TIM10_CLK_ENABLE();			//ʹ�ܶ�ʱ��10
			__HAL_RCC_GPIOF_CLK_ENABLE();			//����GPIOFʱ��
		
			GPIO_Initure.Pin=GPIO_PIN_6;           	//PF6
			GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//�����������
			GPIO_Initure.Pull=GPIO_PULLDOWN;          //����
			GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
			GPIO_Initure.Alternate=GPIO_AF3_TIM10;	//PF6����ΪTIM9_CH1
			HAL_GPIO_Init(GPIOF,&GPIO_Initure);
			HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 3, 3);  //�ж����ȼ�1/3
			HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);          //����TIM10�ж�
			__HAL_TIM_ENABLE_IT(htim, TIM_IT_UPDATE);        //����TIM10�����ж�
		}
}

void TIM1_UP_TIM10_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM10_Handler);
}

//TIM10�жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{	
	
	
	if(htim==(&TIM10_Handler))
	{
//		printf("%d    %d\n",PU, RePU);	
		RePU ++;
		if(RePU>PU)
		{
			HAL_TIM_PWM_Stop_IT(&TIM10_Handler,TIM_CHANNEL_1);
			RePU = 0;
			PU = 0 ;
		}
		
	}
}

//����TIMͨ�� 1��ռ�ձ�
//compare:�Ƚ�ֵ
void TIM_SetTIM9Compare1(u16 compare)
{
	TIM9->CCR1=compare; 
}
void TIM_SetTIM8Compare1(u16 compare)
{
	TIM8_CH1Handler.Pulse=compare; 
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH1Handler,TIM_CHANNEL_1);//����TIM8ͨ��1
	HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_1);//����ͨ��1234
		
}
void TIM_SetTIM8Compare2(u16 compare)
{
	TIM8_CH2Handler.Pulse=compare; 
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH2Handler,TIM_CHANNEL_2);//����TIM8ͨ��2
	HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_2);//����ͨ��1234
		
}
void TIM_SetTIM8Compare3(u16 compare)
{
	TIM8_CH3Handler.Pulse=compare; 
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH3Handler,TIM_CHANNEL_3);//����TIM8ͨ��3
	HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_3);//����ͨ��1234
}
void TIM_SetTIM8Compare4(u16 compare)
{
	TIM8_CH4Handler.Pulse=compare; 
	HAL_TIM_PWM_ConfigChannel(&TIM8_Handler,&TIM8_CH4Handler,TIM_CHANNEL_4);//����TIM8ͨ��4
	HAL_TIM_PWM_Start(&TIM8_Handler,TIM_CHANNEL_4);//����ͨ��1234
}
