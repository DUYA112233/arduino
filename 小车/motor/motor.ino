
#define PinA 2 //数字端口2是Arduino的外部中断0的端口
#define PinB 3 //数字端口3是Arduino的外部中断1的端口

float PerRound = 1768; //减速比为34的电机ab相共同输出时1768次电平变换为一圈

int E =5; //连接小车电机的PWM控制端口到数字接口5
int M =4; //连接小车电机的dir控制端口到数字接口4

float PWM=150;//设置电机初始PWM功率值

int flag;   //暂存变量，用于Arduino接受Andriod手机的控制字符
long count = 0;  //定义编码器码盘计数值（此编码器转一圈发出334个脉冲）
float rpm = 0;    //每分钟(min)转速(r/min)
unsigned long time = 0, old_time = 0;// 时间标记
 
//初始化
void setup()
{
  Serial.begin(9600);    // 启动串口通信，波特率9600b/s
  pinMode(M, OUTPUT);   //直流电机驱动板的控制端口设置为输出模式
  pinMode(E, OUTPUT);
  pinMode(PinA,INPUT); //伺服电机编码器的OUTA和OUTB信号端设置为输入模式
  pinMode(PinB,INPUT);
  //定义外部中断的中断子程序Code(),中断触发为下跳沿触发
  //当编码器码盘的正交编码板OUTA脉冲信号发生下跳沿中断时，
  //将自动调用执行中断子程序Code()。
  attachInterrupt(0, Code,CHANGE);
  attachInterrupt(1, Code,CHANGE);
}
//对直流电机驱动板的使能端口和转向端口进行设置，以使小车
//执行前进、后退、左转、右转、停止和速度切换动作。
void advance()//小车前进
{ 
     digitalWrite(M,HIGH);
     analogWrite(E,PWM/24*25); //前进转的会慢一点，纠正误差
}
void back()//小车后退
{    
     digitalWrite(M,LOW);
     analogWrite(E,PWM);
}

void Stop()//小车停止
{
     digitalWrite(E, LOW); //右电机停
}  
//主程序
void loop()
{
  //如果Arduino控制器读缓冲区中存在Andriod手机下达的字符命令
  if (Serial.available()>0)
  {    
      flag = Serial.read(); //读出Arduino控制器读缓冲区的字节
      delay(5);    
      if(flag =='a')      //如果读出的字节为“前进”标志字符'a'
      {            
         Stop();           //小车先暂停
         delay(10);
         advance();      //小车再前进
         count = 0; //恢复小车编码器初始计数状态
         old_time=  millis();   
       }
       else if( flag =='b') //如果读出的字节为“后退”标志字符'b'   
       {                
         Stop();        //小车先暂停
         delay(10);
         back();           //小车再后退
         count = 0;  //恢复小车编码器初始计数状态
         old_time=  millis();       
       }                   
      else if(flag=='m')
      {
        PWM=200;    //小车行驶速度切换为高速状态
        count = 0;  //恢复小车编码器初始计数状态
        old_time=millis(); 
      }
      else if(flag=='n')
      {
        PWM=150;   //小车行驶速度切换为低速状态
        count = 0;  //恢复小车编码器初始计数状态
        old_time=millis(); 
      }
      else if(flag=='s') //如果读出的字节为“停止”标志字符's'
      {
        Stop();        //小车停止 
      }
    } 
 
  time = millis();//以毫秒为单位，计算当前时间
  //计算出每0.5秒钟内，编码器码盘计得的脉冲数，
  if(abs(time - old_time) >= 1000) // 如果计时时间已达0.5秒
  {
    detachInterrupt(0); // 关闭外部中断0
    detachInterrupt(1);
     //此直流减速电机的编码器码盘为334个齿，减速比为34。
    //把编码器每0.5秒钟计得的脉冲数，换算为当前转速值的计算式 
    rpm =(float)count/PerRound*60;   
    Serial.println(rpm);
    Serial.println(count);
//根据刚刚调节后的小车电机PWM功率值，
//及时修正小车前进或者后退状态，以使小车走直线
    if(flag=='a')
    advance();
    if(flag=='b')
    back();     
    count = 0;   //把脉冲计数值清零，以便计算下一个0.5秒的脉冲计数
    old_time=  millis();     // 记录每次0.5秒测速后的时间节点    
    attachInterrupt(0, Code,CHANGE); // 重新开放外部中断0
    attachInterrupt(1, Code,CHANGE);
  }
}
 
//右侧电机编码器码盘计数中断子程序
void Code()
{  
  count += 1; // 编码器码盘计数加一 
}
