int InPin=4;
int OutPin=13;
void setup ()
{
pinMode(4,INPUT);//将4号数字口设置为输入状态，13号数字口设置为输出状态
pinMode(13,OUTPUT);
Serial.begin(9600);//设置波特率为9600
}
void loop()
{
int n = digitalRead(4);//创建一个变量n，将4号数字口的状态采集出来赋值给他。
Serial.println(n);//显示n变量
if (n==HIGH)//判断n是否为高电平，如果是执行下面的语句，不是则跳过。
{
digitalWrite(13,HIGH);
delay(5000);//延时，让灯多亮会。
digitalWrite(13,LOW);
}
}
