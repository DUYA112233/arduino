int led = 9; // led 引脚定义，这里需要使用有PWM 功能的引脚
int brightness = 0; // led 亮度
int fadeAmount = 5; // 调节的单步间隔
// 初始化
void setup() {
// led 引脚定义位输出
pinMode(led, OUTPUT);// 独立模块LY-51S 开发板上LED1-LED8 都可以使用。
}
// 主循环
void loop() {
// 设置了led 的亮度
analogWrite(led, brightness);
//下一个循环调整led 亮度
brightness = brightness + fadeAmount;
// 到最大值后反向调整
if (brightness == 0 || brightness == 255) {
  fadeAmount = -fadeAmount ;
}
// 等待30ms
delay(30);
}


