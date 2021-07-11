/*
 * LCD.h
 *
 *  Created on: Dec 25, 2020
 *      Author: Al Badr
 */
#define ClearDisplay     0x01

#ifndef LCD_H_
#define LCD_H_
#define ClearDisplay     0x01
#define ReturnHome       0x02
#define EntryModeSet     0x04
#define DisplayOn_OFF    0x0F
#define cursor_shift     0x0A
#define function_set     0x30
#define lcd_DisplayOn    0x0C
#define lcd_FunctionSet8bit 0x38
#define lcd_SetCursor       0x80

#define Enable_Channel         PORTB0
#define RS                     PORTB1
#define ReadWrite              PORTB2


extern void LCD_writeCommand(uint8 cmd);
extern void LCD_Init(void);

extern void LCD_WriteData(uint8 ASCII);
extern void LCD_writestring (uint8 *ptr);

//extern void Gotoxy(uint8 row, uint8 pos);
extern void  LCD_GotoXY(uint8 row,uint8 coloum);


void LCD_WriteCharctr (uint8 Data);

extern void LCD_ExtraChar (uint8 Y,uint8 X);

//extern void LCD_Int_to_num(uint32 num);
extern void LCD_WriteNumber(sint64 num);

extern void LCD_Clear(void);


#endif /* LCD_H_ */
