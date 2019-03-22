void setup() {
// 初始化串口参数，这里仅仅作为调试使用
Serial.begin(9600);
}
void loop() {
// 从传感器读入模拟量数据
int sensorReading = analogRead(A0);
// 打印这个数据到串口以便能知道数据的具体数值
Serial.println(sensorReading);
// 把读入的模拟量(这种情况下, 光敏电阻读出值400 - 1000 )
// 换算出频率范围(120 - 1500Hz)
// 根据实际传感器的参数改变下面的最大值和最小值
int thisPitch = map(sensorReading, 400, 1000, 120, 1500);
// 播放对应频率的声音
tone(9, thisPitch, 10);
delay(1); // 延时，等待数据稳定后读取
}
