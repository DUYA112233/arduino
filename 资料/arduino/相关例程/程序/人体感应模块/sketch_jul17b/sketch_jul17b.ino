int ledPin = 13;       // led指示灯引脚
int inPin  = 12;       // 定义输入引脚
int buttonState;             // 读取的当前按键状态
void setup() {
  // 声明引脚为输出模式
  pinMode(ledPin, OUTPUT);  
  pinMode(inPin, INPUT);
}

void loop() {
   buttonState = digitalRead(inPin);
  if(buttonState == HIGH) //如果读入是高电平，说明有人进入区域 
  digitalWrite(ledPin, HIGH);  //吸合继电器
  delay(3000);          //延时1s    
  buttonState = digitalRead(inPin); 
  if(buttonState == LOW) //如果读入是低电平
  digitalWrite(ledPin, LOW);  //释放继电器  
}
