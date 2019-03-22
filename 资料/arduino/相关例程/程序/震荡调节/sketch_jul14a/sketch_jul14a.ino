int sensorPin = A0; // 模拟输入引脚
int ledPin = 13; // led 指示灯引脚
int sensorValue = 0; // 模拟输入数值变量
void setup() {
// 声明引脚为输出模式
pinMode(ledPin, OUTPUT);
}
void loop() {
// 读取电位器电压值
sensorValue = analogRead(sensorPin);
// 点亮led，LY-51S 独立模块开发板上led 模块则是熄灭led
digitalWrite(ledPin, HIGH);
// 使用读取的这个模拟量值作为演示时间，单位ms，范围0-1023
delay(sensorValue);
// 熄灭led，LY-51S 独立模块开发板上led 模块则是点亮led
digitalWrite(ledPin, LOW);
// 使用读取的这个模拟量值作为演示时间，单位ms，范围0-1023
delay(sensorValue);
}
