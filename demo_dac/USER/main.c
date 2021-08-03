#include "sys.h"
#include "delay.h"
#include "led.h"
#include "dac.h"
#include "key.h"

 int main(void)
 { 	
	u8 wave=0;//���η���
	u8 slot=10;//���ʱ϶
	u8 V = 0,num=0;//�����ѹ��ʼֵ�����������
	delay_init();			//��ʱ������ʼ��
	Dac1_Init();		 	//DACͨ��1��ʼ��
	KEY_Init(); 			//������ʼ��
	DAC_SetChannel1Data(DAC_Align_12b_R, V);
	while(1)
	{
		if(k1==0)//k1����
		{			
			while(k1==0);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����
			if(slot<20)//����������
				slot++;
		}
		if(k2==0)//k1����
		{	
			while(k2==0);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����
			if(slot>1)//����������
				slot--;
		}	
		if(k3)//k1����
		{	
			while(k3);//�ȴ������ɿ�
			delay_ms(5);//��ʱ����
			wave++;
			if(wave>1)//����������
				wave=0;
		}	
		
		switch(wave)
		{
			case 0:
							if(num<32)//���ǲ�
							V=num*2;
							else
							V=(63-num)*2;
							break;
			case 1:
							V=num;//��ݲ�
							break;
				
			default :break;
		}
		num++;
		if(num>63)
			num=0;
		delay_ms(slot);//���ò���������
		DAC_SetChannel1Data(DAC_Align_12b_R, V*64);//����Vֵ�����Ӧ�ĵ�ѹ
	}										    
}	
 


