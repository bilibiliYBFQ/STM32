#ifndef STM_LED_H
#define STM_LED_H
#include "sys.h"


#define LED  PAout(8)

/* ����SPI���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�������뼴������ı���Ӧ������*/
#define LED_GPIO_PORT	 GPIOA			            /* GPIO�˿� */
#define LED_RCC 	     RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LED_PIN		     GPIO_Pin_8	

void LED_GPIO_Init(void);

#endif

