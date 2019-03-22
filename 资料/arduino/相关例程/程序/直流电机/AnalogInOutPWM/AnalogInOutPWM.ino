/*
 http://shop34791330.taobao.com/ //德飞莱旗舰店
 http://qixingchong.tmall.com/   //七星虫旗舰店
 http://www.doflye.net //德飞莱技术论坛
 http://www.doflye.net/forum-98-1.html //德飞莱论坛arduino版块
 
 通过检测电位器的模拟电压值，通过串口反映出对应的数字量，然后把
 数据变化到0-255区间，使用PWM引脚调节led亮度或者电机速度

 如果使用LY-51S独立模块开发板，参考以下链接：
 http://www.doflye.net/thread-5295-1-1.html
 
 
 */

// 引脚定义
const int analogInPin = A0;  // 模拟输入引脚
const int analogOutPin = 9; //  PWM输出引脚

int sensorValue = 0;        // 电位器电压值
int outputValue = 0;        // 模拟量输出值（PWM）

void setup() {
  // 初始化串口参数
  Serial.begin(9600); 
}

void loop() {
  // 读取模拟量值
  sensorValue = analogRead(analogInPin);            
  // 变换数据区间
  outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // 输出对应的PWM值
  analogWrite(analogOutPin, outputValue);           

  // 打印结果到串口监视器
  //这里可以使用arduino自带的串口调试器，也可以使用德飞莱串口调试软件
  //下载地址：http://doflye.net/viewthread.php?tid=4929
  Serial.print("sensor = " );                       
  Serial.print(sensorValue);      
  Serial.print("\t output = ");      
  Serial.println(outputValue);   

  // 等待2ms进行下一个循环
  // 取保能稳定读取下一次数值
  delay(2);                     
}
