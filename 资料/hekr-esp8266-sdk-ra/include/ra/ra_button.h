/**
* @file         ra_button.h
* @brief        �����ӿ�
* @par Copyright (c):
*       Hangzhou District Nine Technology Co., Ltd.
*/

#ifndef __MODULE_KEY_H__
#define	__MODULE_KEY_H__
#include "ra_types.h"
#include <ra_gpio.h>
/**
* ra_button_pressed_callback_t ���������ص�����ԭ�Ͷ���
*/
typedef void(*ra_button_pressed_callback_t)(void);

/**
* ע�ᰴ���жϴ�����
* @param[in]	pin					�����ܽ����
* @param[in]	irq_type			gpio�ж�����
* @param[in]	long_pressed_threshold		������ֵ�����룩
* @param[in]	short_pressed_callback	�̰�������ָ��
* @param[in]	long_pressed_callback	����������ָ��
* @retval		0	�ɹ�
* @retval		-1	ʧ��
*/
int ra_register_button_irq_handler(
	ra_uint8_t pin,
	ra_gpio_irq_type_t irq_type,
	ra_size_t long_pressed_threshold,
	ra_button_pressed_callback_t short_pressed_callback,
	ra_button_pressed_callback_t long_pressed_callback);
#endif