#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "timer.h"
#include "exti.h"
#include "sdram.h"
#include "tftlcd.h"
#include "ltdc.h"
#include "mpu.h"
#include "usmart.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "WM.h"
#include "includes.h"
#include "FramewinDLG.h"
#include "DIALOG.h"
/************************************************
 ALIENTEK STM32������

 UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
 ����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
 ���ȼ�0���жϷ������������� OS_IntQTask()
 ���ȼ�1��ʱ�ӽ������� OS_TickTask()
 ���ȼ�2����ʱ���� OS_TmrTask()
 ���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
 ���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
************************************************/

//�������ȼ�
#define START_TASK_PRIO				3
//�����ջ��С	
#define START_STK_SIZE 				128
//������ƿ�
OS_TCB StartTaskTCB;
//�����ջ	
CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				4
//�����ջ��С
#define TOUCH_STK_SIZE				128
//������ƿ�
OS_TCB TouchTaskTCB;
//�����ջ
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *p_arg);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				5
//�����ջ��С
#define LED0_STK_SIZE				128
//������ƿ�
OS_TCB Led0TaskTCB;
//�����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *p_arg);

//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO			6
//�����ջ��С
#define EMWINDEMO_STK_SIZE			512
//������ƿ�
OS_TCB EmwindemoTaskTCB;
//�����ջ
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task����
void emwindemo_task(void *p_arg);

//����������ת��Ϊ�Ƕ�
double count_to_angle(u16 count)
{
	double angle = 0.0;
	angle = count / 10000 * 360;
	return angle;
}

int main(void)
{  
  OS_ERR err;
	CPU_SR_ALLOC();
    
	Write_Through();                //Cahceǿ��͸д
	MPU_Memory_Protection();        //������ش洢����
	Cache_Enable();                 //��L1-Cache
      
	Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
	HAL_Init();				        //��ʼ��HAL��
	delay_init(216);                //��ʱ��ʼ��
	uart2_init(115200);		        //���ڳ�ʼ��
	EXTI_Init();                     //������ʼ��
	LED_Init();                     //��ʼ��LED
	SDRAM_Init();                   //SDRAM��ʼ��
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
  my_mem_init(SRAMIN);		    //��ʼ���ڲ��ڴ��
	my_mem_init(SRAMEX);		    //��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMDTCM);		    //��ʼ��DTCM�ڴ��
    
  OSInit(&err);		            //��ʼ��UCOSIII
	OS_CRITICAL_ENTER();            //�����ٽ���
	//������ʼ����
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//������ƿ�
				 (CPU_CHAR	* )"start task", 		//��������
                 (OS_TASK_PTR )start_task, 			//������
                 (void		* )0,					//���ݸ��������Ĳ���
                 (OS_PRIO	  )START_TASK_PRIO,     //�������ȼ�
                 (CPU_STK   * )&START_TASK_STK[0],	//�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		//�����ջ��С
                 (OS_MSG_QTY  )0,					//�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	  )0,					//��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void   	* )0,					//�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR 	* )&err);				//��Ÿú�������ʱ�ķ���ֵ
	OS_CRITICAL_EXIT();	            //�˳��ٽ���	 
	OSStart(&err);                  //����UCOSIII
	while(1);
}

//��ʼ������
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;

	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	//ʹ��ʱ��Ƭ��ת���ȹ���,����Ĭ�ϵ�ʱ��Ƭ����
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif		
	__HAL_RCC_CRC_CLK_ENABLE();		//ʹ��CRCʱ��
    WM_SetCreateFlags(WM_CF_MEMDEV);//����STemWin�洢�豸
	GUI_Init();  			//STemWin��ʼ��
	WM_MULTIBUF_Enable(1);  //����STemWin�໺��,RGB�����ܻ��õ�
	OS_CRITICAL_ENTER();	//�����ٽ���
	//STemWin Demo����	
	OSTaskCreate((OS_TCB*     )&EmwindemoTaskTCB,		
				 (CPU_CHAR*   )"Emwindemo task", 		
                 (OS_TASK_PTR )emwindemo_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )EMWINDEMO_TASK_PRIO,     
                 (CPU_STK*    )&EMWINDEMO_TASK_STK[0],	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE/10,	
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);
	//����������
	OSTaskCreate((OS_TCB*     )&TouchTaskTCB,		
				 (CPU_CHAR*   )"Touch task", 		
                 (OS_TASK_PTR )touch_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )TOUCH_TASK_PRIO,     
                 (CPU_STK*    )&TOUCH_TASK_STK[0],	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE/10,	
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);			 
	//LED0����
	OSTaskCreate((OS_TCB*     )&Led0TaskTCB,		
				 (CPU_CHAR*   )"Led0 task", 		
                 (OS_TASK_PTR )led0_task, 			
                 (void*       )0,					
                 (OS_PRIO	  )LED0_TASK_PRIO,     
                 (CPU_STK*    )&LED0_TASK_STK[0],	
                 (CPU_STK_SIZE)LED0_STK_SIZE/10,	
                 (CPU_STK_SIZE)LED0_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void*       )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR*     )&err);	                 
	OS_TaskSuspend((OS_TCB*)&StartTaskTCB,&err);		//����ʼ����			 
	OS_CRITICAL_EXIT();	//�˳��ٽ���
}

//EMWINDEMO����
void emwindemo_task(void *p_arg)
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
	//����Ƥ��
	BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX); 
	CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
	MENU_SetDefaultSkin(MENU_SKIN_FLEX);
	MULTIPAGE_SetDefaultSkin(MULTIPAGE_SKIN_FLEX);
	PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
	SPINBOX_SetDefaultSkin(SPINBOX_SKIN_FLEX);
	CreateFramewin();
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
		GUI_Delay(100);
	}
}

//TOUCH����
void touch_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		GUI_TOUCH_Exec();	
		OSTimeDlyHMSM(0,0,0,5,OS_OPT_TIME_PERIODIC,&err);//��ʱ5ms
	}
}

//LED0����
void led0_task(void *p_arg)
{
	OS_ERR err;
	while(1)
	{
		LED0_Toggle;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);//��ʱ500ms
	}
}

