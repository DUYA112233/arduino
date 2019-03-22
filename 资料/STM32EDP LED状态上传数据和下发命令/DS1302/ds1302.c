#include "stm32f10x.h"
#include "ds1302.h"
#include "delay.h"
#include "lcd.h"
#include "EEPROM.H"
unsigned char time_buf1[8]={0x20,0X11,0X03,0X18,0X01,0X19,0X28,0X05};//空年月日时分秒周   2017年3月17日22时44分55秒星期5
unsigned char time_buf[8] ;                         //空年月日时分秒周
unsigned char time_buf2[8] ;  

void Set_time(unsigned char  bb)			 //调时间处理
{
	switch(bb)
	{
        
		case 1:time_buf1[1]++;if(time_buf1[1]>99)   time_buf1[1]=0;    
              Ds1302_Write_Time();break; //正常时间 年 加1
		case 2:time_buf1[1]--;if(time_buf1[1]<=0)   time_buf1[1]=99;    
              Ds1302_Write_Time();break; //正常时间 年 减1
		case 3:time_buf1[2]++;if(time_buf1[2]>12)   time_buf1[2]=1;    
              Ds1302_Write_Time();break; //正常时间 月   加1
		case 4:time_buf1[2]--;if(time_buf1[2]<=0)   time_buf1[2]=12;    
              Ds1302_Write_Time();break; //正常时间 月   减1  

		case 5:time_buf1[3]++;if(time_buf1[3]>=31)   time_buf1[3]=1;    
              Ds1302_Write_Time();break; //正常时间 日   加1
		case 6:time_buf1[3]--;if(time_buf1[3]<=0)   time_buf1[3]=31;    
              Ds1302_Write_Time();break; //正常时间 日   减1         
        
		case 7:time_buf1[4]++;if(time_buf1[4]>=24)   time_buf1[4]=0;    
              Ds1302_Write_Time();break; //正常时间 小时 加1
		case 8:time_buf1[4]--;if(time_buf1[4]<=0)   time_buf1[4]=23;    
              Ds1302_Write_Time();break; //正常时间 小时 减1
		case 9:time_buf1[5]++;if(time_buf1[5]>=60)   time_buf1[5]=0;    
              Ds1302_Write_Time();break; //正常时间 分   加1
		case 10:time_buf1[5]--;if(time_buf1[5]<=0)   time_buf1[5]=59;    
              Ds1302_Write_Time();break; //正常时间 分   减1

		case 11:time_buf1[7]++;if(time_buf1[7]>7)   time_buf1[7]=1;    
              Ds1302_Write_Time();break; //正常时间 周   加1
		case 12:time_buf1[7]--;if(time_buf1[7]<=0)   time_buf1[7]=7;    
              Ds1302_Write_Time();break; //正常时间 周   减1         
        default :break;
	}
}

//从ds1302读来的十进制数据进行 个位十位分离，存到TempData[]中
void Time_changer(u8 *out_time)						
{
        Ds1302_Read_Time();        
        out_time[1]=time_buf1[1];	//年	
        out_time[2]=time_buf1[2];   //月
        out_time[3]=time_buf1[3];   //日
        out_time[4]=time_buf1[4];   //时
        out_time[5]=time_buf1[5];   //分
        out_time[6]=time_buf1[6];	//秒
        out_time[7]=time_buf1[7];   //周
}


/*------------------------------------------------
           向DS1302写入一字节数据
------------------------------------------------*/
void Ds1302_Write_Byte(unsigned char addr, unsigned char d)
{
	unsigned char i;
    Ds1302_DPinInit(Output);//数据口配置为输出
	RST_CLR;
	delay_us(2);
	SCK_CLR;
	delay_us(2);
	RST_SET;	
	delay_us(2);
	//写入目标地址：addr
	addr = addr & 0xFE;     //最低位置零
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
	
	//写入数据：d
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
	RST_CLR;					//停止DS1302总线
}
/*------------------------------------------------
           从DS1302读出一字节数据
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
	                  //写入目标地址：addr
	addr = addr | 0x01;//最低位置高
    Ds1302_DPinInit(Output);//数据口配置为输入
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
	
	//输出数据：temp
    Ds1302_DPinInit(Input);//数据口配置为输入        
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
	
	RST_CLR;	//停止DS1302总线

	return temp;
}

/*------------------------------------------------
           向DS1302写入时钟数据
------------------------------------------------*/
void Ds1302_Write_Time(void) 
{
	unsigned char i,tmp=0;
	for(i=0;i<8;i++)
	{                  //BCD处理
		tmp=time_buf1[i]/10;
		time_buf[i]=time_buf1[i]%10;
		time_buf[i]=time_buf[i]+tmp*16;
	}
	Ds1302_Write_Byte(ds1302_control_add,0x00);			//关闭写保护 
	Ds1302_Write_Byte(ds1302_charger_add,0xa9);			//涓流充电 		

	Ds1302_Write_Byte(ds1302_year_add,time_buf[1]);		//年 
	Ds1302_Write_Byte(ds1302_month_add,time_buf[2]);	//月 
	Ds1302_Write_Byte(ds1302_date_add,time_buf[3]);		//日 
	Ds1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//秒 
	Ds1302_Write_Byte(ds1302_min_add,time_buf[5]);		//分
	Ds1302_Write_Byte(ds1302_hr_add,time_buf[4]);		//时 
	Ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//周 
   
	Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护 
}

/*------------------------------------------------
           从DS1302读出时钟数据
------------------------------------------------*/
void Ds1302_Read_Time(void)  
{ 
	unsigned char i,tmp=0;   
    
	time_buf[1]=Ds1302_Read_Byte(ds1302_year_readd);		//年 
	Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护   
    
	time_buf[2]=Ds1302_Read_Byte(ds1302_month_readd);		//月 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护   
    
	time_buf[3]=Ds1302_Read_Byte(ds1302_date_readd);		//日 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护   
    
	time_buf[4]=Ds1302_Read_Byte(ds1302_hr_readd);		//时 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护   
    
	time_buf[5]=Ds1302_Read_Byte(ds1302_min_readd);		//分 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护   
    
	time_buf[6]=(Ds1302_Read_Byte(ds1302_sec_readd));//秒 
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护   
    
	time_buf[7]=Ds1302_Read_Byte(ds1302_day_readd);		//周     
    Ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护   
	
	for(i=0;i<8;i++)
	   {           //BCD处理
		tmp=time_buf[i]/16;
		time_buf1[i]=time_buf[i]%16;
		time_buf1[i]=time_buf1[i]+tmp*10;
	   }
}

/*------------------------------------------------
                DS1302初始化
------------------------------------------------*/
void Ds1302_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
  //  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE); //因为用的是Jtag的接口，所以要重定义
 //   AFIO->MAPR|=GPIO_Remap_SWJ_JTAGDisable;/*!< JTAG-DP Disabled and SW-DP Enabled */
    
    /*使能GPIOB,复用功能时钟*/
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
    
	RST_CLR;			//RST脚置低
	SCK_CLR;			//SCK脚置低

	
//    Ds1302_Write_Time();
    Ds1302_Write_Byte(ds1302_sec_add,0x00);	  //秒可以走
		Ds1302_Write_Byte(ds1302_hr_add ,0x00);	  //秒可以走
	//	writeclock();
}

void Ds1302_DPinInit(u8 State)
{
    GPIO_InitTypeDef GPIO_InitStructure;    
    if(State==Output)
    {
        /*配置为 输出 Out  */
        GPIO_InitStructure.GPIO_Pin = ZDA;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;  //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure); 	
    }
    else
    {
        GPIO_InitStructure.GPIO_Pin = ZDA;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;  //上拉输入
        GPIO_Init(GPIOA, &GPIO_InitStructure); 
    
    }
}

void display(void)
{
// Time_changer(time_buf);
// LCD_ShowNum(130,130,time_buf1[1],1,16);  //年
 //LCD_ShowNum(138,130,time_buf1[2],1,16);  //月
 //LCD_ShowChar(146,130,'-',16,0);          
// LCD_ShowNum(154,130,time_buf1[3],1,16);  //日
POINT_COLOR=0xFFFF;	//画笔颜色
BACK_COLOR=0x0000;  //背景色 

 LCD_ShowNum(165,0,time_buf1[4],2,16);  //时
	LCD_ShowChar(181,0,':',16,0);          
 LCD_ShowNum(189,0,time_buf1[5],2,16);//分
	LCD_ShowChar(207,0,':',16,0); 	
 LCD_ShowNum(215,0,time_buf1[6],2,16);//秒
 LCD_ShowNum(37,0,time_buf1[7],2,16);//秒
// delay_ms(1000);
	
}
/******************写时间制度12/24***************************/
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
  Ds1302_Read_Time();   //读取此时的时间
	Flash_write(USER_ADDR+(i*4)+1,(u32 *)time_buf1, 7);
}
