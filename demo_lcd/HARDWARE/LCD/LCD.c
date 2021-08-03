#include "lcd.h"
#include "delay.h"
#include "font.h"

//Һ��IO��ʼ������
void LCD_GPIO_Init(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(LCD_SCL_RCC | LCD_SDA_RCC | LCD_RES_RCC | \
                         LCD_DC_RCC | LCD_CS_RCC| LCD_BLK_RCC, ENABLE);	 //ʹ�ܶ˿�ʱ��

  GPIO_InitStructure.GPIO_Pin = LCD_SCL_PIN;	 //�������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
  GPIO_Init(LCD_SCL_GPIO_PORT, &GPIO_InitStructure);	 //��ʼ��GPIO

  GPIO_InitStructure.GPIO_Pin = LCD_SDA_PIN;	 //�������
  GPIO_Init(LCD_SDA_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO

  GPIO_InitStructure.GPIO_Pin = LCD_RES_PIN;	 //�������
  GPIO_Init(LCD_RES_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO

  GPIO_InitStructure.GPIO_Pin = LCD_DC_PIN;	 //�������
  GPIO_Init(LCD_DC_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO

  GPIO_InitStructure.GPIO_Pin = LCD_CS_PIN;	 //�������
  GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO
  
  GPIO_InitStructure.GPIO_Pin = LCD_BLK_PIN;	 //�������
  GPIO_Init(LCD_BLK_GPIO_PORT, &GPIO_InitStructure);//��ʼ��GPIO

}
//��SPI���ߴ���һ��8λ����
void  SPI_WriteData(u8 Data)
{
  unsigned char i = 0;
  for(i = 8; i > 0; i--)
  {
    if(Data & 0x80)
      LCD_SDA = 1; //�������
    else LCD_SDA = 0;

    LCD_SCL = 0;
    LCD_SCL = 1;
    Data <<= 1;
  }
}

//��Һ����дһ��8λָ��
void LCD_WriteIndex(u8 Index)
{
  //SPI д����ʱ��ʼ
  LCD_CS = 0;
  LCD_DC = 0;
  SPI_WriteData(Index);
  LCD_CS = 1;
}

//��Һ����дһ��8λ����
void LCD_WriteData(u8 Data)
{
  LCD_CS = 0;
  LCD_DC = 1;
  SPI_WriteData(Data);
  LCD_CS = 1;
}
//��Һ����дһ��16λ����
void LCD_WriteData_16Bit(u16 Data)
{
  LCD_CS = 0;
  LCD_DC = 1;
  SPI_WriteData(Data >> 8); 	//д���8λ����
  SPI_WriteData(Data); 			//д���8λ����
  LCD_CS = 1;
}

void LCD_WriteReg(u8 Index, u8 Data)
{
  LCD_WriteIndex(Index);
  LCD_WriteData(Data);
}

//��λLCD
void LCD_Reset(void)
{
  LCD_RES = 0;
  delay_ms(100);
  LCD_RES = 1;
  delay_ms(50);
}

//LCD ��ʼ��������ο������ֲ�
void LCD_Init(void)
{
  LCD_GPIO_Init();
  LCD_Reset(); //Reset before LCD Init.

  //LCD Init For 1.44Inch LCD Panel with ST7735R.
  LCD_WriteIndex(0x11);//Sleep exit
  delay_ms (120);

  //ST7735R Frame Rate
  LCD_WriteIndex(0xB1);
  LCD_WriteData(0x01);
  LCD_WriteData(0x2C);
  LCD_WriteData(0x2D);

  LCD_WriteIndex(0xB2);
  LCD_WriteData(0x01);
  LCD_WriteData(0x2C);
  LCD_WriteData(0x2D);

  LCD_WriteIndex(0xB3);
  LCD_WriteData(0x01);
  LCD_WriteData(0x2C);
  LCD_WriteData(0x2D);
  LCD_WriteData(0x01);
  LCD_WriteData(0x2C);
  LCD_WriteData(0x2D);

  LCD_WriteIndex(0xB4); //Column inversion
  LCD_WriteData(0x07);

  //ST7735R Power Sequence
  LCD_WriteIndex(0xC0);
  LCD_WriteData(0xA2);
  LCD_WriteData(0x02);
  LCD_WriteData(0x84);
  LCD_WriteIndex(0xC1);
  LCD_WriteData(0xC5);

  LCD_WriteIndex(0xC2);
  LCD_WriteData(0x0A);
  LCD_WriteData(0x00);

  LCD_WriteIndex(0xC3);
  LCD_WriteData(0x8A);
  LCD_WriteData(0x2A);
  LCD_WriteIndex(0xC4);
  LCD_WriteData(0x8A);
  LCD_WriteData(0xEE);

  LCD_WriteIndex(0xC5); //VCOM
  LCD_WriteData(0x0E);

  LCD_WriteIndex(0x36); //MX, MY, RGB mode
  LCD_WriteData(0xC8);

  //ST7735R Gamma Sequence
  LCD_WriteIndex(0xe0);
  LCD_WriteData(0x0f);
  LCD_WriteData(0x1a);
  LCD_WriteData(0x0f);
  LCD_WriteData(0x18);
  LCD_WriteData(0x2f);
  LCD_WriteData(0x28);
  LCD_WriteData(0x20);
  LCD_WriteData(0x22);
  LCD_WriteData(0x1f);
  LCD_WriteData(0x1b);
  LCD_WriteData(0x23);
  LCD_WriteData(0x37);
  LCD_WriteData(0x00);
  LCD_WriteData(0x07);
  LCD_WriteData(0x02);
  LCD_WriteData(0x10);

  LCD_WriteIndex(0xe1);
  LCD_WriteData(0x0f);
  LCD_WriteData(0x1b);
  LCD_WriteData(0x0f);
  LCD_WriteData(0x17);
  LCD_WriteData(0x33);
  LCD_WriteData(0x2c);
  LCD_WriteData(0x29);
  LCD_WriteData(0x2e);
  LCD_WriteData(0x30);
  LCD_WriteData(0x30);
  LCD_WriteData(0x39);
  LCD_WriteData(0x3f);
  LCD_WriteData(0x00);
  LCD_WriteData(0x07);
  LCD_WriteData(0x03);
  LCD_WriteData(0x10);

  LCD_WriteIndex(0x2a);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);
  LCD_WriteData(0x7f);

  LCD_WriteIndex(0x2b);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);
  LCD_WriteData(0x00);
  LCD_WriteData(0x9f);

  LCD_WriteIndex(0xF0); //Enable test command
  LCD_WriteData(0x01);
  LCD_WriteIndex(0xF6); //Disable ram power save mode
  LCD_WriteData(0x00);

  LCD_WriteIndex(0x3A); //65k mode
  LCD_WriteData(0x05);


  LCD_WriteIndex(0x29);//Display on
}


/*************************************************
��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����
*************************************************/
void LCD_SetRegion(u16 x_start, u16 y_start, u16 x_end, u16 y_end)
{
  LCD_WriteIndex(0x2a);
  LCD_WriteData(0x00);
  LCD_WriteData(x_start + 2);
  LCD_WriteData(0x00);
  LCD_WriteData(x_end + 2);

  LCD_WriteIndex(0x2b);
  LCD_WriteData(0x00);
  LCD_WriteData(y_start + 3);
  LCD_WriteData(0x00);
  LCD_WriteData(y_end + 3);

  LCD_WriteIndex(0x2c);

}

/*************************************************
��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����
*************************************************/
void LCD_SetXY(u16 x, u16 y)
{
  LCD_SetRegion(x, y, x, y);
}


/*************************************************
��������LCD_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����
*************************************************/
void LCD_DrawPoint(u16 x, u16 y, u16 Data)
{
  LCD_SetRegion(x, y, x + 1, y + 1);
  LCD_WriteData_16Bit(Data);

}

/*****************************************
 �������ܣ���TFTĳһ�����ɫ
 ���ڲ�����color  ����ɫֵ
******************************************/
unsigned int LCD_ReadPoint(u16 x, u16 y)
{
  unsigned int Data;
  LCD_SetXY(x, y);

  //LCD_ReadData();//���������ֽ�
  //Data=LCD_ReadData();
  LCD_WriteData(Data);
  return Data;
}
/*************************************************
��������LCD_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����
*************************************************/
void LCD_Clear(u16 Color)
{
  unsigned int i, m;
  LCD_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
  LCD_WriteIndex(0x2C);
  for(i = 0; i < X_MAX_PIXEL; i++)
    for(m = 0; m < Y_MAX_PIXEL; m++)
    {
      LCD_WriteData_16Bit(Color);
    }
}

//��ILI93xx����������ΪGBR��ʽ��������д���ʱ��ΪRGB��ʽ��
//ͨ���ú���ת��
//c:GBR��ʽ����ɫֵ
//����ֵ��RGB��ʽ����ɫֵ
u16 LCD_BGR2RGB(u16 c)
{
  u16  r, g, b, rgb;
  b = (c >> 0) & 0x1f;
  g = (c >> 5) & 0x3f;
  r = (c >> 11) & 0x1f;
  rgb = (b << 11) + (g << 5) + (r << 0);
  return(rgb);
}


//��Բ
void LCD_Circle(u16 X, u16 Y, u16 R, u16 fc)
{
  //Bresenham�㷨
  unsigned short  a, b;
  int c;
  a = 0;
  b = R;
  c = 3 - 2 * R;
  while (a < b)
  {
    LCD_DrawPoint(X + a, Y + b, fc); //        7
    LCD_DrawPoint(X - a, Y + b, fc); //        6
    LCD_DrawPoint(X + a, Y - b, fc); //        2
    LCD_DrawPoint(X - a, Y - b, fc); //        3
    LCD_DrawPoint(X + b, Y + a, fc); //        8
    LCD_DrawPoint(X - b, Y + a, fc); //        5
    LCD_DrawPoint(X + b, Y - a, fc); //        1
    LCD_DrawPoint(X - b, Y - a, fc); //        4

    if(c < 0) c = c + 4 * a + 6;
    else
    {
      c = c + 4 * (a - b) + 10;
      b -= 1;
    }
    a += 1;
  }
  if (a == b)
  {
    LCD_DrawPoint(X + a, Y + b, fc);
    LCD_DrawPoint(X + a, Y + b, fc);
    LCD_DrawPoint(X + a, Y - b, fc);
    LCD_DrawPoint(X - a, Y - b, fc);
    LCD_DrawPoint(X + b, Y + a, fc);
    LCD_DrawPoint(X - b, Y + a, fc);
    LCD_DrawPoint(X + b, Y - a, fc);
    LCD_DrawPoint(X - b, Y - a, fc);
  }
}

//���ߺ�����ʹ��Bresenham �����㷨
void LCD_DrawLine(u16 x0, u16 y0, u16 x1, u16 y1, u16 Color)
{
  int dx,             // difference in x's
      dy,             // difference in y's
      dx2,            // dx,dy * 2
      dy2,
      x_inc,          // amount in pixel space to move during drawing
      y_inc,          // amount in pixel space to move during drawing
      error,          // the discriminant i.e. error i.e. decision variable
      index;          // used for looping


  LCD_SetXY(x0, y0);
  dx = x1 - x0; //����x����
  dy = y1 - y0; //����y����

  if (dx >= 0)
  {
    x_inc = 1;
  }
  else
  {
    x_inc = -1;
    dx    = -dx;
  }

  if (dy >= 0)
  {
    y_inc = 1;
  }
  else
  {
    y_inc = -1;
    dy    = -dy;
  }

  dx2 = dx << 1;
  dy2 = dy << 1;

  if (dx > dy)//x�������y���룬��ôÿ��x����ֻ��һ���㣬ÿ��y���������ɸ���
  {
    //���ߵĵ�������x���룬��x���������
    // initialize error term
    error = dy2 - dx;

    // draw the line
    for (index = 0; index <= dx; index++) //Ҫ���ĵ������ᳬ��x����
    {
      //����
      LCD_DrawPoint(x0, y0, Color);

      // test if error has overflowed
      if (error >= 0) //�Ƿ���Ҫ����y����ֵ
      {
        error -= dx2;

        // move to next line
        y0 += y_inc; //����y����ֵ
      } // end if error overflowed

      // adjust the error term
      error += dy2;

      // move to the next pixel
      x0 += x_inc; //x����ֵÿ�λ���󶼵���1
    } // end for
  } // end if |slope| <= 1
  else//y�����x�ᣬ��ÿ��y����ֻ��һ���㣬x�����ɸ���
  {
    //��y��Ϊ��������
    // initialize error term
    error = dx2 - dy;

    // draw the line
    for (index = 0; index <= dy; index++)
    {
      // set the pixel
      LCD_DrawPoint(x0, y0, Color);

      // test if error overflowed
      if (error >= 0)
      {
        error -= dy2;

        // move to next line
        x0 += x_inc;
      } // end if error overflowed

      // adjust the error term
      error += dx2;

      // move to the next pixel
      y0 += y_inc;
    } // end for
  } // end else |slope| > 1
}

//������
void LCD_box(u16 x, u16 y, u16 w, u16 h, u16 bc)
{
  LCD_DrawLine(x, y, x + w, y, 0xEF7D);
  LCD_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0x2965);
  LCD_DrawLine(x, y + h, x + w, y + h, 0x2965);
  LCD_DrawLine(x, y, x, y + h, 0xEF7D);
  LCD_DrawLine(x + 1, y + 1, x + 1 + w - 2, y + 1 + h - 2, bc);
}

//������
void LCD_box2(u16 x, u16 y, u16 w, u16 h, u8 mode)
{
  if (mode == 0)
  {
    LCD_DrawLine(x, y, x + w, y, 0xEF7D);
    LCD_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0x2965);
    LCD_DrawLine(x, y + h, x + w, y + h, 0x2965);
    LCD_DrawLine(x, y, x, y + h, 0xEF7D);
  }
  if (mode == 1)
  {
    LCD_DrawLine(x, y, x + w, y, 0x2965);
    LCD_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0xEF7D);
    LCD_DrawLine(x, y + h, x + w, y + h, 0xEF7D);
    LCD_DrawLine(x, y, x, y + h, 0x2965);
  }
  if (mode == 2)
  {
    LCD_DrawLine(x, y, x + w, y, 0xffff);
    LCD_DrawLine(x + w - 1, y + 1, x + w - 1, y + 1 + h, 0xffff);
    LCD_DrawLine(x, y + h, x + w, y + h, 0xffff);
    LCD_DrawLine(x, y, x, y + h, 0xffff);
  }
}

/**************************************************************************************
��������: ����Ļ��ʾһ͹��İ�ť��
��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
��    ��: ��
**************************************************************************************/
void DisplayButtonDown(u16 x1, u16 y1, u16 x2, u16 y2)
{
  LCD_DrawLine(x1,  y1,  x2, y1, GRAY2); //H
  LCD_DrawLine(x1 + 1, y1 + 1, x2, y1 + 1, GRAY1); //H
  LCD_DrawLine(x1,  y1,  x1, y2, GRAY2); //V
  LCD_DrawLine(x1 + 1, y1 + 1, x1 + 1, y2, GRAY1); //V
  LCD_DrawLine(x1,  y2,  x2, y2, WHITE); //H
  LCD_DrawLine(x2,  y1,  x2, y2, WHITE); //V
}

/**************************************************************************************
��������: ����Ļ��ʾһ���µİ�ť��
��    ��: u16 x1,y1,x2,y2 ��ť�����ϽǺ����½�����
��    ��: ��
**************************************************************************************/
void DisplayButtonUp(u16 x1, u16 y1, u16 x2, u16 y2)
{
  LCD_DrawLine(x1,  y1,  x2, y1, WHITE); //H
  LCD_DrawLine(x1,  y1,  x1, y2, WHITE); //V

  LCD_DrawLine(x1 + 1, y2 - 1, x2, y2 - 1, GRAY1); //H
  LCD_DrawLine(x1,  y2,  x2, y2, GRAY2); //H
  LCD_DrawLine(x2 - 1, y1 + 1, x2 - 1, y2, GRAY1); //V
  LCD_DrawLine(x2, y1, x2, y2, GRAY2);  //V
}

//��ʾ16*16��Ӣ����ģ
//x:������
//y:������
//fc:������ɫ
//bc:������ɫ
//*s:Ҫ��ʾ����
void LCD_DrawFont_GBK16(u16 x, u16 y, u16 fc, u16 bc, u8 *s)
{
  unsigned char i, j;
  unsigned short k, x0;
  x0 = x;

  while(*s)//��Ӧ�ַ��ǿ�
  {
    if((*s) < 128)
    {
      k = *s;
      if (k == 13)
      {
        x = x0;
        y += 16;
      }
      else
      {
        if (k > 32) k -= 32;
        else k = 0;

        for(i = 0; i < 16; i++)
          for(j = 0; j < 8; j++)
          {
            if(asc16[k * 16 + i] & (0x80 >> j))	LCD_DrawPoint(x + j, y + i, fc);
            else
            {
              if (fc != bc) LCD_DrawPoint(x + j, y + i, bc);
            }
          }
        x += 8;
      }
      s++;
    }

    else
    {


      for (k = 0; k < hz16_num; k++)//�����ֱ�
      {
        if ((hz16[k].Index[0] == *(s)) && (hz16[k].Index[1] == *(s + 1)))//�ж��Ƿ���������Ӧ����
        {
          for(i = 0; i < 16; i++)
          {
            for(j = 0; j < 8; j++)
            {
              if(hz16[k].Msk[i * 2] & (0x80 >> j))	LCD_DrawPoint(x + j, y + i, fc);
              else
              {
                if (fc != bc) LCD_DrawPoint(x + j, y + i, bc);
              }
            }
            for(j = 0; j < 8; j++)
            {
              if(hz16[k].Msk[i * 2 + 1] & (0x80 >> j))	LCD_DrawPoint(x + j + 8, y + i, fc);
              else
              {
                if (fc != bc) LCD_DrawPoint(x + j + 8, y + i, bc);
              }
            }
          }
        }
      }
      s += 2;//����ռ���ַ�
      x += 16;
    }

  }
}


//ȡģ��ʽ ˮƽɨ�� ������ ��λ��ǰ
//��ʾͼƬ
//x:��ʼ������
//y:��ʼ������
//x1:ͼƬ���
//y1:ͼƬ�߶�

//*p:ͼƬ����
void LCD_Showimage(u16 x0, u16 y0, u16 x1, u16 y1, const unsigned char *p) //��ʾ128*128 ͼƬ
{
  int i;
  unsigned char picH, picL;

  LCD_SetRegion(x0, y0, x0 + x1 - 1, y0 + y1 - 1);		//��������:ɨ����㵽�յ�0��127���պ�128����
  for(i = 0; i < x1 * y1; i++)
  {
    picL = *(p + i * 2);	//���ݵ�λ��ǰ
    picH = *(p + i * 2 + 1);
    LCD_WriteData_16Bit(picH << 8 | picL);
  }

}

