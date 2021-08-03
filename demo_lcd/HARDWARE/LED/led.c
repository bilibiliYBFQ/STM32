#include "led.h"


void LED_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(LED_RCC, ENABLE);	 //ʹ�ܶ˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = LED_PIN;	 //�������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);	 //��ʼ��GPIO
}

