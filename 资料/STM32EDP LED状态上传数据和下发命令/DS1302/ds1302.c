#include "stm32f10x.h"
#include "ds1302.h"
#include "delay.h"
#include "lcd.h"
#include "EEPROM.H"
unsigned char time_buf1[8]={0x20,0X11,0X03,0X18,0X01,0X19,0X28,0X05};//��������ʱ������   2017��3��17��22ʱ44��55������5
unsigned char time_buf[8] ;                         //��������ʱ������
unsigned char time_buf2[8] ;  

void Set_time(unsigned char  bb)			 //��ʱ�䴦��
{
	switch(bb)
	{
        
		case 1:time_buf1[1]++;if(time_buf1[1]>99)   time_buf1[1]=0;    
              Ds1302_Write_Time();break; //����ʱ�� �� ��1
		case 2:time_buf1[1]--;if(time_buf1[1]<=0)   time_buf1[1]=99;    
              Ds1302_Write_Time();break; //����ʱ�� �� ��1
		case 3:time_buf1[2]++;if(time_buf1[2]>12)   time_buf1[2]=1;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1
		case 4:time_buf1[2]--;if(time_buf1[2]<=0)   time_buf1[2]=12;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1  

		case 5:time_buf1[3]++;if(time_buf1[3]>=31)   time_buf1[3]=1;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1
		case 6:time_buf1[3]--;if(time_buf1[3]<=0)   time_buf1[3]=31;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1         
        
		case 7:time_buf1[4]++;if(time_buf1[4]>=24)   time_buf1[4]=0;    
              Ds1302_Write_Time();break; //����ʱ�� Сʱ ��1
		case 8:time_buf1[4]--;if(time_buf1[4]<=0)   time_buf1[4]=23;    
              Ds1302_Write_Time();break; //����ʱ�� Сʱ ��1
		case 9:time_buf1[5]++;if(time_buf1[5]>=60)   time_buf1[5]=0;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1
		case 10:time_buf1[5]--;if(time_buf1[5]<=0)   time_buf1[5]=59;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1

		case 11:time_buf1[7]++;if(time_buf1[7]>7)   time_buf1[7]=1;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1
		case 12:time_buf1[7]--;if(time_buf1[7]<=0)   time_buf1[7]=7;    
              Ds1302_Write_Time();break; //����ʱ�� ��   ��1         
        default :break;
	}
}

//��ds1302������ʮ�������ݽ��� ��λʮλ���룬�浽TempData[]��
void Time_changer(u8 *out_time)						
{
        Ds1302_Read_Time();        
        out_time[1]=time_buf1[1];	//��	
        out_time[2]=time_buf1[2];   //��
        out_time[3]=time_buf1[3];   //��
        out_time[4]=time_buf1[4];   //ʱ
        out_time[5]=time_buf1[5];   //��
        out_time[6]=time_buf1[6];	//��
        out_time[7]=time_buf1[7];   //��
}


/*------------------------------------------------
           ��DS1302д��һ�ֽ�����
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d)
{
	unsigned char i;
    Ds1302_DPinInit(Output);//���ݿ�����Ϊ���
	RST_CLR;
	delay_us(2);
	SCK_CLR;
	delay_us(2);
	RST_SET;	
	delay_us(2);
	//д��Ŀ���ַ��addr
	addr = addr & 0xFE;     //���λ����
	for (i = 0; i < 8; i ++) 
	    { 
		if (addr & 0x01) 
		    {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		delay_us(2);
		SCK_CLR;
		addr = addr >> 1;
		}
	
	//д�����ݣ�d
	for (i = 0; i < 8; i ++) 
	   {
		if (d & 0x01) 
		    {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
        delay_us(2);
        SCK_CLR;
		d = d >> 1;
		}
	RST_CLR;					//ֹͣDS1302����
}
/*------------------------------------------------
           ��DS1302����һ�ֽ�����
------------------------------------------------*/

unsigned char Ds1302_Read_Byte(unsigned char addr) 
{

	unsigned char i;
	unsigned char temp=0;
    
	RST_CLR;
	delay_us(2);
	SCK_CLR;
	delay_us(2);			
	RST_SET;	
	delay_us(2);                 		 
	                  //д��Ŀ���ַ��addr
	addr = addr | 0x01;//���λ�ø�
    Ds1302_DPinInit(Output);//���ݿ�����Ϊ����
	for (i = 0; i < 8; i ++) 
	    {
	     
		if (addr & 0x01) 
		   {
			IO_SET;
			}
		else 
		    {
			IO_CLR;
			}
		SCK_SET;
		delay_us(2);
		SCK_CLR;
		addr = addr >> 1;
		}
	
	//������ݣ�temp
    Ds1302_DPinInit(Input);//���ݿ�����Ϊ����        
	for (i = 0; i < 8; i ++) 
	    {
		temp = temp >> 1;
		if (IO_R) 
		   {
			temp |= 0x80;
			}
		else 
		   {
			temp &= 0x7F;
			}
		SCK_SET;
		delay_us(2);
		SCK_CLR;
		}
	
	RST_CLR;	//ֹͣDS1302����

	return temp;
}

/*------------------------------------------------
           ��DS1302д��ʱ������
------------------------------------------------*/
void Ds1302_Write_Time(void) 
{
	unsigned char i,tmp=0;
	for(i=0;i<8;i++)
	{                  //BCD����
		tmp=time_buf1[i]/10;
		time_buf[i]=time_buf1[i]%10;
		time_buf[i]=time_buf[i]+tmp*16;
	}
	Ds1302_Write_Byte(ds1302_control_add,0x00);			//�ر�д���� 
	Ds1302_Write_Byte(ds1302_charger_add,0xa9);			//������ 		

	Ds1302_Write_Byte(ds1302_year_add,time_buf[1]);		//�� 
	Ds1302_Write_Byte(ds1302_month_add,time_buf[2]);	//�� 
	Ds1302_Write_Byte(ds1302_date_add,time_buf[3]);		//�� 
	Ds1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//�� 
	Ds1302_Write_Byte(ds1302_min_add,time_buf[5]);		//��
	Ds1302_Write_Byte(ds1302_hr_add,time_buf[4]);		//ʱ 
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//�� 
   
	Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д���� 
}

/*------------------------------------------------
           ��DS1302����ʱ������
------------------------------------------------*/
void Ds1302_Read_Time(void)  
{ 
	unsigned char i,tmp=0;   
    
	time_buf[1]=Ds1302_Read_Byte(ds1302_year_readd);		//�� 
	Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����   
    
	time_buf[2]=Ds1302_Read_Byte(ds1302_month_readd);		//�� 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����   
    
	time_buf[3]=Ds1302_Read_Byte(ds1302_date_readd);		//�� 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����   
    
	time_buf[4]=Ds1302_Read_Byte(ds1302_hr_readd);		//ʱ 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����   
    
	time_buf[5]=Ds1302_Read_Byte(ds1302_min_readd);		//�� 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����   
    
	time_buf[6]=(Ds1302_Read_Byte(ds1302_sec_readd));//�� 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����   
    
	time_buf[7]=Ds1302_Read_Byte(ds1302_day_readd);		//��     
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//��д����   
	
	for(i=0;i<8;i++)
	   {           //BCD����
		tmp=time_buf[i]/16;
		time_buf1[i]=time_buf[i]%16;
		time_buf1[i]=time_buf1[i]+tmp*10;
	   }
}

/*------------------------------------------------
                DS1302��ʼ��
------------------------------------------------*/
void Ds1302_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  //  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //��Ϊ�õ���Jtag�Ľӿڣ�����Ҫ�ض���
 //   AFIO->MAPR|=GPIO_Remap_SWJ_JTAGDisable;/*!< JTAG-DP Disabled and SW-DP Enabled */
    
    /*ʹ��GPIOB,���ù���ʱ��*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = SCK;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
	
	  GPIO_InitStructure.GPIO_Pin = RST;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    Ds1302_DPinInit(Output);
    
	RST_CLR;			//RST���õ�
	SCK_CLR;			//SCK���õ�

	
//    Ds1302_Write_Time();
    Ds1302_Write_Byte(ds1302_sec_add,0x00);	  //�������
		Ds1302_Write_Byte(ds1302_hr_add ,0x00);	  //�������
	//	writeclock();
}

void Ds1302_DPinInit(u8 State)
{
    GPIO_InitTypeDef GPIO_InitStructure;    
    if(State==Output)
    {
        /*����Ϊ ��� Out  */
        GPIO_InitStructure.GPIO_Pin = ZDA;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;  //��������
        GPIO_Init(GPIOA, &GPIO_InitStructure); 	
    }
    else
    {
        GPIO_InitStructure.GPIO_Pin = ZDA;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //��������
        GPIO_Init(GPIOA, &GPIO_InitStructure); 
    
    }
}

void display(void)
{
// Time_changer(time_buf);
// LCD_ShowNum(130,130,time_buf1[1],1,16);  //��
 //LCD_ShowNum(138,130,time_buf1[2],1,16);  //��
 //LCD_ShowChar(146,130,'-',16,0);          
// LCD_ShowNum(154,130,time_buf1[3],1,16);  //��
POINT_COLOR=0xFFFF;	//������ɫ
BACK_COLOR=0x0000;  //����ɫ 

 LCD_ShowNum(165,0,time_buf1[4],2,16);  //ʱ
	LCD_ShowChar(181,0,':',16,0);          
 LCD_ShowNum(189,0,time_buf1[5],2,16);//��
	LCD_ShowChar(207,0,':',16,0); 	
 LCD_ShowNum(215,0,time_buf1[6],2,16);//��
 LCD_ShowNum(37,0,time_buf1[7],2,16);//��
// delay_ms(1000);
	
}
/******************дʱ���ƶ�12/24***************************/
/*void writeclock()
{
  Ds1302_DPinInit(Output);
	RST_CLR;
	SCK_CLR;
	RST_SET;
	delay_us(20);
	Ds1302_Write_Byte(0X84,0X00);	
	
	RST_CLR;
 


}*/
void Recordtime(u16 i)
{
  Ds1302_Read_Time();   //��ȡ��ʱ��ʱ��
	Flash_write(USER_ADDR+(i*4)+1,(u32 *)time_buf1, 7);
}
