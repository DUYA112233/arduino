#ifndef _ESP8266_H_
#define _ESP8266_H_





#define REV_OK		0	//������ɱ�־
#define REV_WAIT	1	//����δ��ɱ�־

extern unsigned char  AT_Mode;     //��ATָ���ģʽ ���ڱ�ʾ����������Wifiģ���ģʽ  �Դ��ڽ������ݽ��в�ͬ�Ĵ���
extern unsigned char  Contral_flag;  //���ڴ�������ָ��  �жϽ���ʲô����
extern char Rx_Buff[200];
extern int  Rx_count;
#define API_KEY     "LZDYWJJkQ0a4Wa1bu=cG2IRu3Ws="		//��Ҫ����Ϊ�û��Լ��Ĳ���
#define DEV_ID      "30027152"							//��Ҫ����Ϊ�û��Լ��Ĳ���

//#define API_KEY     "4js4HIFpihbdrVuZJmKm6syRyxo="		//��Ҫ����Ϊ�û��Լ��Ĳ���
//#define DEV_ID      "29802187"							//��Ҫ����Ϊ�û��Լ��Ĳ���

/******��OneNet�������������ݶԽ�ʱ������ */
#define AT          "AT\r\n"	
#define CWMODE      "AT+CWMODE=3\r\n"		//STA+APģʽ
#define wifi_RST    "AT+RST\r\n"
#define CIFSR       "AT+CIFSR\r\n"
#define CWJAP       "AT+CWJAP=\"ICT\",\"icteam2017\"\r\n"	//ssid: onenet ���룺��
#define CIPSTART    "AT+CIPSTART=\"TCP\",\"jjfaedp.hedevice.com\",876\r\n"	//EDP������ 183.230.40.39/876
//#define CIPSTART    "AT+CIPSTART=\"TCP\",\"183.230.40.33\",80\r\n"		//HTTP������183.230.40.33/80    
#define CIPMODE0    "AT+CIPMODE=0\r\n"		//��͸��ģʽ
#define CIPMODE1    "AT+CIPMODE=1\r\n"		//͸��ģʽ
#define CIPSEND     "AT+CIPSEND\r\n"   
#define Out_CIPSEND     "+++" 
#define CIPSTATUS   "AT+CIPSTATUS\r\n"		//����״̬��ѯ



/*********Wifiģ������Ϊ������ģʽ�� ������Ϊ�ͻ�������������ݶԽ�ʱ������  
#define AT          "AT\r\n"	
#define CWMODE      "AT+CWMODE=3\r\n"		//STA+APģʽ
#define wifi_RST    "AT+RST\r\n"
#define CWJAP       "AT+CWJAP=\"ICT\",\"icteam2017\"\r\n"	//ssid: ICT ���룺icteam2017
#define Check_CWJAP "AT+CWJAP?\r\n"	//��ѯ�Ƿ����·����
#define CIFSR       "AT+CIFSR\r\n"  //��ѯ·��������ĵ�ַ
#define CIPMUX       "AT+CIPMUX=1\r\n"  //��������ģʽ
#define CIPSERVER     "AT+CIPSERVER=1,8089\r\n"  //����������
#define CIPSTO     "AT+CIPSTO=2880\r\n"    //���÷�������ʱʱ��
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
