int sensorInPin = A5;//定义模拟接口0
 int ledPin=8;//定义数字接口8
 void setup()
{
pinMode(8,OUTPUT);//设置数字8 引脚为输出模式
Serial.begin(9600);//设置波特率为9600
}
void loop()
{
int i;//定义发量i
while(1)
{
i=analogRead(5);//读取模拟5 口电压值
Serial.println(i);//显示i变量
if(i>1000)//既倾斜传感器处于导通状态
{
digitalWrite(8,HIGH);//灯亮
}
else//否则
{
digitalWrite(8,LOW);//灯灭
}
}
}
