#include <Servo.h>
Servo myservo;
int pos = 0; // 用于存储舵机位置的变量
//初始化
void setup()
{
myservo.attach(9); // 舵机控制信号引脚
}
void loop()
{
for(pos = 0; pos < 180; pos += 1) // 从0 度-180 度
{ // 步进角度1 度
myservo.write(pos); // 输入对应的角度值，舵机会转到此位置
delay(15); // 15ms 后进入下一个位置
}
for(pos = 180; pos>=1; pos-=1) // 从180 度-0 度
{
myservo.write(pos); // 输入对应的角度值，舵机会转到此位置
delay(15); // 15ms 后进入下一个位置
}
}
