
/********************************************************/
/*
*   功能：  基于STM32单片机与OneNet平台的LED灯控制实验  	
*   日期：  2018.05.18                                 
*   来源：  广东海洋大学																
*   作者：  智能控制团队Allen                           
*   PS：由于某些代码是自己敲的 可能不规范 或者有些瑕疵 大家凑合着看吧  
*  说明：该程序存在一个BUG 配置完AT指令后 延迟函数delay_ms 就有点失灵了大概延迟时间会缩小10倍 我找不到原因。
*/
/********************************************************/
#include "stm32f10x.h"
#include "esp8266.h"
#include "delay.h"
#include "usart.h"
#include "stdio.h"
#include "sys.h"
#include "led.h"
#include "onenet.h"
#include "string.h" 
#include "Tim.h"

unsigned int Heart_Pack=0;  //用于定时器TIM1自加计数，用于满足设定自加数值时发送EDP心跳包的标志位
void Connect_OneNet(void);
u8  AT_Mode=0;     //发AT指令的模式 用于表示程序处于配置Wifi模块的模式  对串口接收数据进行不同的处理
u8  Contral_flag=0;  //用于存贮控制指令  判断进行什么操作


	int main(void)
 {	 

	  EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};   //定义一个结构体变量   供心跳包装载数据用
	 /*   配置LED灯  */
  	GPIO_InitTypeDef GPIO_InitStructure;  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;       
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
		
  	 uart_init(115200);    //打开串口1
	
     ESP8266_GPIO_Init();  //初始化ESP8266的引脚
	   ESP8266Mode_inti();   //初始化ESP8266的AT指令
		
     Tim1_Init(5000,72);   //定时器周期配置为5MS
		
     	Connect_OneNet();    //接入OneNet平台
	
	  while(1)	             //while循环执行各种功能 
		{   
			if(Heart_Pack==5000)              //每隔25秒发一次心跳包   OneNet平台默认四分钟无数据交换就会断开与设备的连接 发心跳包可以保证连接。
			{
				EDP_PacketPing(&edpPacket);     //装载并发送心跳包
				Heart_Pack=0;
			
			}   //定时发送心跳包  
			 
		/*用strstr函数来判断操作指令是否匹配 对该函数不了解的朋友自行百度吧*/	 
       if(strstr((const char*)Message_Buf,"OPEN"))    //判断到操作指令为OPEN 
			 {
			    LED_ON;   //打开LED
				  OneNet_SendData(1);  //向平台发数据1
				 	delay_ms(100);     //延迟保护 防止频繁发数据，容易断开与平台连接
				  memset(Message_Buf, 0, sizeof(Message_Buf));    //执行完指令 清空指令存贮空间 防止继续执行该指令
			 }
		   if(strstr((const char*)Message_Buf,"CLOSE"))   //判断到操作指令为CLOSE 
			 {
			    LED_OFF; //关闭LED
				  OneNet_SendData(0);  //向平台发数据0
				  delay_ms(100);   //延迟保护 防止频繁发数据，容易断开与平台连接
				  memset(Message_Buf, 0, sizeof(Message_Buf));    //执行完指令 清空指令存贮空间 防止继续执行该指令
			 }
		
		}
			
     
	  
 }


void Connect_OneNet(void)
{
     while(!OneNet_Connect)     //判断是否接入平台成功
	   {	
	    	while(OneNet_DevLink())			//接入OneNET
	   	 delay_ms(10000);       //由于延迟函数出BUG了 实际上是大概1秒延迟 稍微等待接入完成
	   }


}
		
