#include "sys.h"
#include "usart.h"	
#include "lcd.h"
#include "delay.h"
#include "string.h" 	 
#include "esp8266.h"
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
////////////////////////////////////////////////////////////////////////////////// 	  
 

/////////////////////////////////////////////////////////////////  
unsigned char Message_length;
int OneNet_Connect=0;      //�����ж�wifiģ���Ƿ�������OneNetƽ̨�ı�־

char Rx_Buff[200];
int  Rx_count=0;   //����ESP8266�жϽ������ݵĶ���
int ok_flag=0;
char Message_Buf[20];  //���ڴ�������ָ��
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  

//��ʼ��IO ����1 
//bound:������*/
void uart_init(u32 bound)
	{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1);  //��λ����1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;	
	static int i;
//		if(AT_Mode==0)        
//		Rx_count=0;
		
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
	    	Res =USART_ReceiveData(USART1);//(USART1->DR);	//��ȡ���յ�������	
				Rx_Buff[Rx_count]=Res;
    if(AT_Mode==1)			                         //����wifiģ�鷢ATָ��ʱ��ģʽ
		{
			if(strstr(Rx_Buff,"OK")||strstr(Rx_Buff,">"))    //�ж�ESP8266�Ƿ񷵻�OK
			{
				 memset(Rx_Buff, 0, sizeof(Rx_Buff));  //���Rx_Buff����
         ok_flag=1;			 
         Rx_count=0;				
			}
			else                                   //���������������
			{
						Rx_count++;	
					if(Rx_count==150)                   //���������������� �����������
						{
								Rx_count=0;
					    memset(Rx_Buff, 0, sizeof(Rx_Buff));
						}
			}
		}
			else if(AT_Mode==0)               //���տ���ָ��ģʽ
			{
					 	
					if(Rx_count==150)                   //���������������� �����������
						{
								Rx_count=0;                  //���´�����[0]��ʼ��������
					    memset(Rx_Buff, 0, sizeof(Rx_Buff));  //��յ�ǰ������������
						}
					    ok_flag=1;                         //�ñ�־���ڷ�ATָ������в��õ� ������SendCmd()�����в鿴������ ����ATָ������״̬
						
						if(Message_length>0)                   //��ʾ���Կ�ʼ��������ָ��
						 {
						    Message_Buf[i]=Rx_Buff[Rx_count];   //��������ָ������
							  i++;
						    Message_length--;                  //��һ��ָ�ʣ��������һ,�жϲ���ָ���Ƿ�������
						 }
						 
						if(Rx_count>3&&Rx_Buff[Rx_count-2]==0&&Rx_Buff[Rx_count-1]==0&&Rx_Buff[Rx_count]>0)   
						//�����ǰ���յ������ݴ���0������������ݵ�ǰ��������Ϊ00 ����ǰ���ݾ��ǲ���ָ��ĳ��ȡ�
						{
							 memset(Message_Buf, 0, sizeof(Message_Buf)); //��մ�������ָ������飬׼�������µĲ���ָ��
							
						   Message_length=Rx_Buff[Rx_count];      //�����յ������ݴ�Ϊ����ָ��ȡ�
							 i=0;                                   //���i
						}
						Rx_count++;                               //׼���洢��һ������ 
						
			 }
           
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		 }	 
		
		 
		/**********�ж�WiFiģ���Ƿ�������OneNet ƽ̨*******/
		 {
		  if(Rx_Buff[Rx_count-3]==0x20&&Rx_Buff[Rx_count-2]==0x02&&Rx_Buff[Rx_count-1]==0x00&&Rx_Buff[Rx_count]==0x00)  //������ƽ̨ʱ ƽ̨�᷵�� 20 02 00 00������
			{
			     OneNet_Connect=1;         //������ɵı�־λ
			
			}
		 }
		 if(Rx_Buff[Rx_count-2]==0x64&&Rx_Buff[Rx_count-1]==0x01&&Rx_Buff[Rx_count]==0x60)  //������ƽ̨ʱ ƽ̨�᷵�� 20 02 00 00������
			{
			     OneNet_Connect=0;         //���ӶϿ�
			
			}
		 
} 

