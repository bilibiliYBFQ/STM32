#ifndef __LCD_H
#define __LCD_H
#include "sys.h"

#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        128

//��ɫ���붨��
#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111


#define LCD_SCL  PBout(8)
#define LCD_SDA  PBout(9)
#define LCD_RES  PBout(6)
#define LCD_DC   PBout(5)
#define LCD_CS   PBout(7)
#define LCD_BLK   PBout(4)

/* ����SPI���ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�������뼴������ı���Ӧ������*/
#define LCD_SCL_GPIO_PORT	 GPIOB			            /* GPIO�˿� */
#define LCD_SCL_RCC 	     RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LCD_SCL_PIN		     GPIO_Pin_8			        /* ���ӵ�SCLʱ���ߵ�GPIO */

#define LCD_SDA_GPIO_PORT	 GPIOB			            /* GPIO�˿� */
#define LCD_SDA_RCC 	     RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LCD_SDA_PIN		     GPIO_Pin_9			        /* ���ӵ�SDA�����ߵ�GPIO */

#define LCD_RES_GPIO_PORT	 GPIOB			            /* GPIO�˿� */
#define LCD_RES_RCC 	     RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LCD_RES_PIN		     GPIO_Pin_6			        /* ���ӵ�RESʱ���ߵ�GPIO */

#define LCD_DC_GPIO_PORT	 GPIOB			            /* GPIO�˿� */
#define LCD_DC_RCC 	       RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LCD_DC_PIN		     GPIO_Pin_5			        /* ���ӵ�DC�����ߵ�GPIO */

#define LCD_CS_GPIO_PORT	 GPIOB			            /* GPIO�˿� */
#define LCD_CS_RCC	       RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LCD_CS_PIN		     GPIO_Pin_7			      /* ���ӵ�CS�����ߵ�GPIO */

#define LCD_BLK_GPIO_PORT	 GPIOB			            /* GPIO�˿� */
#define LCD_BLK_RCC	       RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LCD_BLK_PIN		     GPIO_Pin_4			      /* ���ӵ�BLK�����ߵ�GPIO */


void LCD_GPIO_Init(void);
void LCD_WriteIndex(u8 Index);
void LCD_WriteData(u8 Data);
void LCD_WriteData_16Bit(u16 Data);
void LCD_WriteReg(u8 Index,u8 Data);
void LCD_Reset(void);
void LCD_Init(void);
void LCD_SetRegion(u16 x_start,u16 y_start,u16 x_end,u16 y_end);
void LCD_SetXY(u16 x,u16 y);
void LCD_DrawPoint(u16 x,u16 y,u16 Data);
unsigned int LCD_ReadPoint(u16 x,u16 y);
void LCD_Clear(u16 Color);


u16 LCD_BGR2RGB(u16 c);
void LCD_Circle(u16 X,u16 Y,u16 R,u16 fc);
void LCD_DrawLine(u16 x0, u16 y0,u16 x1, u16 y1,u16 Color);
void LCD_box(u16 x, u16 y, u16 w, u16 h,u16 bc);
void LCD_box2(u16 x,u16 y,u16 w,u16 h, u8 mode);
void DisplayButtonDown(u16 x1,u16 y1,u16 x2,u16 y2);
void DisplayButtonUp(u16 x1,u16 y1,u16 x2,u16 y2);
void LCD_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void LCD_DrawFont_GBK24(u16 x, u16 y, u16 fc, u16 bc, u8 *s);
void LCD_DrawFont_Num32(u16 x, u16 y, u16 fc, u16 bc, u16 num);
void LCD_Showimage(u16 x0, u16 y0,u16 x1, u16 y1,const unsigned char *p);

#endif
