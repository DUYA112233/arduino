int sensorInPin = A0; // 模拟输入引脚
int jdqPin = 12;//jdq控制引脚
int sensorValue = 0; // 模拟输入数值变量
void setup() {
// 声明引脚为输出模式
Serial.begin(9600);
pinMode(jdqPin,OUTPUT);
}
void loop() {
// 读取光敏电压值
sensorValue = analogRead(sensorInPin);
if(sensorValue>150){//热敏数值可自行修改
  digitalWrite(jdqPin,HIGH);
  }
  else{digitalWrite(jdqPin,LOW);}
Serial.println(sensorValue);
delay(sensorValue);
}
