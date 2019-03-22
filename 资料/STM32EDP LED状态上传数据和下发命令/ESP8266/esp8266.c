/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	esp8266.c
	*
	*	ԭ���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-05-08
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		ESP8266�ļ�����
	*
	*	�汾�޸ļ�¼��	��
	
	* �޸��ߣ� �㶫�����ѧ���ܿ����Ŷ� Allen
	
	* ����  �� 2018.05.18
	************************************************************
	************************************************************
	************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"

//�����豸����
#include "esp8266.h"

//Ӳ������
#include "delay.h"
#include "usart.h"

//C��
#include <string.h>
#include <stdio.h>
#define LED      PAout(8)



unsigned char esp8266_buf[128];
unsigned short esp8266_cnt = 0, esp8266_cntPre = 0;




/** ���ڷ���һ�����ݵĺ���
  *
  *
  *
  */ 
void USART_Write(unsigned char *cmd, int len)
{  
	  int i;
	   USART_ClearFlag(USART1,USART_FLAG_TC);    //����֮ǰ��շ��ͱ�־  û����һ�� �����׶��� ��һ���������׶�ʧ
	   for(i=0;i<len;i++)
	   {
		   USART_SendData(USART1,*cmd);   //���͵�ǰ����
			 while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);  //�������
//			 delay_ms(30);
			 cmd++;      //ָ���Լ� ׼��������һ������
		   
		 }
 
}

/**
  * @brief  ��ʼ��ESP8266�õ���GPIO����
  * @param  ��
  * @retval ��
  */
void ESP8266_GPIO_Init(void)
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;


	/* ���� CH_PD ����*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;               //�����������ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;                      //��ʼ��CH-DP���� ����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;              //����ʱ��
	GPIO_Init(GPIOA,&GPIO_InitStructure);   
	GPIO_SetBits(GPIOA,GPIO_Pin_14); 
  
}

void ESP8266Mode_inti(void)
{
//	  int i=0;
	  AT_Mode = 1;  //���뷢ATָ��ģʽ
	
/****wifiģ����OneNetƽ̨���ݶԽ����� */
    SendCmd(AT, "OK", 10000);		//ģ����Ч�Լ��
    SendCmd(CWMODE, "OK", 10000);	//ģ�鹤��ģʽ
    SendCmd(wifi_RST, "OK", 10000);		//ģ������
    SendCmd(CWJAP, "OK", 10000);		//������Ҫ���ӵ�WIFI�ȵ�SSID������
    SendCmd(CIPSTART, "OK", 10000);	//TCP����
    SendCmd(CIPMODE1, "OK", 10000);	//����͸��ģʽ
	  SendCmd(CIPSEND, ">", 10000);	//����͸��ģʽ
     
	
  /***������Ϊ��������wifiģ������ͨ��  
	  SendCmd(AT, "OK", 10000);		//ģ����Ч�Լ��
	  SendCmd(wifi_RST, "OK", 10000);		//ģ������
    SendCmd(CWMODE, "OK", 10000);	//ģ�鹤��ģʽ ����STA��APģʽ
		SendCmd(CWJAP, "OK", 10000);		//������Ҫ���ӵ�WIFI�ȵ�SSID������ 
		SendCmd(CIFSR, "OK", 10000);   //��ѯ·��������ķ�������ַ
		SendCmd(CIPSTART, "OK", 10000);   //������Է�����  
		SendCmd(CIPMODE1, "OK", 10000);   //����͸��ģʽ
		SendCmd(CIPSEND, "OK", 10000);   //����͸��ģʽ
		*/
		
		 AT_Mode = 0;   //ATָ������ �˳���ģʽ
	}

	
/** 
	* �������ܣ� ����Cmd����ĺ���
  * CMD�� 		��Ҫ���͵�ATָ��
  * result �� ���ͳɹ�ʱ���ص���ֵ��result��������Ա�
  * timeOut ���ӳ�ʱ��
  *	
*/	
	
void SendCmd(char* cmd, char* result, int timeOut)
{
    while(1)
    {
			  memset(Rx_Buff, 0, sizeof(Rx_Buff)); //��������֮ǰ��������������飬�����ڴ����н��ա�
			  Rx_count=0;
        USART_Write((unsigned char *)cmd,strlen((const char *)cmd));   //�ô��ڰ�cmd����д��ESP8266
        delay_ms(timeOut);                                          //�ӳٵȴ�
			  LED=~LED;        //��������
        if(ok_flag==1)	//�Ƚ�����ָ������������Ƿ�һ�����ж��Ƿ���Ԥ�ڵĽ��  ��Ԥ�ڽ����ͬ����ʾָ�����óɹ�������
        {  
					  ok_flag=0;   //��ձ�־
            break;
        }
        else
        {
            delay_ms(100);
					
        }
    }
}


/**   
 * �������ܣ�ESP8266д���ݵĺ���

 *   

*/
void ESP8266_SendData(unsigned char *data, unsigned short len)
{
	 
  	USART_Write(data,len);   //��������

}



/*** ���º�����Ϊԭ���߱�д ĳЩ�������� ����û��ȥ�о� ����Ҳ��̫�� �� ���þ��� ***/

//==========================================================
//	�������ƣ�	ESP8266_Clear
//
//	�������ܣ�	��ջ���
//
//	��ڲ�����	��
//
//	���ز�����	��
//
//	˵����		
//==========================================================
void ESP8266_Clear(void)
{

	memset(esp8266_buf, 0, sizeof(esp8266_buf));
	esp8266_cnt = 0;

}

//==========================================================
//	�������ƣ�	ESP8266_WaitRecive
//
//	�������ܣ�	�ȴ��������
//
//	��ڲ�����	��
//
//	���ز�����	REV_OK-�������		REV_WAIT-���ճ�ʱδ���
//
//	˵����		ѭ�����ü���Ƿ�������
//==========================================================
_Bool ESP8266_WaitRecive(void)
{

	if(esp8266_cnt == 0) 							//������ռ���Ϊ0 ��˵��û�д��ڽ��������У�����ֱ����������������
		return REV_WAIT;
		
	if(esp8266_cnt == esp8266_cntPre)				//�����һ�ε�ֵ�������ͬ����˵���������
	{
		esp8266_cnt = 0;							//��0���ռ���
			
		return REV_OK;								//���ؽ�����ɱ�־
	}
		
	esp8266_cntPre = esp8266_cnt;					//��Ϊ��ͬ
	
	return REV_WAIT;								//���ؽ���δ��ɱ�־

}

//==========================================================
//	�������ƣ�	ESP8266_GetIPD
//
//	�������ܣ�	��ȡƽ̨���ص�����
//
//	��ڲ�����	�ȴ���ʱ��(����10ms)
//
//	���ز�����	ƽ̨���ص�ԭʼ����
//
//	˵����		��ͬ�����豸���صĸ�ʽ��ͬ����Ҫȥ����
//				��ESP8266�ķ��ظ�ʽΪ	"+IPD,x:yyy"	x�������ݳ��ȣ�yyy����������
//==========================================================
unsigned char *ESP8266_GetIPD(unsigned short timeOut)
{

	char *ptrIPD = NULL;
	
	do
	{
		if(ESP8266_WaitRecive() == REV_OK)								//����������
		{
			ptrIPD = strstr((char *)esp8266_buf, "IPD,");				//������IPD��ͷ
			if(ptrIPD == NULL)											//���û�ҵ���������IPDͷ���ӳ٣�������Ҫ�ȴ�һ�ᣬ�����ᳬ���趨��ʱ��
			{
				//UsartPrintf(USART_DEBUG, "\"IPD\" not found\r\n");
			}
			else
			{
				ptrIPD = strchr(ptrIPD, ':');							//�ҵ�':'
				if(ptrIPD != NULL)
				{
					ptrIPD++;
					return (unsigned char *)(ptrIPD);
				}
				else
					return NULL;
				
			}
		}
		
		delay_ms(50);													//��ʱ�ȴ�
	} while(timeOut--);
	
	return NULL;														//��ʱ��δ�ҵ������ؿ�ָ��

}


