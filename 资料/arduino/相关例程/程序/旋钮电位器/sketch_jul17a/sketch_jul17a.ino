const int analogInPin = A0;  // 模拟输入引脚
int sensorValue = 0;        // 电位器电压值
void setup()
{// 初始化串口参数
  Serial.begin(9600); 
}
void loop() {
  // 读取模拟量值
  sensorValue = analogRead(analogInPin);
 // 打印结果到串口监视器
 Serial.println(sensorValue); 
}

