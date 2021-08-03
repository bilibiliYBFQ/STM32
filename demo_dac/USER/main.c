#include "sys.h"
#include "delay.h"
#include "led.h"
#include "dac.h"
#include "key.h"

 int main(void)
 { 	
	u8 wave=0;//波形分类
	u8 slot=10;//输出时隙
	u8 V = 0,num=0;//输出电压初始值，输出计数器
	delay_init();			//延时函数初始化
	Dac1_Init();		 	//DAC通道1初始化
	KEY_Init(); 			//按键初始化
	DAC_SetChannel1Data(DAC_Align_12b_R, V);
	while(1)
	{
		if(k1==0)//k1按下
		{			
			while(k1==0);//等待按键松开
			delay_ms(5);//延时消抖
			if(slot<20)//增加输出间隔
				slot++;
		}
		if(k2==0)//k1按下
		{	
			while(k2==0);//等待按键松开
			delay_ms(5);//延时消抖
			if(slot>1)//减少输出间隔
				slot--;
		}	
		if(k3)//k1按下
		{	
			while(k3);//等待按键松开
			delay_ms(5);//延时消抖
			wave++;
			if(wave>1)//减少输出间隔
				wave=0;
		}	
		
		switch(wave)
		{
			case 0:
							if(num<32)//三角波
							V=num*2;
							else
							V=(63-num)*2;
							break;
			case 1:
							V=num;//锯齿波
							break;
				
			default :break;
		}
		num++;
		if(num>63)
			num=0;
		delay_ms(slot);//设置波形输出间隔
		DAC_SetChannel1Data(DAC_Align_12b_R, V*64);//根据V值输出对应的电压
	}										    
}	
 


