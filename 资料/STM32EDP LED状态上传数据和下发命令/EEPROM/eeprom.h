#ifndef __STMFLASH_H__
#define __STMFLASH_H__
#include "stm32f10x.h"
#include "usart.h"
//定义EEPROM的模拟起始地址为FLASH的第255页的起始地址
#define FLASH_PAGE255_ADDR  0x0807F800
//定于备份区域的大小为50个字节
//可以根据需要调整
#define STMFLASH_SIZE			1024

#define USER_SECTOR   (253)     //扇区的范围0~255。K60的内存大小为512k,一个扇区为2k，所以最大为255
#define USER_ADDR     0x08000000+(USER_SECTOR*1024)// FLASH_TEST_SECTOR*(2048)

void Flash_write(u32 StartAddr, u32 *DataSrcPtr, u16 DateSize);
void Flash_read(u32 ReadAddr ,u32 *Read_Buff, u16 Date_Size);
void Flash_Test(void);

//void STMFLASH_Read_Backup(void);
//void STMFLASH_Write_NoErase(void);
//void STMFLASH_Read(u16 ReadAddr,u8 *pstr,u16 NumberToRead);
//void STMFLASH_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);			   
#endif

















