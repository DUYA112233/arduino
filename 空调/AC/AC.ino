#include <IRremote.h>//红外发射模块接D3引脚
#include <MsTimer2.h>
#include <math.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT22
#define DHTPIN 6

DHT_Unified dht(DHTPIN, DHTTYPE);

IRsend irsend;
int red = 5;
int blue = 4;
int onOroff = 0;
unsigned int count = 0;
bool change = 0;
float bright;
float temp;
const unsigned int key_on[198]={6050,7300,550,1650,500,1700,500,1650,550,1600,550,1650,500,1650,550,1650,550,1600,500,650,500,600,550,550,550,550,550,600,550,550,500,650,500,600,550,1600,500,1700,550,1600,550,1600,550,1650,550,1650,550,1600,550,1650,500,600,500,600,550,600,550,550,550,550,550,550,550,600,500,600,550,1650,500,1650,550,1650,550,1600,500,1650,550,1650,550,1650,500,1650,500,600,500,650,500,600,550,550,550,550,600,550,550,600,450,650,500,1650,500,650,500,600,500,1650,500,650,500,600,500,600,550,1650,500,600,500,1700,500,1650,550,550,550,1650,550,1600,550,1650,500,600,500,1650,550,600,500,1650,550,550,550,1650,550,550,550,1650,550,1650,500,600,550,1600,500,650,500,1650,550,600,500,1650,550,550,550,600,500,600,500,1650,550,600,500,1650,550,600,500,1650,550,550,550,600,500,1650,550,550,550,1650,550,550,550,1650,550,550,550,1650,500,1650,500,7350,550};
const unsigned int key_off[198]={6000,7300,600,1600,550,1650,500,1650,550,1600,550,1650,500,1700,500,1650,550,1600,550,600,550,550,550,550,550,600,500,600,500,600,550,600,550,550,550,1650,500,1650,500,1650,550,1650,550,1600,500,1700,500,1650,550,1650,550,550,550,550,550,600,550,550,500,650,500,600,550,550,550,550,550,1650,550,1650,500,1650,550,1600,550,1650,500,1650,500,1700,550,1600,550,550,550,600,550,550,550,600,500,600,500,600,550,550,600,550,550,1600,550,1650,500,600,550,1650,500,600,500,600,550,600,550,1600,500,600,550,600,550,1600,550,600,550,1600,500,1650,550,1650,550,550,550,1650,550,550,550,1650,500,600,550,1650,450,650,500,1650,500,1650,600,550,550,1600,550,600,550,1600,550,550,600,1600,550,550,550,600,550,550,550,1600,550,600,550,1600,550,600,550,1600,550,550,550,600,550,1600,550,600,550,1600,550,550,550,1650,500,600,550,1650,500,1650,550,7300,550};
//编码部分

void setup(){
  Serial.begin(9600);
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);   //dht22
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  attachInterrupt(0, turn, RISING);  //上升沿触发
  // 中断设置函数，每 1s 进入一次中断
   MsTimer2::set(1000, flash);
   //开始计时
   MsTimer2::start();
}

void flash()  //定时中断读温度
{
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
  }                     
   bright = (analogRead(0)-9)/10;
   Serial.print("The bright is ");
   Serial.println(bright);
   if(onOroff == 0 && bright < 10)
   {
     if(temp > 30)
     {
       if(count < 300)
       {
         count++; 
       }
     } 
     else
     {
       if(count > 0)
       {
         count--;
       }
     } 
     if(count >= 300)
     {
       change = 1;
     } 
   }
   if(onOroff == 1 && bright < 10)
   {
     if(temp > 24)
     {
       if(count < 300)
       {
         count++; 
       }
     }
     else
     {
       if(count > 0)
       {
         count--;
       }
     }
     if(count <= 0)
     {
       change = 1;  
     }
   }
   Serial.print("The count is ");
   Serial.println(count);
}

void loop()
{ 
  if(change == 1 && onOroff == 0)
  {
    digitalWrite(red, HIGH);
    irsend.sendRaw(key_on,198,38);
    onOroff = 1;
    change = 0;
    Serial.print("The state is ");
    Serial.println(onOroff);
    delay(500);
    digitalWrite(red, LOW);
    MsTimer2::set(1000, flash);
    MsTimer2::start();
  }
  else if(change == 1 && onOroff == 1)
  {
    digitalWrite(blue, HIGH);
    irsend.sendRaw(key_off,198,38);
    onOroff = 0;
    change = 0;
    Serial.print("The state is ");
    Serial.println(onOroff);
    delay(500);
    digitalWrite(blue, LOW);
    MsTimer2::set(1000, flash);
    MsTimer2::start();
  }
}

void turn()
{
  change = 1;
}

