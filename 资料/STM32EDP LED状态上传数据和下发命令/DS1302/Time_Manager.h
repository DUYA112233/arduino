#ifndef __TIME_MANAGER_H_

#include "pbdata.h"

void Show_Time(u16 x,u16 y,u8 En);
void LCD_TimeSecond(u16 x0,u16 y0,u8 r,u8 i);
void LCD_TimeMinute(u16 x0,u16 y0,u8 r,u8 i);
void LCD_TimeHour(u16 x0,u16 y0,u8 r,u8 i,u8 m);

void My_TimeSet(void);

#endif