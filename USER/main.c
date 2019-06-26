#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "exti.h"
#include "tftlcd.h"
#include "mpu.h"
#include "sdram.h"
#include "touch.h"
#include "malloc.h"
#include "GUI.h"
#include "WM.h"
#include "GUIDEMO.h"
#include "FramewinDLG.h"
/************************************************
 ALIENTEK ������STM32F7������ 
************************************************/

//����������ת��Ϊ�Ƕ�
double count_to_angle(u16 count)
{
	double angle = 0.0;
	angle = count / 10000 * 360;
	return angle;
}

int main(void)
{
	u16 count1 = 0;
	u16 count2 = 0;
	u16 count3 = 0;
	u16 count4 = 0;
	u16 count5 = 0;	
	double angle1 = 0.0;
	double angle2 = 0.0;
	double angle3 = 0.0;
	double angle4 = 0.0;
	double angle5 = 0.0;
	Write_Through();                //Cahceǿ��͸д
	MPU_Memory_Protection();    	//�ڴ汣��
    Cache_Enable();                 //��L1-Cache
	
    HAL_Init();				           //��ʼ��HAL��
    Stm32_Clock_Init(432, 25, 2, 9);   //����ʱ��,216Mhz 
    SDRAM_Init();                   //��ʼ��SDRAM
    delay_init(216);                //��ʱ��ʼ��
	uart2_init(115200);		       	//����2��ʼ��
    LED_Init();                     //��ʼ��LED	
	EXTI_Init();                    //�ⲿ�жϳ�ʼ��
	TFTLCD_Init();                  //��ʼ��LCD
	TP_Init();				        //��������ʼ�� 
	// ��ʼ����ʱ��1-5���ڹؽڱ���������
	TIM1_Encoder_Init(0xFFFF-1, 1-1);  //��ʼ��������1 ��ʱ����
	TIM2_Encoder_Init(0xFFFF-1, 1-1);	 //��ʼ��������2 ��ʱ����
	TIM3_Encoder_Init(0xFFFF-1, 1-1);	 //��ʼ��������3 ˳ʱ����
	TIM4_Encoder_Init(0xFFFF-1, 1-1);	 //��ʼ��������4 ˳ʱ����
	TIM5_Encoder_Init(0xFFFF-1, 1-1);	 //��ʼ��������5 ˳ʱ����
	//��ʼ����ʱ��6/7�����ṩϵͳʱ��
//	TIM6_Init(999, 108 - 1);             //1KHZ ��ʱ��6����Ϊ1ms
//  TIM7_Init(999, 1080 - 1);            //������ɨ���ٶ�,100HZ.
	//��ʼ����ʱ��8/9���ڿ���PMW���
	TIM8_PWM_Init(100-1, 108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
	TIM9_PWM_Init(100-1, 108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
	//�ڴ��ʼ��
	my_mem_init(SRAMIN);		    //��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		    //��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMDTCM);		    //��ʼ��DTCM�ڴ��
	
	//��ʼ������������
	__HAL_RCC_CRC_CLK_ENABLE();		 //ʹ��CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV); //����STemWin�洢�豸
	GUI_Init(); 					 //��ʼ��GUI
    GUI_SetBkColor(GUI_BLACK);       //������ɫ
	GUI_Clear();				     //����
	GUI_SetColor(GUI_YELLOW);        //������ɫ
	GUI_SetFont(&GUI_Font24_ASCII);  //��������
	GUI_DispStringHCenterAt("Auxiliary Drilling Device For Spinal Surgery", 240, 0); //ָ��λ����ʾ
	GUI_DispStringAt("relative angles", 10, 520); //ָ��λ����ʾ
	GUI_DispStringAt("angle1:", 10, 550); //ָ��λ����ʾ
	GUI_DispStringAt("angle2:", 10, 600); //ָ��λ����ʾ
	GUI_DispStringAt("angle3:", 10, 650); //ָ��λ����ʾ
	GUI_DispStringAt("angle4:", 10, 700); //ָ��λ����ʾ
	GUI_DispStringAt("angle5:", 10, 750); //ָ��λ����ʾ
	CreateFramewin();
//	WM_MULTIBUF_Enable(1);  //����STemWin�໺��,RGB�����ܻ��õ�
//	GUIDEMO_Main();					//STemWin ��ʾdemo
	while(1)
    {
			count1=__HAL_TIM_GET_COUNTER(&TIM1_Handler);
			count2=__HAL_TIM_GET_COUNTER(&TIM2_Handler);
			count3=__HAL_TIM_GET_COUNTER(&TIM3_Handler);
			count4=__HAL_TIM_GET_COUNTER(&TIM4_Handler);
			count5=__HAL_TIM_GET_COUNTER(&TIM5_Handler);
			angle1 = count_to_angle(count1);
			angle2 = count_to_angle(count2);
			angle3 = count_to_angle(count3);
			angle4 = count_to_angle(count4);
			angle5 = count_to_angle(count5);
			GUI_GotoXY(85, 550);
			GUI_DispSFloatFix(angle1,6,1);
			GUI_GotoXY(85, 600);
			GUI_DispSFloatFix(angle2,6,1);
			GUI_GotoXY(85, 650);
			GUI_DispSFloatFix(angle3,6,1);
			GUI_GotoXY(85, 700);
			GUI_DispSFloatFix(angle4,6,1);
			GUI_GotoXY(85, 750);
			GUI_DispSFloatFix(angle5,6,1);
			delay_ms(10);
	}

}

