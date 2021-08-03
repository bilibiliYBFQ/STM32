#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "stdio.h"
#include "Picture.h"
#include "led.h"

int main(void)
{
	delay_init();
	LED_GPIO_Init();
	
	LCD_Init();
	
	LCD_BLK = 0;
	LCD_Clear(WHITE);
	
	LED=0;

	while(1)
	{
		LCD_Showimage(0, 0, 128, 128, gImage_2);
		delay_ms(3000);
		LCD_Showimage(0, 0, 128, 128, gImage_3);
		delay_ms(5000);
		
		LED=!LED;
	}		
}


