#include <LiquidCrystal.h>
#include "DHT.h"

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define DHTPIN 7
#define DHTTYPE DHT22
#define relayPIN 8
#define touchPIN 18

float hum,tem;
int state = 1;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(relayPIN,OUTPUT);
  pinMode(touchPIN,INPUT);
  attachInterrupt(5, openLCD, CHANGE);
  digitalWrite(relayPIN,LOW);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.setCursor(2, 0);
  lcd.print("hello, world!");
  lcd.setCursor(3, 1);
  lcd.print("o_0****0_o");
  dht.begin();
  delay(2000);
  digitalWrite(relayPIN,HIGH);
  lcd.clear();
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  getdata();
  printdata();
  delay(1000);
}

void getdata()
{
  hum = dht.readHumidity();
  tem = dht.readTemperature();
}

void printdata()
{
  lcd.setCursor(2, 0);
  lcd.print("Hum:");
  lcd.print(hum);
  lcd.print("%");
  lcd.setCursor(2, 1);
  lcd.print("Tem:");
  lcd.print(tem);
  lcd.print("*C");
}

void openLCD()
{
  state = !state;
  digitalWrite(relayPIN,state);
}

