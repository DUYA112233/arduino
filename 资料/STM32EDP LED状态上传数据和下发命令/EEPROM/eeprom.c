#include "eeprom.h"
#include "delay.h"

//2015-6-2 16:51:29
//by @creep

//设置EEPROM的大小为1K
//可根据实际调整大小
u16 STMFLASH_BUFF[STMFLASH_SIZE];             //数组大小为1024bit
//要写数据的起始地址为0-STMFLASH_SIZE,类型为HalfWord类型
//只能写数据类型为HalfWord的数据到EEPROM 里面
void STMFLASH_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)   //写数据 变量形式:地址 数据数组 数组长度
{
	u16 j;
	STMFLASH_Read_Backup();															//读出备份区域的数据
	FLASH_Unlock();                    								 //解锁
	FLASH_ErasePage(FLASH_PAGE255_ADDR); 							//擦除第255页   
	for(j=0;j<NumToWrite;j++)
	{
		STMFLASH_BUFF[j+WriteAddr] = *(pBuffer+j);			//将数据写到数组中去
	}	
	STMFLASH_Write_NoErase();													//将数据写回到第255页中
	FLASH_Lock();																			//上锁	
}
//读取数据为字节类型
//将EEEPROM的1K字节读出来
void STMFLASH_Read_Backup(void)                    //读数据函数 
{
	u16  t;
	for(t=0;t<STMFLASH_SIZE;t++) 
	{
		*(STMFLASH_BUFF+t) = *(u16*)(FLASH_PAGE255_ADDR+t*2);		
	}	
}
//将EEPROM的1K的数组写回到 第255页
//写数据前不擦除
void STMFLASH_Write_NoErase(void)
{
	u16 t;
	for(t=0;t<STMFLASH_SIZE;t++)
	{		
		FLASH_ProgramHalfWord(FLASH_PAGE255_ADDR+t*2,*(STMFLASH_BUFF+t));
	}	
}
//从eeprom中读数据
void STMFLASH_Read(u16 ReadAddr,u8 *pstr,u16 NumberToRead)
{
	u16 t;
	for(t=0;t<NumberToRead;t++)
	{
		*(pstr+t) = *(u16*)(FLASH_PAGE255_ADDR+ReadAddr+t*2);	
	}
}




















