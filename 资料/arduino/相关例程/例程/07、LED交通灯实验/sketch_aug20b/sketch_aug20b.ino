int redled =10; //定义数字10 接口
int yellowled =7; //定义数字7 接口
int greenled =4; //定义数字4 接口
void setup()
{
pinMode(redled, OUTPUT);//定义红色小灯接口为输出接口
pinMode(yellowled, OUTPUT); //定义黄色小灯接口为输出接口
pinMode(greenled, OUTPUT); //定义绿色小灯接口为输出接口
}
void loop()
{
digitalWrite(greenled, HIGH);////点亮 绿灯
delay(5000);//延时5秒
digitalWrite(greenled, LOW); //熄灭 绿灯
for(int i=0;i<3;i++)//闪烁交替三次，黄灯闪烁效果
{
delay(500);//延时0.5 秒 
digitalWrite(yellowled, HIGH);//点亮  黄灯
delay(500);//延时0.5 秒
digitalWrite(yellowled, LOW);//熄灭  黄灯
} 
delay(500);//延时0.5 秒
digitalWrite(redled, HIGH);//点亮 红灯
delay(5000);//延时5 秒
digitalWrite(redled, LOW);//熄灭 红灯
}
