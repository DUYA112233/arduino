/**
************************************************************
* @file         Gizwits + ArduinoUnoR3 Library
* @brief        Gizwits Process , Protcol Transformation
* @author       Gizwits
* @date         2017-08-01
* @version      V03030000
* @copyright    Gizwits
*
* @note         鏈烘櫤浜�.鍙负鏅鸿兘纭欢鑰岀敓
*               Gizwits Smart Cloud  for Smart Products
*               閾炬帴|澧炲�贾祙寮�鏀緗涓珛|瀹夊叏|鑷湁|鑷敱|鐢熸��
*               www.gizwits.com
*
***********************************************************/
#include "Gizwits.h"
#include <Arduino.h>


#define ESP8266WIFI Serial1
dataPoint_t currentDataPoint;
wifiStatueFlags_t wifiStatueFlags;


Gizwits::Gizwits()
{
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
}

Gizwits::~Gizwits()
{
	return;
}

void Gizwits::begin(void)
{
	ESP8266WIFI.begin(9600);
	gizwitsInit();
}

/**
* @brief ESP8266WIFI write , Send to wifi module
*
* @param buf      : Input data
* @param len       : data length
*
* @return : Success,payload length
*			-1锛孍rror
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;

    if(NULL == buf)
    {
        return -1;
    }

    for(i=0; i<len; i++)
    {
        ESP8266WIFI.write(buf[i]);
        if(i >=2 && buf[i] == 0xFF)
        {
            ESP8266WIFI.write(0x55);
        }
    }
    return len;
}

/*void ESP8266WIFIEvent(void)
{
	uint8_t value = 0;
	value = (unsigned char)ESP8266WIFI.read();
	gizPutData(&value, 1);
}*/


/**
* @brief Get package , Handle Protocol Data
*
*
* @return : Null
*/
void Gizwits::process(void)
{
	uint8_t readChar = 0;
    uint16_t i=0,num = 0;
    num = ESP8266WIFI.available();
    if(0 < num)
    {
        for(i=0; i<num; i++)
        {
            readChar = ESP8266WIFI.read();
            gizPutData(&readChar, 1);
        }

    }
	gizwitsHandle((dataPoint_t *)&currentDataPoint);
}

bool Gizwits::wifiHasBeenSet(EVENT_TYPE_T eventType)
{
	bool flag;
	switch(eventType)
	{
			case WIFI_SOFTAP:
				flag = 	wifiStatueFlags.flagWifi_softap;
				wifiStatueFlags.flagWifi_softap = 0;
			break;
			case WIFI_AIRLINK:
				flag = 	wifiStatueFlags.flagWifi_airlink;
				wifiStatueFlags.flagWifi_airlink = 0;
			break;
			case WIFI_STATION:
				flag = 	wifiStatueFlags.flagWifi_station;
				wifiStatueFlags.flagWifi_station = 0;
			break;
			case WIFI_CON_ROUTER:
				flag = 	wifiStatueFlags.flagWifi_con_router;
				wifiStatueFlags.flagWifi_con_router = 0;
			break;
			case WIFI_DISCON_ROUTER:
				flag = 	wifiStatueFlags.flagWifi_discon_router;
				wifiStatueFlags.flagWifi_discon_router = 0;
			break;
			case WIFI_CON_M2M:
				flag = 	wifiStatueFlags.flagWifi_con_m2m;
				wifiStatueFlags.flagWifi_con_m2m = 0;
			break;
			case WIFI_DISCON_M2M:
				flag = 	wifiStatueFlags.flagWifi_discon_m2m;
				wifiStatueFlags.flagWifi_discon_m2m = 0;
			break;
			default:
			break;
	}

	return flag;
}

void Gizwits::setBindMode(uint8_t mode)
{
	gizwitsSetMode(mode);
}


/** The Structure of the current device status **/
attrFlags_t attrFlags;

/**
* @brief Get Datapoint Value

* Description:

* Get Value From currentDataPoint
* @param [in] eventType: event queue
* @param [in] value: Dest , Type In bool/uint32_t/int32_t/float/uint8_t(for binary)
* @return NULL
* @ref Gizwits.h
*/
void Gizwits::read(EVENT_TYPE_T eventType, bool* value)
{
	switch(eventType)
	{
	      case EVENT_AC_OnOff:
	        *value = currentDataPoint.valueAC_OnOff;
	        break;
		default:
			break;
	}

	return;
}

void Gizwits::read(EVENT_TYPE_T eventType, uint32_t* value)
{
	switch(eventType)
	{
		default:
			break;
	}

	return;
}
void Gizwits::read(EVENT_TYPE_T eventType, int32_t* value)
{
	switch(eventType)
	{
		default:
			break;
	}

	return;
}
void Gizwits::read(EVENT_TYPE_T eventType, float* value)
{
	switch(eventType)
	{
		default:
			break;
	}

	return;
}

void Gizwits::readBinary(EVENT_TYPE_T eventType, uint8_t* data)
{
	switch(eventType)
	{
		default:
			break;
	}

	return;
}

/**
* @brief Check datapoint event is or not happen

* Description:

* @param [in] eventType: event queue
* @return 1,This datapoint event happen
*		  0,This datapoint event is not happen
* @ref Gizwits.h
*/
bool Gizwits::hasBeenSet(EVENT_TYPE_T eventType)
{
	bool flag;
	switch(eventType)
	{
			case EVENT_AC_OnOff:
				flag = 	attrFlags.flagAC_OnOff;
				attrFlags.flagAC_OnOff = 0;
				break;
		default:
			break;
	}

	return flag;
}

/**
* @brief Write Datapoint Value

* Description:

* Write value to currentDataPoint
* @param [in] eventType: event queue
* @param [in] value: Source value , Type In bool/uint32_t/int32_t/float/uint8_t(for binary)
* @return NULL
* @ref Gizwits.h
*/
void Gizwits::write(VALUE_TYPE_T valueType, bool value)
{
	switch(valueType)
	{
		default:
			break;
	}
	return;
}

void Gizwits::write(VALUE_TYPE_T valueType, uint32_t value)
{
	switch(valueType)
	{
		default:
			break;
	}

	return;
}
void Gizwits::write(VALUE_TYPE_T valueType, int32_t value)
{
	switch(valueType)
	{
		default:
			break;
	}

	return;
}
void Gizwits::write(VALUE_TYPE_T valueType, float value)
{
	switch(valueType)
	{
		default:
			break;
	}

	return;
}
void Gizwits::writeBinary(VALUE_TYPE_T valueType, uint8_t* data,uint32_t dataLen)
{
	switch(valueType)
	{
		default:
			break;
	}

	return;
}


/**
* @brief Read ms timer

* @param none
* @return System Millisecond
*/
uint32_t gizGetTimerCount(void)
{
  return millis();
}
