#ifndef __DS1302_H__
#define __DS1302_H__

#include "sys.h"

/*------------引脚---------------------      */
#define RST GPIO_Pin_12
#define ZDA GPIO_Pin_11
#define SCK GPIO_Pin_9

#define Output 1
#define Input !Output
//复位脚
#define RST_CLR 	GPIO_ResetBits(GPIOA,RST)//电平置低
#define RST_SET 	GPIO_SetBits(GPIOA,RST)//电平置高

//双向数据
#define IO_CLR	GPIO_ResetBits(GPIOA,ZDA)//电平置低
#define IO_SET	GPIO_SetBits(GPIOA,ZDA)//电平置高
#define IO_R	GPIO_ReadInputDataBit(GPIOA,ZDA)  //电平读取


//时钟信号
#define SCK_CLR	 GPIO_ResetBits(GPIOC,SCK)//时钟信号
#define SCK_SET	 GPIO_SetBits(GPIOC,SCK)//电平置高


#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add			0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add		0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

#define ds1302_sec_readd			0x81		//秒数据地址
#define ds1302_min_readd			0x83		//分数据地址
#define ds1302_hr_readd			    0x85		//时数据地址
#define ds1302_date_readd			0x87		//日数据地址
#define ds1302_month_readd	     	0x89		//月数据地址
#define ds1302_day_readd			0x8b		//星期数据地址
#define ds1302_year_readd			0x8d		//年数据地址

//extern unsigned char time_buf1[8];//空年月日时分秒周
//extern unsigned char time_buf[8] ;//空年月日时分秒周

/*------------------------------------------------
           向DS1302写入一字节数据
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d);
/*------------------------------------------------
           从DS1302读出一字节数据
------------------------------------------------*/
unsigned char Ds1302_Read_Byte(unsigned char addr) ;
/*------------------------------------------------
           向DS1302写入时钟数据
------------------------------------------------*/
void Ds1302_Write_Time(void) ;
/*------------------------------------------------
           从DS1302读出时钟数据
------------------------------------------------*/
void Ds1302_Read_Time(void)  ;
/*------------------------------------------------
                DS1302初始化
------------------------------------------------*/
void Ds1302_Init(void);
/*-----------------------------------------------*/
void Ds1302_DPinInit(u8 State);

/*----------------------------------------------*/
void Time_changer(u8 *out_time);
                //调时间处理
/*----------------------------------------------*/
void Set_time(unsigned char  bb);			 
void display(void);
void Recordtime(u16 i);  //记录时间函数
//void writeclock(void);

#endif

