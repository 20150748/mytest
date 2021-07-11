/*
 * LCD.c
 *
 *  Created on: Dec 25, 2020
 *      Author: Al Badr
 */

#include <util/delay.h>
#define F_CPU 8000000

#include "STD_Types.h"
#include "DIO.h"
#include "DIO_config.h"
#include "LCD_config.h"
#include "LCD.h"

extern const uint8  ExtraChar[];

void LCD_Init(void)
{
	//_delay_ms(30);
	LCD_writeCommand(ReturnHome);
	_delay_ms(30);
	LCD_writeCommand(lcd_FunctionSet8bit);
	_delay_us(39);
	LCD_writeCommand(lcd_DisplayOn);
	_delay_us(39);
	LCD_writeCommand(ClearDisplay);
	_delay_ms(1.53);
}
void LCD_writeCommand(uint8 cmd)
{
	DIO_WriteChannel(Enable_Channel,1);
	DIO_WriteChannel(RS,0);
	DIO_WriteChannel(ReadWrite,0);
	DIO_WritePort(PORT_A,cmd);
	DIO_WriteChannel(Enable_Channel,0);
	_delay_ms(1);
	DIO_WriteChannel(Enable_Channel,1);

}

void LCD_WriteData(uint8 ASCII)
{
	DIO_WriteChannel(Enable_Channel,1);
	DIO_WriteChannel(RS,1);
	DIO_WriteChannel(ReadWrite,0);
	DIO_WritePort(PORT_A,ASCII);
	DIO_WriteChannel(Enable_Channel,0);
	_delay_ms(2);
	DIO_WriteChannel(Enable_Channel,1);
}


void LCD_writestring (uint8 *ptr)
{
	while (*ptr != '\0')
	{
		LCD_WriteData(*ptr);
		ptr++;

	}
}

//void Gotoxy (uint8 Y,uint8 X)
//{
//	if (X>0 && X<=16)
//	{
//		switch(Y)
//		{
//		case 1:LCD_writeCommand(X + 127);break; // x=col, 0x80=127
//
//		case 2:	LCD_writeCommand(X + 191); break; // 191=0xc0
//
//		default: break;
//
//		}
//	}
//}
void  LCD_GotoXY(uint8 row,uint8 coloum)
{
					if (row == 0)

					{
						LCD_writeCommand(0x80 + coloum);
					}

					if (row == 1)

					{
						LCD_writeCommand(0xC0 + coloum);
					}
}


void LCD_ExtraChar (uint8 Y,uint8 X)
{
	uint8 i,j;


	LCD_writeCommand(64); // 0x40
	for(i=0 ; i<64 ; i++)
	{
		//x = ExtraChar[i];
		LCD_WriteData(ExtraChar[i]);
	}

	LCD_writeCommand(128);
	LCD_GotoXY(Y,X);
	//LCD_WriteData('9');

	for (j=0; j<=7 ; j++) // row =j as 8 row
	{
		LCD_WriteData(j);

		_delay_ms(5);
	}

}
//void LCD_Int_to_num(uint32 num)
//{
//
//	char str[10];
//	itoa(num, str,10);
//	//	Gotoxy(row,col);
//	LCD_writestring(str);
//
//}
void LCD_WriteNumber(sint64 num)
{
    uint8 str[16];
    uint8 i=0;
    uint8 j=0;
    uint8 temp;

	if(num==0)
		LCD_WriteData('0');
	else
	{
		if(num<0)
		{
			num*=-1;
			LCD_WriteData('-');
		}
		 while(num)
		 {
			 str[i]=(num%10)+'0';
			 num=num/10;
			 i++;
		 }
		 str[i]='\0';
		 i--;
		 while(j<i)
		 {
			 temp=str[i];
			 str[i]=str[j];
			 str[j]=temp;
			 j++;
			 i--;
		 }

		 LCD_writestring(str);
	}
}

void LCD_Clear(void)
{
	LCD_writeCommand(0x01);		/* Clear display */
	_delay_ms(2);
	LCD_writeCommand(0x80);		/* Cursor at home position */
}


