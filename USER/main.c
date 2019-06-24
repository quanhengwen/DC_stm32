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
/************************************************
 ALIENTEK ������STM32F7������ 
************************************************/

//u16 testsram[250000] __attribute__((at(0XC0000000)));//����������

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

//�����Ļ�������Ͻ���ʾ"RST"
void Load_Drow_Dialog(void)
{
		LCD_Clear(WHITE);//����   
		POINT_COLOR=BLUE;//��������Ϊ��ɫ 
		LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
		POINT_COLOR=RED;//���û�����ɫ 
}
////////////////////////////////////////////////////////////////////////////////
//���ݴ�����ר�в���
//��ˮƽ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	if(len==0)return;
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//��ʵ��Բ
//x0,y0:����
//r:�뾶
//color:��ɫ
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax)// draw lines from outside  
		{
 			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}  
//������֮��ľ���ֵ 
//x1,x2����ȡ��ֵ��������
//����ֵ��|x1-x2|
u16 my_abs(u16 x1,u16 x2)
{			 
	if(x1>x2)return x1-x2;
	else return x2-x1;
}  
//��һ������
//(x1,y1),(x2,y2):��������ʼ����
//size�������Ĵ�ϸ�̶�
//color����������ɫ
void lcd_draw_bline(u16 x1, u16 y1, u16 x2, u16 y2,u8 size,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	if(x1<size|| x2<size||y1<size|| y2<size)return; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		gui_fill_circle(uRow,uCol,size,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   
////////////////////////////////////////////////////////////////////////////////
//5�����ص����ɫ(���ݴ�������)												 
const u16 POINT_COLOR_TBL[5]={RED,GREEN,BLUE,BROWN,GRED};  

//���ݴ��������Ժ���
void ctp_test(void)
{
	u8 t=0;
	u8 i=0;	  	
	u16 count1 = 0;
	u16 count2 = 0;
	u16 count3 = 0;
	u16 count4 = 0;
	u16 count5 = 0;	
 	u16 lastpos[5][2];		//���һ�ε����� 
	while(1)
	{
		tp_dev.scan(0);
		for(t=0;t<5;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
                //printf("X����:%d,Y����:%d\r\n",tp_dev.x[0],tp_dev.y[0]);
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
                    
					lcd_draw_bline(lastpos[t][0],lastpos[t][1],tp_dev.x[t],tp_dev.y[t],2,POINT_COLOR_TBL[t]);//����
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					if(tp_dev.x[t]>(lcddev.width-24)&&tp_dev.y[t]<20)
					{
						Load_Drow_Dialog();//���
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}
		
		delay_ms(5);i++;
		if(i%20==0)LED0_Toggle;
		
		 	
		count1=__HAL_TIM_GET_COUNTER(&TIM1_Handler);
		count2=__HAL_TIM_GET_COUNTER(&TIM2_Handler);
		count3=__HAL_TIM_GET_COUNTER(&TIM3_Handler);
		count4=__HAL_TIM_GET_COUNTER(&TIM4_Handler);
		count5=__HAL_TIM_GET_COUNTER(&TIM5_Handler);
		LCD_ShowxNum(30,500,count1,6,24,0);
		LCD_ShowxNum(30,540,count2,6,24,0);
		LCD_ShowxNum(30,580,count3,6,24,0);
		LCD_ShowxNum(30,620,count4,6,24,0);
		LCD_ShowxNum(30,660,count5,6,24,0);
//		printf("%d   %d   %d   %d    %d\n",count1,count2,count3,count4,count5);	
		
	}	
}


int main(void)
{
		u16 val1 = 0;   //0.68V
		u16 val2 = 0;   //1.33V
		u16 val3 = 0;   //1.99V
		u16 val4 = 0;   //2.64V
		u16 val5 = 0;     //3.30V
		
		u8 lcd_id[12];
//		u8 x = 0;
//		u32 ts = 0;
    Cache_Enable();                 //��L1-Cache
    HAL_Init();				              //��ʼ��HAL��
    Stm32_Clock_Init(432,25,2,9);   //����ʱ��,216Mhz 
    SDRAM_Init();                   //��ʼ��SDRAM
    delay_init(216);                //��ʱ��ʼ��
		uart2_init(115200);		       	 //����2��ʼ��
    LED_Init();                     //��ʼ��LED	
		EXTI_Init();                    //�ⲿ�жϳ�ʼ��
    TIM8_PWM_Init(100-1,108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
		TIM9_PWM_Init(100-1,108-1);     //216M/108=2M�ļ���Ƶ�ʣ��Զ���װ��Ϊ100����ôPWMƵ��Ϊ2M/100=20kHZ
		TFTLCD_Init();                     //��ʼ��LCD
		tp_dev.init();				    			//��������ʼ�� 
		my_mem_init(SRAMIN);		    //��ʼ���ڲ��ڴ��
		my_mem_init(SRAMEX);		    //��ʼ���ⲿ�ڴ��
		my_mem_init(SRAMDTCM);		    //��ʼ��DTCM�ڴ��
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
//		for(ts=0;ts<250000;ts++)
//		{
//		testsram[ts]=ts;//Ԥ���������	 
//  	}
//		fsmc_sdram_test(30,170);//����SRAM����
//		LCD_ShowxNum(30,190,testsram[ts],6,16,0);//��ʾ��������	
//		printf("testsram[%d]:%d\r\n",ts,testsram[ts]);
		
		Load_Drow_Dialog();	 	
	  ctp_test();//����������

}
