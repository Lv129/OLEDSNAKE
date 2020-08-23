#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "oled.h"
#include "myiic.h"
#include "snake.h"
#include "adc.h"
 int main(void)
 {	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
 	LED_Init();			     //LED�˿ڳ�ʼ��
	OLED_Init();			//��ʼ��OLED  
	Adc_Init();		  		//ADC��ʼ��
 	Snake_Init();     //�߳�ʼ��
  Map();     		    //��ͼ
  Food();    			  //ʳ��
	while(1) 	
	{		
     GUI();  
	}
}

