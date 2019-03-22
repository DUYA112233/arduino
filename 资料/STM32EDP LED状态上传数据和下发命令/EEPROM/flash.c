#include "EEPROM.H"
#include "stdio.h"
//��������
#define     DATA_SIZE 3

//#define USER_SECTOR   (254)     //�����ķ�Χ0~255��K60���ڴ��СΪ512k,һ������Ϊ2k���������Ϊ255
//#define USER_ADDR     0x08000000+(USER_SECTOR*1024)// FLASH_TEST_SECTOR*(2048)


s32 Read_buffer[DATA_SIZE]={0x11223344,0x55667788};  //�����������
s32 Write_buffer[DATA_SIZE]={0x11223344,0x55667788}; //����д������

/*======����ָ��������������ֻ����һ���飬��λֻ��Ϊ����====================================================*/

/*==========================================================*/
void Flash_write(u32 StartAddr, u32 *DataSrcPtr, u16 DateSize)// DateSize<=255
{    
    FLASH_Status  FLASHStatus;
	 unsigned int len=0;

//    RCC_HSICmd(ENABLE);

	FLASH_Unlock();
	/* ���һЩ��־λ */
	FLASH_ClearFlag(FLASH_FLAG_BSY |FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	
    
    FLASHStatus = FLASH_ErasePage(StartAddr);
 
    if(FLASHStatus == FLASH_COMPLETE)
    {
        for(len=0;len<DateSize;len++)
        {
            /* ������ʼ��ַΪ 0x8002000 �� FLASH ҳ */
            FLASHStatus = FLASH_ProgramWord(StartAddr+len, DataSrcPtr[len]);    
        }

    }
	/* ���� FLASH ���ƿ�*/
	FLASH_Lock();
    
    if(FLASHStatus==FLASH_COMPLETE)
    {
        printf("д��ɹ���\r\n");
    }
    else
    {
        printf("д��ʧ�ܣ��������:%x��\r\n", FLASHStatus);
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
            Flash_read(USER_ADDR,(u32 *)Write_buffer,DATA_SIZE);//�ȶ���������
        
                
//            printf("\r\nд������Ϊ \r\n");
            for(u8 i=0;i<DATA_SIZE;i++);
//                printf("%x ",Write_buffer[i]);
            
            
            Flash_write(USER_ADDR,(u32 *)Write_buffer,DATA_SIZE);//ͨ���޸ĺ���д��ȥ
            
            
        break;
        
        case 'R':
            Flash_read(USER_ADDR,(u32 *)Read_buffer,DATA_SIZE);
        
//            printf("\r\n��������Ϊ \r\n");
            for(u8 i=0;i<DATA_SIZE;i++);
//                printf("%x ",Read_buffer[i]);        
    
            
            
            break;
    default:break;
    }
  
}






///*=====����Flash��=====================================================*/
void Flash_Test(void)
{
  
//    printf("-------FLASH����д���������-------\r\n");
//    printf("д������Ϊ :%d \r\n",USER_SECTOR);
//    printf("д���ַΪ :0x%x \r\n",USER_ADDR);
//    printf("д�����ݴ�СΪ :%d \r\n",DATA_SIZE);
    
    Param_Flash_WR('W');

    Param_Flash_WR('R');
   
}







