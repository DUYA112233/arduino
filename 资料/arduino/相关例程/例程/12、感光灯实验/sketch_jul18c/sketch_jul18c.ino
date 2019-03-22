int potpin=0;//定义模拟接口0 连接光敏电阻
int ledpin=11;//定义数字接口11 输出PWM 调节LED 亮度
int val=0;//定义变量val
void setup()
{
pinMode(ledpin,OUTPUT);//定义数字接口11 为输出
Serial.begin(9600);//设置波特率为9600
}
void loop()
{
val=analogRead(potpin);//读取传感器的模拟值并赋值给val
Serial.println(val);//显示val 变量数值
analogWrite(ledpin,val);// 打开LED 并设置亮度（PWM 输出最大值255）
delay(10);
}
