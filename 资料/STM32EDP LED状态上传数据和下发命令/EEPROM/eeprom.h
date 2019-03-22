#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x.h"
#include "usart.h"
//����EEPROM��ģ����ʼ��ַΪFLASH�ĵ�255ҳ����ʼ��ַ
#define FLASH_PAGE255_ADDR  0x0807F800
//���ڱ�������Ĵ�СΪ50���ֽ�
//���Ը�����Ҫ����
#define STMFLASH_SIZE			1024

#define USER_SECTOR   (253)     //�����ķ�Χ0~255��K60���ڴ��СΪ512k,һ������Ϊ2k���������Ϊ255
#define USER_ADDR     0x08000000+(USER_SECTOR*1024)// FLASH_TEST_SECTOR*(2048)

void Flash_write(u32 StartAddr, u32 *DataSrcPtr, u16 DateSize);
void Flash_read(u32 ReadAddr ,u32 *Read_Buff, u16 Date_Size);
void Flash_Test(void);

//void STMFLASH_Read_Backup(void);
//void STMFLASH_Write_NoErase(void);
//void STMFLASH_Read(u16 ReadAddr,u8 *pstr,u16 NumberToRead);
//void STMFLASH_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);			   
#endif

















