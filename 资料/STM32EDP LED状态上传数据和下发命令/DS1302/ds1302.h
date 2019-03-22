#ifndef __DS1302_H__
#define __DS1302_H__

#include "sys.h"

/*------------����---------------------      */
#define RST GPIO_Pin_12
#define ZDA GPIO_Pin_11
#define SCK GPIO_Pin_9

#define Output 1
#define Input !Output
//��λ��
#define RST_CLR 	GPIO_ResetBits(GPIOA,RST)//��ƽ�õ�
#define RST_SET 	GPIO_SetBits(GPIOA,RST)//��ƽ�ø�

//˫������
#define IO_CLR	GPIO_ResetBits(GPIOA,ZDA)//��ƽ�õ�
#define IO_SET	GPIO_SetBits(GPIOA,ZDA)//��ƽ�ø�
#define IO_R	GPIO_ReadInputDataBit(GPIOA,ZDA)  //��ƽ��ȡ


//ʱ���ź�
#define SCK_CLR	 GPIO_ResetBits(GPIOC,SCK)//ʱ���ź�
#define SCK_SET	 GPIO_SetBits(GPIOC,SCK)//��ƽ�ø�


#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add			0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add		0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

#define ds1302_sec_readd			0x81		//�����ݵ�ַ
#define ds1302_min_readd			0x83		//�����ݵ�ַ
#define ds1302_hr_readd			    0x85		//ʱ���ݵ�ַ
#define ds1302_date_readd			0x87		//�����ݵ�ַ
#define ds1302_month_readd	     	0x89		//�����ݵ�ַ
#define ds1302_day_readd			0x8b		//�������ݵ�ַ
#define ds1302_year_readd			0x8d		//�����ݵ�ַ

//extern unsigned char time_buf1[8];//��������ʱ������
//extern unsigned char time_buf[8] ;//��������ʱ������

/*------------------------------------------------
           ��DS1302д��һ�ֽ�����
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d);
/*------------------------------------------------
           ��DS1302����һ�ֽ�����
------------------------------------------------*/
unsigned char Ds1302_Read_Byte(unsigned char addr) ;
/*------------------------------------------------
           ��DS1302д��ʱ������
------------------------------------------------*/
void Ds1302_Write_Time(void) ;
/*------------------------------------------------
           ��DS1302����ʱ������
------------------------------------------------*/
void Ds1302_Read_Time(void)  ;
/*------------------------------------------------
                DS1302��ʼ��
------------------------------------------------*/
void Ds1302_Init(void);
/*-----------------------------------------------*/
void Ds1302_DPinInit(u8 State);

/*----------------------------------------------*/
void Time_changer(u8 *out_time);
                //��ʱ�䴦��
/*----------------------------------------------*/
void Set_time(unsigned char  bb);			 
void display(void);
void Recordtime(u16 i);  //��¼ʱ�亯��
//void writeclock(void);

#endif

