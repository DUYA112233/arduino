#ifndef _ESP8266_H_
#define _ESP8266_H_





#define REV_OK		0	//接收完成标志
#define REV_WAIT	1	//接收未完成标志

extern unsigned char  AT_Mode;     //发AT指令的模式 用于表示程序处于配置Wifi模块的模式  对串口接收数据进行不同的处理
extern unsigned char  Contral_flag;  //用于存贮控制指令  判断进行什么操作
extern char Rx_Buff[200];
extern int  Rx_count;
#define API_KEY     "LZDYWJJkQ0a4Wa1bu=cG2IRu3Ws="		//需要定义为用户自己的参数
#define DEV_ID      "30027152"							//需要定义为用户自己的参数

//#define API_KEY     "4js4HIFpihbdrVuZJmKm6syRyxo="		//需要定义为用户自己的参数
//#define DEV_ID      "29802187"							//需要定义为用户自己的参数

/******与OneNet服务器进行数据对接时的配置 */
#define AT          "AT\r\n"	
#define CWMODE      "AT+CWMODE=3\r\n"		//STA+AP模式
#define wifi_RST    "AT+RST\r\n"
#define CIFSR       "AT+CIFSR\r\n"
#define CWJAP       "AT+CWJAP=\"ICT\",\"icteam2017\"\r\n"	//ssid: onenet 密码：空
#define CIPSTART    "AT+CIPSTART=\"TCP\",\"jjfaedp.hedevice.com\",876\r\n"	//EDP服务器 183.230.40.39/876
//#define CIPSTART    "AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n"		//HTTP服务器183.230.40.33/80    
#define CIPMODE0    "AT+CIPMODE=0\r\n"		//非透传模式
#define CIPMODE1    "AT+CIPMODE=1\r\n"		//透传模式
#define CIPSEND     "AT+CIPSEND\r\n"   
#define Out_CIPSEND     "+++" 
#define CIPSTATUS   "AT+CIPSTATUS\r\n"		//网络状态查询



/*********Wifi模块设置为服务器模式， 电脑作为客户端与其进行数据对接时的配置  
#define AT          "AT\r\n"	
#define CWMODE      "AT+CWMODE=3\r\n"		//STA+AP模式
#define wifi_RST    "AT+RST\r\n"
#define CWJAP       "AT+CWJAP=\"ICT\",\"icteam2017\"\r\n"	//ssid: ICT 密码：icteam2017
#define Check_CWJAP "AT+CWJAP?\r\n"	//查询是否接入路由器
#define CIFSR       "AT+CIFSR\r\n"  //查询路由器分配的地址
#define CIPMUX       "AT+CIPMUX=1\r\n"  //开启多连模式
#define CIPSERVER     "AT+CIPSERVER=1,8089\r\n"  //创建服务器
#define CIPSTO     "AT+CIPSTO=2880\r\n"    //设置服务器超时时间
*/


void ESP8266_Init(void);

void ESP8266_Clear(void);

void SendCmd(char* cmd, char* result, int timeOut);

unsigned char *ESP8266_GetIPD(unsigned short timeOut);

void ESP8266_SendData(unsigned char *data, unsigned short len);

void ESP8266Mode_inti(void);

void ESP8266_GPIO_Init(void);

void USART_Write(unsigned char *cmd, int len);

#endif
