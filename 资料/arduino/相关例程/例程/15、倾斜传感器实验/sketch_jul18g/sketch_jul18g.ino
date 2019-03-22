 int qxInPin =6;//定义模拟接口0
 int ledPin=8;//定义数字接口8
  void setup()
{
Serial.begin(9600);
pinMode(8,OUTPUT);//设置数字8 引脚为输出模式
pinMode(6,INPUT);
}
void loop()
{
int i;//定义发量i
{while(1)
i=digitalRead(6);//读取模拟5 口电压值
Serial.println(i);//(digitalRead);
delay(100);
if(i=HIGH)//(digitalRead>512)//如果大于512（2.5V）
{
  delay(500);
  if(i=HIGH);//(digitalRead>512){
digitalWrite(8,HIGH);//点亮led 灯
}
else//否则
{
digitalWrite(8,LOW);//熄灭led 灯
}
}
}
