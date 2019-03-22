#include "sys.h"
#include "usart.h"	
#include "lcd.h"
#include "delay.h"
#include "string.h" 	 
#include "esp8266.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
////////////////////////////////////////////////////////////////////////////////// 	  
 

/////////////////////////////////////////////////////////////////  
unsigned char Message_length;
int OneNet_Connect=0;      //用于判断wifi模块是否连接上OneNet平台的标志

char Rx_Buff[200];
int  Rx_count=0;   //用于ESP8266判断接受数据的多少
int ok_flag=0;
char Message_Buf[20];  //用于存贮操作指令
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  

//初始化IO 串口1 
//bound:波特率*/
void uart_init(u32 bound)
	{
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART1);  //复位串口1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART1, ENABLE);                    //使能串口 

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;	
	static int i;
//		if(AT_Mode==0)        
//		Rx_count=0;
		
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
	    	Res =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据	
				Rx_Buff[Rx_count]=Res;
    if(AT_Mode==1)			                         //配置wifi模块发AT指令时的模式
		{
			if(strstr(Rx_Buff,"OK")||strstr(Rx_Buff,">"))    //判断ESP8266是否返回OK
			{
				 memset(Rx_Buff, 0, sizeof(Rx_Buff));  //清空Rx_Buff数组
         ok_flag=1;			 
         Rx_count=0;				
			}
			else                                   //否则继续接受数据
			{
						Rx_count++;	
					if(Rx_count==150)                   //数据溢出，清空数组 方便继续接收
						{
								Rx_count=0;
					    memset(Rx_Buff, 0, sizeof(Rx_Buff));
						}
			}
		}
			else if(AT_Mode==0)               //接收控制指令模式
			{
					 	
					if(Rx_count==150)                   //数据溢出，清空数组 方便继续接收
						{
								Rx_count=0;                  //重新从数组[0]开始接收数据
					    memset(Rx_Buff, 0, sizeof(Rx_Buff));  //清空当前数组所有数据
						}
					    ok_flag=1;                         //该标志是在发AT指令过程中才用的 可以在SendCmd()函数中查看其作用 保持AT指令的完成状态
						
						if(Message_length>0)                   //表示可以开始存贮操作指令
						 {
						    Message_Buf[i]=Rx_Buff[Rx_count];   //存贮操作指令数据
							  i++;
						    Message_length--;                  //存一个指令，剩余数量减一,判断操作指令是否存贮完成
						 }
						 
						if(Rx_count>3&&Rx_Buff[Rx_count-2]==0&&Rx_Buff[Rx_count-1]==0&&Rx_Buff[Rx_count]>0)   
						//如果当前接收到的数据大于0，并且这个数据的前两个数据为00 代表当前数据就是操作指令的长度。
						{
							 memset(Message_Buf, 0, sizeof(Message_Buf)); //清空存贮操作指令的数组，准备存贮新的操作指令
							
						   Message_length=Rx_Buff[Rx_count];      //将接收到的数据存为操作指令长度。
							 i=0;                                   //清空i
						}
						Rx_count++;                               //准备存储下一个数据 
						
			 }
           
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		 }	 
		
		 
		/**********判断WiFi模块是否连接上OneNet 平台*******/
		 {
		  if(Rx_Buff[Rx_count-3]==0x20&&Rx_Buff[Rx_count-2]==0x02&&Rx_Buff[Rx_count-1]==0x00&&Rx_Buff[Rx_count]==0x00)  //连接上平台时 平台会返回 20 02 00 00给我们
			{
			     OneNet_Connect=1;         //连接完成的标志位
			
			}
		 }
		 if(Rx_Buff[Rx_count-2]==0x64&&Rx_Buff[Rx_count-1]==0x01&&Rx_Buff[Rx_count]==0x60)  //连接上平台时 平台会返回 20 02 00 00给我们
			{
			     OneNet_Connect=0;         //连接断开
			
			}
		 
} 

