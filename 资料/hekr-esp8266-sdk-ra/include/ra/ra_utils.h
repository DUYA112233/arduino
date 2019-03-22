/**
* @file         ra_utils.h
* @brief        ͨ�ýӿ�
* @par Copyright (c):
*       Hangzhou District Nine Technology Co., Ltd.
*/

#ifndef __RA_UTILS_H__
#define __RA_UTILS_H__
#include "ra_types.h"

/**
* ͨ�����ͻص�ԭ��
*/
typedef void(*ra_callback_t)(void *arg);

/**
* SDK��ʼ��
*/
void ra_init(void *arg);

/**
* ��ѯϵͳʣ����� heap ���ռ��С
* @retval	ra_uint32_t	���� heap �ռ��С
*/
ra_uint32_t ra_get_free_heap_size(void);

/**
* ��ѯϵͳʱ��
* @retval	ra_uint32_t	ϵͳ�ϵ�ʱ�䣬���ϵ�����ѯʱ�̵�ʱ�䣨΢�룩
*/
ra_uint32_t ra_get_system_uptime(void);

/**��ѯdevTid
* @retval	��NULL devTid
* @note ������Ҫfree
*/
char *ra_get_devtid(void);

/** �ָ�������Ĭ������
* @note ���WIFI���ã�����������ģʽ
*/
void ra_restore_to_factory_default_settings(void);

/** ϵͳ����
*/
void ra_system_reboot(void);

/** WIFI����
@retval	0	���߳ɹ�
@retval	-1	����ʧ��
*/
int ra_wifi_sleep(void);

/** WIFI����
*/
void ra_wifi_wakeup(void);

/**
* ע��ϵͳ��ʼ����ɵĻص�����
* @param[in]	cb	�ص�����
* @param[in]	arg	�ص������Ĳ���
* @retval	��
* @note		ra_disconnect_wifi()����ϵͳ��ʼ����ɺ����
*/
void ra_register_system_init_done_callback(ra_callback_t cb, void *arg);

/**
* ���ù̼���ǰ�汾��
* @param[in]	version	�汾�ţ���ʽΪ"xx.xx.xx.xx"���磺"4.1.1.1"
* @retval	0 ���óɹ�
* @retval	-1 ����ʧ��
* @note		version�汾�Ÿ�ʽ������"xx.xx.xx.xx"��Ҫ��ȻӰ��OTA����
*/
int ra_set_current_firmware_version(char *version);

/**
* ��ѯ�̼���ǰ�汾��
* @retval	'A'	��ǰ�̼�������A��
* @retval	'B'	��ǰ�̼�������B��
*/
char ra_get_current_firmware_type(void);
#endif