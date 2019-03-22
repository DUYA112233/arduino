#include "EEPROM.H"
#include "stdio.h"
//变量定义
#define     DATA_SIZE 3

//#define USER_SECTOR   (254)     //扇区的范围0~255。K60的内存大小为512k,一个扇区为2k，所以最大为255
//#define USER_ADDR     0x08000000+(USER_SECTOR*1024)// FLASH_TEST_SECTOR*(2048)


s32 Read_buffer[DATA_SIZE]={0x11223344,0x55667788};  //定义读缓冲区
s32 Write_buffer[DATA_SIZE]={0x11223344,0x55667788}; //定义写缓冲区

/*======擦除指定的扇区，不能只擦除一个块，单位只能为扇区====================================================*/

/*==========================================================*/
void Flash_write(u32 StartAddr, u32 *DataSrcPtr, u16 DateSize)// DateSize<=255
{    
    FLASH_Status  FLASHStatus;
	 unsigned int len=0;

//    RCC_HSICmd(ENABLE);

	FLASH_Unlock();
	/* 清除一些标志位 */
	FLASH_ClearFlag(FLASH_FLAG_BSY |FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	
    
    FLASHStatus = FLASH_ErasePage(StartAddr);
 
    if(FLASHStatus == FLASH_COMPLETE)
    {
        for(len=0;len<DateSize;len++)
        {
            /* 擦除起始地址为 0x8002000 的 FLASH 页 */
            FLASHStatus = FLASH_ProgramWord(StartAddr+len, DataSrcPtr[len]);    
        }

    }
	/* 锁定 FLASH 控制块*/
	FLASH_Lock();
    
    if(FLASHStatus==FLASH_COMPLETE)
    {
        printf("写入成功。\r\n");
    }
    else
    {
        printf("写入失败，错误代码:%x。\r\n", FLASHStatus);
    }
}
/*==========================================================*/
void Flash_read(u32 ReadAddr ,u32 *Read_Buff, u16 Date_Size)
{
    u16 len=0;
    u32 *ptr;
    ptr = (u32*)ReadAddr;

    while(len < Date_Size )
    {
        Read_Buff[len] = *(ptr + len);
        len+=1;
    }
}


//void Write_ID_and_Name()
//{
//	
//	
//	
//	Flash_write();


//}
void Param_Flash_WR(char wr)
{
    switch(wr)
    {
        case 'W':
            Flash_read(USER_ADDR,(u32 *)Write_buffer,DATA_SIZE);//先读出来数据
        
                
//            printf("\r\n写入内容为 \r\n");
            for(u8 i=0;i<DATA_SIZE;i++);
//                printf("%x ",Write_buffer[i]);
            
            
            Flash_write(USER_ADDR,(u32 *)Write_buffer,DATA_SIZE);//通过修改后再写进去
            
            
        break;
        
        case 'R':
            Flash_read(USER_ADDR,(u32 *)Read_buffer,DATA_SIZE);
        
//            printf("\r\n读出内容为 \r\n");
            for(u8 i=0;i<DATA_SIZE;i++);
//                printf("%x ",Read_buffer[i]);        
    
            
            
            break;
    default:break;
    }
  
}






///*=====测试Flash用=====================================================*/
void Flash_Test(void)
{
  
//    printf("-------FLASH擦除写入测试例程-------\r\n");
//    printf("写入扇区为 :%d \r\n",USER_SECTOR);
//    printf("写入地址为 :0x%x \r\n",USER_ADDR);
//    printf("写入数据大小为 :%d \r\n",DATA_SIZE);
    
    Param_Flash_WR('W');

    Param_Flash_WR('R');
   
}







