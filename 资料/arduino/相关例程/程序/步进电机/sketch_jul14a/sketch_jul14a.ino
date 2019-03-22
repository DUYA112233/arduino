#include <Stepper.h>
// change this to the number of steps on your motor
#define STEPS 512
// 定义引脚的连接
Stepper stepper(STEPS, 8, 10, 9, 11);
//上一次的读取模拟量
int previous = 0;
//初始化电机转动速度
void setup()
{
stepper.setSpeed(20);
}
//主循环
void loop()
{
// 读取AD 值，在LY-51S 可以直接通过电位器调节
int val = analogRead(0);
// 把速度设置为这次和上次读取的差值
stepper.step(val - previous);
// 记下这次读取值，方便下次比较
previous = val;
}
