#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"
#include "exti.h"
#include "lcd.h"
#include "mpu.h"
#include "sdram.h"
/************************************************
 ALIENTEK ������STM32F7������ 
************************************************/

u16 testsram[250000] __attribute__((at(0XC0000000)));//����������

//SDRAM�ڴ����	    
void fsmc_sdram_test(u16 x,u16 y)
{  
	u32 i=0;  	  
	u32 temp=0;	   
	u32 sval=0;	//�ڵ�ַ0����������	  				   
  	LCD_ShowString(x,y,180,y+16,16,"Ex Memory Test:    0KB "); 
	//ÿ��16K�ֽ�,д��һ������,�ܹ�д��2048������,�պ���32M�ֽ�
	for(i=0;i<32*1024*1024;i+=16*1024)
	{
		*(vu32*)(Bank5_SDRAM_ADDR+i)=temp; 
		temp++;
	}
	//���ζ���֮ǰд�������,����У��		  
 	for(i=0;i<32*1024*1024;i+=16*1024) 
	{	
  		temp=*(vu32*)(Bank5_SDRAM_ADDR+i);
		if(i==0)sval=temp;
 		else if(temp<=sval)break;//�������������һ��Ҫ�ȵ�һ�ζ��������ݴ�.	   		   
		LCD_ShowxNum(x+15*8,y,(u16)(temp-sval+1)*16,5,16,0);	//��ʾ�ڴ�����  
		printf("SDRAM Capacity:%dKB\r\n",(u16)(temp-sval+1)*16);//��ӡSDRAM����
 	}					 
}	

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
		u8 lcd_id[12];
		u8 x = 0;
		u32 ts = 0;
    Cache_Enable();                 //��L1-Cache
    HAL_Init();				        //��ʼ��HAL��
    Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
    SDRAM_Init();                   //��ʼ��SDRAM
    delay_init(216);                //��ʱ��ʼ��
		uart2_init(115200);		        //����2��ʼ��
    LED_Init();                     //��ʼ��LED	
		EXTI_Init();                    //�ⲿ�жϳ�ʼ��
    TIM8_PWM_Init(100-1,108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
		TIM9_PWM_Init(100-1,108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
		LCD_Init();                     //��ʼ��LCD
    POINT_COLOR=RED; 
		sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣	
		
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
		
		//�ڴ汣��
		MPU_Memory_Protection();
//		MPU_Set_Protection(0X20002000,MPU_REGION_SIZE_128B,MPU_REGION_NUMBER0,MPU_REGION_PRIV_RO_URO);//ֻ��  
//		printf("MPU open!\r\n");	//��ʾMPU��
		

		//SDRAM����
		for(ts=0;ts<250000;ts++)
		{
		testsram[ts]=ts;//Ԥ���������	 
  	}
		fsmc_sdram_test(30,170);//����SRAM����
		LCD_ShowxNum(30,190,testsram[ts],6,16,0);//��ʾ��������	
		printf("testsram[%d]:%d\r\n",ts,testsram[ts]);
		
    while(1)
    {
				delay_ms(1000);	 	
				count1=__HAL_TIM_GET_COUNTER(&TIM1_Handler);
				count2=__HAL_TIM_GET_COUNTER(&TIM2_Handler);
				count3=__HAL_TIM_GET_COUNTER(&TIM3_Handler);
				count4=__HAL_TIM_GET_COUNTER(&TIM4_Handler);
				count5=__HAL_TIM_GET_COUNTER(&TIM5_Handler);
				printf("%d   %d   %d   %d    %d\n",count1,count2,count3,count4,count5);	
				switch(x)
				{
						case 0:LCD_Clear(WHITE);break;
						case 1:LCD_Clear(BLACK);break;
						case 2:LCD_Clear(BLUE);break;
						case 3:LCD_Clear(RED);break;
						case 4:LCD_Clear(MAGENTA);break;
						case 5:LCD_Clear(GREEN);break;
						case 6:LCD_Clear(CYAN);break; 
						case 7:LCD_Clear(YELLOW);break;
						case 8:LCD_Clear(BRRED);break;
						case 9:LCD_Clear(GRAY);break;
						case 10:LCD_Clear(LGRAY);break;
						case 11:LCD_Clear(BROWN);break;
				}
				POINT_COLOR=RED;	  
				LCD_ShowString(10,40,260,32,32,"Apollo STM32F4/F7"); 	
				LCD_ShowString(10,80,240,24,24,"TFTLCD TEST");
				LCD_ShowString(10,110,240,16,16,"ATOM@ALIENTEK");
				LCD_ShowString(10,130,240,16,16,lcd_id);		//��ʾLCD ID	      					 
				LCD_ShowString(10,150,240,12,12,"2016/7/11");	      					 
				x++;
				if(x==12)x=0;
				LED0_Toggle;

				
    } 
}
