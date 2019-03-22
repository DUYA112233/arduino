/**
* @file         ra_parameter.h
* @brief        ������ȡ�����ӿ�
* @par Copyright (c):
*       Hangzhou District Nine Technology Co., Ltd.
*/

#ifndef __RA_PARAMETER_H__
#define __RA_PARAMETER_H__
#include "ra_types.h"

/** �����������Ͳ���
* @param[in]  key   ������
* @param[in]  value ����ֵ
* @retval	0       ���óɹ�
* @retval	-2      �ڴ����
* @retval	-3      ��������
*/
int ra_set_parameter_integer(const char *key, ra_int32_t value);

/** ��ȡ�������Ͳ���
* @param[in]  key   ������
* @param[out]  value   ����ֵ
* @retval	0       ��ȡ�ɹ�
* @retval	-1      �ڲ�����
*/
int ra_get_parameter_integer(const char *key, ra_int32_t *value);

/** �����ַ������Ͳ���
* @param[in]  key   ������
* @param[in]  value ����ֵ
* @retval	0       ���óɹ�
* @retval	-2      �ڴ����
* @retval	-3      ��������
*/
int ra_set_parameter_string(const char *key, const char *value);

/** ��ȡ�ַ������Ͳ���
* @param[in]  key   ������
* @param[out]  buf  ������
* @param[in]  buf_len  ����������(����������)
* @retval	��0     valueʵ�ʳ���
* @retval	-1      �ڲ�����
* @retval	-3      ��������
*/
int ra_get_parameter_string(const char *key, char *buf, ra_size_t buf_len);

/** ɾ������
* @param[in]  key   ������
* @retval	0       ��ȡ�ɹ�
* @retval	-2      �ڴ����
* @retval	-3       ��������
*/
int ra_delete_parameter(const char *key);

#endif