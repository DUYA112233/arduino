#include "led.h"
#include "stm32f10x.h"

void LED_Init(void)
{
	
	
  GPIO_InitTypeDef GPIOC_date;	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE); //使能C口时钟
  
	GPIOC_date.GPIO_Mode=GPIO_Mode_Out_PP;               //设置推挽输出模式
	GPIOC_date.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_5;                      //初始化Pin5
	GPIOC_date.GPIO_Speed=GPIO_Speed_50MHz;              //设置时钟
	GPIO_Init(GPIOC,&GPIOC_date);                        //初始化IO口数据	
 	//GPIO_SetBits(GPIOC,GPIO_Pin_5);                      //选择哪个Pin口输出高电平
  GPIO_ResetBits(GPIOC,GPIO_Pin_6);
  GPIO_ResetBits(GPIOC,GPIO_Pin_5);
	

}
