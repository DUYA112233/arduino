/**
* @file         ra_gpio.h
* @brief        gpio��ؽӿ�
* @par Copyright (c):
*       Hangzhou District Nine Technology Co., Ltd.
*/

#ifndef __RA_GPIO_H__
#define __RA_GPIO_H__
#include "ra_types.h"

/**
* IO�������ƽ״̬
*/
typedef enum
{
	/** �͵�ƽ */
	RA_GPIO_LOW = 0,
	/** �ߵ�ƽ */
	RA_GPIO_HIGH = 1
} ra_gpio_state_t;//�ߵ͵�ƽ 


/**
* ra_gpio_int_type_t ö�����Ͷ���
*/
typedef enum
{
	RA_GPIO_IRQ_TYPE_DISABLE = 0,
	RA_GPIO_IRQ_TYPE_POSEDGE,
	RA_GPIO_IRQ_TYPE_NEGEDGE,
	RA_GPIO_IRQ_TYPE_ANYEGDE,
	RA_GPIO_IRQ_TYPE_LOLEVEL,
	RA_GPIO_IRQ_TYPE_HILEVEL
} ra_gpio_irq_type_t;

typedef enum
{
	RA_GPIO_DIRECTION_INPUT,
	RA_GPIO_DIRECTION_OUTPUT,
} ra_gpio_direction_t;

/**
* ra_gpio_irq_callback_t ����ԭ�Ͷ���
*/
typedef void(*ra_gpio_irq_callback_t)(ra_uint8_t pin, void *arg);

/**
* ����IO�������ƽ
* ����IO������߻��ߵ͵�ƽ
* @param[in]	pin		����
* @param[in]	value	��ƽ
*/
void ra_gpio_output(ra_uint8_t pin, ra_gpio_state_t value);

/**
* ��ȡ��ǰIO�������ƽ
* @param[in]   pin �߼��ܽźš�
* @retval		��ƽ
*/
ra_gpio_state_t ra_gpio_input(ra_uint8_t pin);

/**
* GPIO�ж�ע�ắ��
* @param[in]	pin		����
* @param[in]	type
* @param[in]	callback
* @retval
*/
int ra_gpio_irq_register_callback(
	ra_uint8_t pin,
	ra_gpio_irq_type_t type,
	ra_gpio_irq_callback_t callback,
	void *arg);

/**
* GPIOģʽ����
* @param[in]	pin		����
* @param[in]	mode
* @retval
*/
void ra_gpio_set_direction(ra_uint8_t pin, ra_gpio_direction_t direction);

/**
* GPIO��������ʹ��
* @param[in]	pin		����
* @param[in]	enabled  ʹ��
* @retval
*/
void ra_gpio_set_pullup(ra_uint8_t pin, ra_bool enabled);


#endif