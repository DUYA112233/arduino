 int buzzer=8;//设置控制蜂鸣器的数字8 脚
void setup()
{
pinMode(buzzer,OUTPUT);//设置数字IO 脚模式，OUTPUT 为输出
}
void loop()
{
unsigned char i,j;//定义发量
while(1)
{
for(i=0;i<80;i++)//输出一个频率的声音
{
digitalWrite(buzzer,HIGH);//发声音
delay(1);//延时1ms
digitalWrite(buzzer,LOW);//不发声音
delay(1);//延时1ms
}
for(i=0;i<100;i++)//输出另一个频率的声音
{
digitalWrite(buzzer,HIGH);//发声音
delay(2);//延时2ms
digitalWrite(buzzer,LOW);//不发声音
delay(2);//延时2ms
}
}
}

