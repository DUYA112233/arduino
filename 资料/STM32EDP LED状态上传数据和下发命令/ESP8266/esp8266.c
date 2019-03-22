/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	esp8266.c
	*
	*	原作者： 		张继瑞
	*
	*	日期： 		2017-05-08
	*
	*	版本： 		V1.0
	*
	*	说明： 		ESP8266的简单驱动
	*
	*	版本修改记录：	无
	
	* 修改者： 广东海洋大学智能控制团队 Allen
	
	* 日期  ： 2018.05.18
	************************************************************
	************************************************************
	************************************************************
**/

//单片机头文件
#include "stm32f10x.h"

//网络设备驱动
#include "esp8266.h"

//硬件驱动
#include "delay.h"
#include "usart.h"

//C库
#include <string.h>
#include <stdio.h>
#define LED      PAout(8)



unsigned char esp8266_buf[128];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;




/** 串口发送一组数据的函数
  *
  *
  *
  */ 
void USART_Write(unsigned char *cmd, int len)
{  
	  int i;
	   USART_ClearFlag(USART1,USART_FLAG_TC);    //发送之前清空发送标志  没有这一句 很容易丢包 第一个数据容易丢失
	   for(i=0;i<len;i++)
	   {
		   USART_SendData(USART1,*cmd);   //发送当前数据
			 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  //发送完成
//			 delay_ms(30);
			 cmd++;      //指针自加 准备发送下一个数据
		   
		 }
 
}

/**
  * @brief  初始化ESP8266用到的GPIO引脚
  * @param  无
  * @retval 无
  */
void ESP8266_GPIO_Init(void)
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* 配置 CH_PD 引脚*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;               //设置推挽输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;                      //初始化CH-DP引脚 拉高
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;              //设置时钟
	GPIO_Init(GPIOA,&GPIO_InitStructure);   
	GPIO_SetBits(GPIOA,GPIO_Pin_14); 
  
}

void ESP8266Mode_inti(void)
{
//	  int i=0;
	  AT_Mode = 1;  //进入发AT指令模式
	
/****wifi模块与OneNet平台数据对接配置 */
    SendCmd(AT, "OK", 10000);		//模块有效性检查
    SendCmd(CWMODE, "OK", 10000);	//模块工作模式
    SendCmd(wifi_RST, "OK", 10000);		//模块重置
    SendCmd(CWJAP, "OK", 10000);		//配置需要连接的WIFI热点SSID和密码
    SendCmd(CIPSTART, "OK", 10000);	//TCP连接
    SendCmd(CIPMODE1, "OK", 10000);	//配置透传模式
	  SendCmd(CIPSEND, ">", 10000);	//进入透传模式
     
	
  /***电脑作为服务器，wifi模块与其通信  
	  SendCmd(AT, "OK", 10000);		//模块有效性检查
	  SendCmd(wifi_RST, "OK", 10000);		//模块重置
    SendCmd(CWMODE, "OK", 10000);	//模块工作模式 兼容STA和AP模式
		SendCmd(CWJAP, "OK", 10000);		//配置需要连接的WIFI热点SSID和密码 
		SendCmd(CIFSR, "OK", 10000);   //查询路由器分配的服务器地址
		SendCmd(CIPSTART, "OK", 10000);   //接入电脑服务器  
		SendCmd(CIPMODE1, "OK", 10000);   //配置透传模式
		SendCmd(CIPSEND, "OK", 10000);   //开启透传模式
		*/
		
		 AT_Mode = 0;   //AT指令发送完毕 退出该模式
	}

	
/** 
	* 函数功能： 发送Cmd命令的函数
  * CMD： 		需要发送的AT指令
  * result ： 发送成功时返回的数值与result期望结果对比
  * timeOut ：延迟时间
  *	
*/	
	
void SendCmd(char* cmd, char* result, int timeOut)
{
    while(1)
    {
			  memset(Rx_Buff, 0, sizeof(Rx_Buff)); //发送数据之前，先情况接收数组，数据在串口中接收。
			  Rx_count=0;
        USART_Write((unsigned char *)cmd,strlen((const char *)cmd));   //用串口把cmd命令写给ESP8266
        delay_ms(timeOut);                                          //延迟等待
			  LED=~LED;        //闪灯提醒
        if(ok_flag==1)	//比较两个指针里面的数据是否一样，判断是否有预期的结果  和预期结果相同，表示指令设置成功，跳出
        {  
					  ok_flag=0;   //清空标志
            break;
        }
        else
        {
            delay_ms(100);
					
        }
    }
}


/**   
 * 函数功能：ESP8266写数据的函数

 *   

*/
void ESP8266_SendData(unsigned char *data, unsigned short len)
{
	 
  	USART_Write(data,len);   //发送数据

}



/*** 以下函数均为原作者编写 某些函数功能 本人没有去研究 所以也不太懂 哈 能用就行 ***/

//==========================================================
//	函数名称：	ESP8266_Clear
//
//	函数功能：	清空缓存
//
//	入口参数：	无
//
//	返回参数：	无
//
//	说明：		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	函数名称：	ESP8266_WaitRecive
//
//	函数功能：	等待接收完成
//
//	入口参数：	无
//
//	返回参数：	REV_OK-接收完成		REV_WAIT-接收超时未完成
//
//	说明：		循环调用检测是否接收完成
//==========================================================
_Bool ESP8266_WaitRecive(void)
{

	if(esp8266_cnt == 0) 							//如果接收计数为0 则说明没有处于接收数据中，所以直接跳出，结束函数
		return REV_WAIT;
		
	if(esp8266_cnt == esp8266_cntPre)				//如果上一次的值和这次相同，则说明接收完毕
	{
		esp8266_cnt = 0;							//清0接收计数
			
		return REV_OK;								//返回接收完成标志
	}
		
	esp8266_cntPre = esp8266_cnt;					//置为相同
	
	return REV_WAIT;								//返回接收未完成标志

}

//==========================================================
//	函数名称：	ESP8266_GetIPD
//
//	函数功能：	获取平台返回的数据
//
//	入口参数：	等待的时间(乘以10ms)
//
//	返回参数：	平台返回的原始数据
//
//	说明：		不同网络设备返回的格式不同，需要去调试
//				如ESP8266的返回格式为	"+IPD,x:yyy"	x代表数据长度，yyy是数据内容
//==========================================================
unsigned char *ESP8266_GetIPD(unsigned short timeOut)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(ESP8266_WaitRecive() == REV_OK)								//如果接收完成
		{
			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//搜索“IPD”头
			if(ptrIPD == NULL)											//如果没找到，可能是IPD头的延迟，还是需要等待一会，但不会超过设定的时间
			{
				//UsartPrintf(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//找到':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (unsigned char *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		delay_ms(50);													//延时等待
	} while(timeOut--);
	
	return NULL;														//超时还未找到，返回空指针

}


