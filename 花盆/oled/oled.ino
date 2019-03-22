#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#include "DHT.h"
//#include <TimeLib.h>

U8G2_SSD1306_128X64_NONAME_1_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
#define DHTPIN 6
#define DHTTYPE DHT22
float soil_V, soil_hum;
float hum, tem;
unsigned long time_day;
double min = 300;  //全湿300
double max = 1023; //全干待测
DHT dht(DHTPIN, DHTTYPE);

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g2.setFont(u8g_font_unifont);
  u8g2.drawStr(0, 16, "Soil-Hum");
  u8g2.setCursor(76, 16);
  u8g2.print(soil_hum);
  u8g2.drawStr(116, 16, "%");
  u8g2.drawStr(0, 32, "Air-Hum");
  u8g2.setCursor(68, 32);
  u8g2.print(hum);
  u8g2.drawStr(108, 32, "%");
  u8g2.drawStr(0, 48, "Air-Hum");
  u8g2.setCursor(68, 48);
  u8g2.print(tem);
  u8g2.drawStr(108, 48, "C*");
  u8g2.setFont(u8g2_font_ncenB10_tr);
  u8g2.drawStr(28, 64, "DAY");
  u8g2.setCursor(76, 64);
  u8g2.print(time_day);
}

void getdata()
{
  soil_V = analogRead(A0);
  soil_hum = (1023-soil_V)/(max-min)*100;
  hum = dht.readHumidity();
  tem = dht.readTemperature();
  time_day = (millis()/1000)/86400+1;
}

void setup(void) {
  u8g2.begin();
}

void loop(void) {
  // picture loop
  getdata();
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  // rebuild the picture after some delay
  delay(1000);
}
