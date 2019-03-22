#include "led.h"
#include "stm32f10x.h"

void LED_Init(void)
{
	
	
  GPIO_InitTypeDef GPIOC_date;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //ʹ��C��ʱ��
  
	GPIOC_date.GPIO_Mode=GPIO_Mode_Out_PP;               //�����������ģʽ
	GPIOC_date.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_5;                      //��ʼ��Pin5
	GPIOC_date.GPIO_Speed=GPIO_Speed_50MHz;              //����ʱ��
	GPIO_Init(GPIOC,&GPIOC_date);                        //��ʼ��IO������	
 	//GPIO_SetBits(GPIOC,GPIO_Pin_5);                      //ѡ���ĸ�Pin������ߵ�ƽ
  GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	

}
