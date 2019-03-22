/**
************************************************************
* @file         Gizwits + ArduinoUnoR3 Library 
* @brief        Datapoints handle , Gizwits Process
* @author       Gizwits
* @date         2017-08-01
* @version      V03030000
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#include "Gizwits.h"
#include <Wire.h>

Gizwits myGizwits;

/**
* Serial Init , Gizwits Init  
* @param none
* @return none
*/
void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  myGizwits.begin();

  Serial.println("GoKit init  OK \n");

}

/**
* Arduino loop 
* @param none
* @return none
*/
void loop() {  
  
  //Configure network
  //if(XXX) //Trigger Condition
  myGizwits.setBindMode(0x02);  //0x01:Enter AP Mode;0x02:Enter Airlink Mode
  bool varR_AC_OnOff = 0;
  if(myGizwits.hasBeenSet(EVENT_AC_OnOff))
  {
    myGizwits.read(EVENT_AC_OnOff,&varR_AC_OnOff);//Address for storing data
    Serial.println(F("EVENT_AC_OnOff"));
    Serial.println(varR_AC_OnOff,DEC);

  }


  //binary datapoint handle

  myGizwits.process();
}
