int sensorInPin = A0;//定义模拟接口0
int LEDPin=6;//定义数字接口6
int sensorValue = 0;// 模拟输入变量
void setup()
{
pinMode(LEDPin,OUTPUT);//定义数字接口6 为输出
Serial.begin(9600);//设置波特率为9600
//注意：模拟接口自动设置为输入
}
void loop()
{
sensorValue=analogRead(sensorInPin);// 读取传感器的模拟值并赋值给val
Serial.println(sensorValue);//显示val 变量
analogWrite(LEDPin,sensorValue);// 
delay(10);//延时时间用来控制串口监视器数据刷新快慢，可自行设置
}
