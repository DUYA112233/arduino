
/********************************************************/
/*
*   ���ܣ�  ����STM32��Ƭ����OneNetƽ̨��LED�ƿ���ʵ��  	
*   ���ڣ�  2018.05.18                                 
*   ��Դ��  �㶫�����ѧ																
*   ���ߣ�  ���ܿ����Ŷ�Allen                           
*   PS������ĳЩ�������Լ��õ� ���ܲ��淶 ������Щ覴� ��Ҵպ��ſ���  
*  ˵�����ó������һ��BUG ������ATָ��� �ӳٺ���delay_ms ���е�ʧ���˴���ӳ�ʱ�����С10�� ���Ҳ���ԭ��
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

unsigned int Heart_Pack=0;  //���ڶ�ʱ��TIM1�ԼӼ��������������趨�Լ���ֵʱ����EDP�������ı�־λ
void Connect_OneNet(void);
u8  AT_Mode=0;     //��ATָ���ģʽ ���ڱ�ʾ����������Wifiģ���ģʽ  �Դ��ڽ������ݽ��в�ͬ�Ĵ���
u8  Contral_flag=0;  //���ڴ�������ָ��  �жϽ���ʲô����


	int main(void)
 {	 

	  EDP_PACKET_STRUCTURE edpPacket = {NULL, 0, 0, 0};   //����һ���ṹ�����   ��������װ��������
	 /*   ����LED��  */
  	GPIO_InitTypeDef GPIO_InitStructure;  
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
		GPIO_InitStructure.GPIO_Pin =GPIO_Pin_8;       
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
		
  	 uart_init(115200);    //�򿪴���1
	
     ESP8266_GPIO_Init();  //��ʼ��ESP8266������
	   ESP8266Mode_inti();   //��ʼ��ESP8266��ATָ��
		
     Tim1_Init(5000,72);   //��ʱ����������Ϊ5MS
		
     	Connect_OneNet();    //����OneNetƽ̨
	
	  while(1)	             //whileѭ��ִ�и��ֹ��� 
		{   
			if(Heart_Pack==5000)              //ÿ��25�뷢һ��������   OneNetƽ̨Ĭ���ķ��������ݽ����ͻ�Ͽ����豸������ �����������Ա�֤���ӡ�
			{
				EDP_PacketPing(&edpPacket);     //װ�ز�����������
				Heart_Pack=0;
			
			}   //��ʱ����������  
			 
		/*��strstr�������жϲ���ָ���Ƿ�ƥ�� �Ըú������˽���������аٶȰ�*/	 
       if(strstr((const char*)Message_Buf,"OPEN"))    //�жϵ�����ָ��ΪOPEN 
			 {
			    LED_ON;   //��LED
				  OneNet_SendData(1);  //��ƽ̨������1
				 	delay_ms(100);     //�ӳٱ��� ��ֹƵ�������ݣ����׶Ͽ���ƽ̨����
				  memset(Message_Buf, 0, sizeof(Message_Buf));    //ִ����ָ�� ���ָ������ռ� ��ֹ����ִ�и�ָ��
			 }
		   if(strstr((const char*)Message_Buf,"CLOSE"))   //�жϵ�����ָ��ΪCLOSE 
			 {
			    LED_OFF; //�ر�LED
				  OneNet_SendData(0);  //��ƽ̨������0
				  delay_ms(100);   //�ӳٱ��� ��ֹƵ�������ݣ����׶Ͽ���ƽ̨����
				  memset(Message_Buf, 0, sizeof(Message_Buf));    //ִ����ָ�� ���ָ������ռ� ��ֹ����ִ�и�ָ��
			 }
		
		}
			
     
	  
 }


void Connect_OneNet(void)
{
     while(!OneNet_Connect)     //�ж��Ƿ����ƽ̨�ɹ�
	   {	
	    	while(OneNet_DevLink())			//����OneNET
	   	 delay_ms(10000);       //�����ӳٺ�����BUG�� ʵ�����Ǵ��1���ӳ� ��΢�ȴ��������
	   }


}
		
