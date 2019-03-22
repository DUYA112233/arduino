int hycgInPin = A5;//定义模拟接口0
int Beep=8;//定义蜂鸣器接口为数字8 接口
int val=0;
void setup()
{
pinMode(8,OUTPUT);//设置数字8 引脚为输出方式
pinMode(hycgInPin,INPUT);
Serial.begin(9600);//设置波特率为9600
}
void loop()
{
  int i;//定义发量i
while(1)
{
i=analogRead(5);//读取模拟5 口电压值
Serial.println(i);//显示i 变量
if(i>800)//如果大于51
{
digitalWrite(8,LOW);//蜂鸣器发声
}
else//否则
{
digitalWrite(8,HIGH);//蜂鸣器不发声
}
}
  }

