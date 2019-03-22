#ifndef __LED_H_
#define __LED_H_

#define LED_set GPIOC   //宏定义LED灯的高低电平

#define LED GPIO_Pin_6    

#define LED_H  LED_set->BSRR=LED
#define	LED_L  LED_set->BRR=LED	

void LED_Init(void);


#endif

