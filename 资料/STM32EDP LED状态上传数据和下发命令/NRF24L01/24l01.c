#include "24l01.h"
#include "lcd.h"
#include "delay.h"
#include "spi.h"
#include "EEPROM.H"
#include "ds1302.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//NRF24L01 驱动函数	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2010/6/16 
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  
 
	 

const u8 TX_ADDRESS[TX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
const u8 RX_ADDRESS[RX_ADR_WIDTH]={0x34,0x43,0x10,0x10,0x01}; //发送地址
u8 RXdate[6]={0,0,0,0,0,0};            //接收到的5位数据存入的数组      

u8 CardKeep[6]={0,0,0,0,0,0};                            //存贮NRF接收到卡号的数组,第五位为考勤次数
u8 Cardjudge[6]={0,0,0,0,0,0};                           //用于判断存进去的卡号是否成功	
u8 Cardjudge1[6]={0,0,0,0,0,0};                                     //用于存读出来的卡号数据
 u16 Cardnum;  //目前拥有的卡数
//初始化24L01的IO口
void NRF24L01_Init(void)
{
	
	/*RCC->APB2ENR|=1<<2;    //使能PORTA口时钟 
	RCC->APB2ENR|=1<<4;    //使能PORTC口时钟 
	GPIOA->CRL&=0XFFF000FF;//PA4输出
	GPIOA->CRL|=0X00033300; 
	GPIOA->ODR|=7<<2;	   //PA2.3.4 输出1		 
	GPIOC->CRL&=0XFF00FFFF;//PC4输出 PC5输出
	GPIOC->CRL|=0X00830000; 
	GPIOC->ODR|=3<<4;	   //上拉	*/ 
	SPI2_Init();    //初始化SPI
	NRF24L01_CE=0; 	//使能24L01
	NRF24L01_CSN=1;	//SPI片选取消	
  
 
}
//检测24L01是否存在
//返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   	 
	NRF24L01_Write_Buf(N_WRITE_REG+TX_ADDR,buf,5);//写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//检测24L01错误	
	return 0;		 //检测到24L01
}	 	 
//SPI写寄存器
//reg:指定寄存器地址
//value:写入的值
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
   	NRF24L01_CSN=0;                 //使能SPI传输
  	status =SPI2_ReadWriteByte(reg);//发送寄存器号 
  	SPI2_ReadWriteByte(value);      //写入寄存器的值
  	NRF24L01_CSN=1;                 //禁止SPI传输	   
  	return(status);       			//返回状态值
}
//读取SPI寄存器值
//reg:要读的寄存器
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
 	NRF24L01_CSN = 0;          //使能SPI传输		
  	SPI2_ReadWriteByte(reg);   //发送寄存器号
  	reg_val=SPI2_ReadWriteByte(0XFF);//读取寄存器内容
  	NRF24L01_CSN = 1;          //禁止SPI传输		    
  	return(reg_val);           //返回状态值
}	
//在指定位置读出指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
  	NRF24L01_CSN = 0;           //使能SPI传输
  	status=SPI2_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI2_ReadWriteByte(0XFF);//读出数据
  	NRF24L01_CSN=1;       //关闭SPI传输
  	return status;        //返回读到的状态值
}
//在指定位置写指定长度的数据
//reg:寄存器(位置)
//*pBuf:数据指针
//len:数据长度
//返回值,此次读到的状态寄存器值
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
 	NRF24L01_CSN = 0;          //使能SPI传输
  	status = SPI2_ReadWriteByte(reg);//发送寄存器值(位置),并读取状态值
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI2_ReadWriteByte(*pBuf++); //写入数据	 
  	NRF24L01_CSN = 1;       //关闭SPI传输
  	return status;          //返回读到的状态值
}				   
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:发送完成状况
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
 	SPI2_SetSpeed(SPI_BaudRatePrescaler_8);//spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   
	NRF24L01_CE=0;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//写数据到TX BUF  32个字节
 	NRF24L01_CE=1;//启动发送	   
	while(NRF24L01_IRQ!=0);//等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值	   
	NRF24L01_Write_Reg(N_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX)//达到最大重发次数
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//清除TX FIFO寄存器 
		return MAX_TX; 
	}
	if(sta&TX_OK)//发送完成
	{
		return TX_OK;
	}
	return 0xff;//其他原因发送失败
}
//启动NRF24L01发送一次数据
//txbuf:待发送数据首地址
//返回值:0，接收完成；其他，错误代码
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
	SPI2_SetSpeed(SPI_BaudRatePrescaler_8); //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）   
	sta=NRF24L01_Read_Reg(STATUS);  //读取状态寄存器的值    	 
	NRF24L01_Write_Reg(N_WRITE_REG+STATUS,sta); //清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)//接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);//读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);//清除RX FIFO寄存器 
		return 0; 
	}	   
	return 1;//没收到任何数据
}					    
//该函数初始化NRF24L01到RX模式
//设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR
//当CE变高后,即进入RX模式,并可以接收数据了		   
void RX_Mode(void)
{
	NRF24L01_CE=0;	  
  	NRF24L01_Write_Buf(N_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);//写RX节点地址
	  
  	NRF24L01_Write_Reg(N_WRITE_REG+EN_AA,0x01);    //使能通道0的自动应答    
  	NRF24L01_Write_Reg(N_WRITE_REG+EN_RXADDR,0x01);//使能通道0的接收地址  	 
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_CH,40);	     //设置RF通信频率		  
  	NRF24L01_Write_Reg(N_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);//选择通道0的有效数据宽度 	    
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_SETUP,0x0f);//设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg(N_WRITE_REG+CONFIG, 0x0f);//配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
  	NRF24L01_CE = 1; //CE为高,进入接收模式 
}						 
//该函数初始化NRF24L01到TX模式
//设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR
//PWR_UP,CRC使能
//当CE变高后,即进入RX模式,并可以接收数据了		   
//CE为高大于10us,则启动发送.	 
void TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
  	NRF24L01_Write_Buf(N_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//写TX节点地址 
  	NRF24L01_Write_Buf(N_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //设置TX节点地址,主要为了使能ACK	  

  	NRF24L01_Write_Reg(N_WRITE_REG+EN_AA,0x01);     //使能通道0的自动应答    
  	NRF24L01_Write_Reg(N_WRITE_REG+EN_RXADDR,0x01); //使能通道0的接收地址  
  	NRF24L01_Write_Reg(N_WRITE_REG+SETUP_RETR,0x1a);//设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_CH,40);       //设置RF通道为40
  	NRF24L01_Write_Reg(N_WRITE_REG+RF_SETUP,0x0f);  //设置TX发射参数,0db增益,2Mbps,低噪声增益开启   
  	NRF24L01_Write_Reg(N_WRITE_REG+CONFIG,0x0e);    //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF24L01_CE=1;//CE为高,10us后启动发送
}		  

/*******************************保存发过来的卡号到Flash********************************/
/*** 发过来的卡号数据是四位数据，用四位数组存贮每记录一次数据就把卡号Cardnum+1************/
u16 KeepCard(u16 Cardnum,u8 *Cardkeep)
{
	 u16 i=0,flag=0;


 Flash_write(USER_ADDR+Cardnum*2,(u32 *)Cardkeep, 5);        //将发送过来的卡号贮存到Flash
 Flash_read(USER_ADDR+Cardnum*2 ,(u32 *)Cardjudge, 5);
 for(i=0;i<5;i++)
  {  
		if(Cardjudge[i]!=Cardkeep[i])                  //判断读出来的数据和写进去的数据是否一样
		{
		  
			flag=0;
			break;                                      //只需要判断到一个数据不一样就可以中断判断了
		}
		else flag=1;                                  //如果写入的卡号和读出来的卡号一模一样 则返回1 否则返回0
	}

	
	return flag;
}
/******************************NRF监测函数********************************/
/************************用于实时接收数据并处理****************************/
void NRFChecking()
{   
  	u16 flag=0,i=0,j=0,sign=0;     //判断是否写入成功的标志
	  RX_Mode();     //打开接收模式，使NRF长期处于接收数据状态 
    NRF24L01_RxPacket(RXdate);  //接收到的数据存到RXdate数组里面
	 if(RXdate[4]==KeepCardSign)   //注册模式的标志 发过来的数据是注册的卡号
	 {
	  
		 flag=KeepCard(Cardnum,RXdate);  //写入接收到的数据  写入成功返回1 失败返回0
		 	if(flag==0)
	   {
		   printf("写入卡号失败");
	   }
	   else printf("卡号记录成功") ; 
		 
		 Cleandate();//清空数组缓存
		 Cardnum=Cardnum+1;                  //注册卡号成功 卡的数据加1
	  
	 }
	 
	if(RXdate[4]==Normalmode)          //正常开门模式 记录卡号考勤
	{
		for(i=0;i<Cardnum;i++)           //逐张卡号判断 判断是那一张卡的信息
		{
			Flash_read(USER_ADDR+i*2 ,(u32 *)Cardjudge1, 6);       //逐张卡读取 然后判断 判断第i张卡
		 for(j=0;j<4;j++)                            
			{
				if(RXdate[j]==Cardjudge1[j])                  //如果卡号对上了一次 sign就自加一次 当sign加满4次的时候 证明这张卡和他一模一样了
				{
				   sign++;
				}
				if(sign==4)	                                  //sign满了4 就终止跳出
				{
				  Flash_read(USER_ADDR+i*4 ,(u32 *)Cardjudge1, 6);    //再次读出判断好的卡号
          Cardjudge1[5]=Cardjudge1[5]+1;               //数组的第六位存贮的是考勤的次数 
          Flash_write(USER_ADDR+i*4,(u32 *)Cardjudge1, 6);  //把数据重新再写会Flash 此时考勤次数已经加1	
					 Recordtime(i);
          Cleandate();					
				}
				
			}
		}
		
		
	}
		 
	  
}

/*********************************清空缓存的函数*******************************/
void Cleandate(void)               //用于清除写完数据后的数组;
{

  u16 i=0;
	for(i=0;i<6;i++)
	{	
  	RXdate[i]=0;   //清空数组的数据
		CardKeep[i]=0;
		Cardjudge[i]=0;
		Cardjudge1[i]=0;
	}

}

