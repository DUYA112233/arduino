const int analogInPin = A0; // 模拟输入引脚
const int analogOutPin = 9; // PWM 输出引脚
int sensorValue = 0; // 电位器电压值
int outputValue = 0; // 模拟量输出值（PWM）
void setup() {
// 初始化串口参数
Serial.begin(9600);
}
void loop() {
// 读取模拟量值
sensorValue = analogRead(analogInPin);
// 变换数据区间
outputValue = map(sensorValue, 0, 1023, 0, 255);
// 输出对应的PWM 值
analogWrite(analogOutPin, outputValue);
// 打印结果到串口监视器
//这里可以使用arduino 自带的串口调试器，也可以使用德飞莱串口调试软件
//下载地址：http://doflye.net/viewthread.php?tid=4929
Serial.print("sensor = " );
Serial.print(sensorValue);
Serial.print("\t output = ");
Serial.println(outputValue);
// 等待2ms 进行下一个循环
// 取保能稳定读取下一次数值
delay(2);
}
