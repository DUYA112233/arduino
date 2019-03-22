int inf[4] = {8,9,10,11}; //四个检测高度红外对射
int button = 12;          //检测红外是否处于工作状态的红外对射
const int Trig = 4;       //超声波发射
const int Echo = 5;       //超声波接收
int motorPin[4] = {2,3,6,7};  //步进电机
const int led = 13;       //显示是否复位

void setup() {
  Serial.begin(9600);
  for(int i = 0 ; i < 4 ; i++)
  {
    pinMode(inf[i], INPUT);
    pinMode(motorPin[i], OUTPUT);
  }
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(led, OUTPUT);
}

int bottle_flag = 0;    //检测到杯子在直到杯子被拿走变回0
int t = 0;              //多t后才算正式触发（保护机制）
int m = 0;              //检测空杯（不用）
int start_flag = 0;     //标记是否已经开始放水
int flag;               //第几个红外被触发
int dis;                //水面与超声波高度
float last_dis;         //记录上次成功测到的dis
float remain_dis;       //剩余安全高度
int max_flag = -1;      //记录杯子高度
int motorSpeed = 1200;  //步进速度
int count = 0;          // 计算累积步数
int lookup[8] = {B01000, B01100, B00100, B00110,
B00010, B00011, B00001, B01001};//步进电机参数
char input;

/******************************************
*扫描红外对射端口是否触发，返回触发端口序号
*/

int scan()
{
  if(digitalRead(button) == HIGH)
  {
    for(int i = 0 ; i < 4 ; i++)
    {
      if(digitalRead(inf[i]) == LOW)
      {
        return i;
      }
    }
    return 6;    //6表示没有杯子
  }
  else return 5; //5表示红外不在工作
}

/******************************************
*超声波检测水面高度
*/
float wave()
{
  digitalWrite(Trig,LOW);
  delayMicroseconds(2);
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  dis = pulseIn(Echo,HIGH)/58.00;
  if(dis == 0 || dis > 25) return last_dis;
  else
  {
    last_dis = dis;
    return dis;
  }
}

/******************************************
*无杯子时的待机状态
*/

int no_bottle()
{
  flag = scan();
  while(flag != 6 && flag != 5)
  {
    flag = scan();
    if(max_flag < flag) max_flag = flag;
    if(start_to_end() != 1) t++;
    Serial.print(flag);
    Serial.print("\t");
    Serial.println(t);
    if(t > 3)
    {
      t = 0;
      return 1;
    }
    delay(200);
  }
  if(flag == 5)
  {
    t = 0;
    Serial.println("off");
    delay(200);
    return no_bottle();
  }
  else if(flag == 6)
  {
    t = 0;
  }
  return 0;
}

/******************************************
*加水过程中的控制停水
*/
int start_to_end()
{
  dis = wave();
  Serial.print("\t");
  Serial.print("dis = ");
  Serial.println(dis);
  remain_dis = dis - (6.5+3.5*max_flag);
  Serial.print("remain_dis = ");
  Serial.println(remain_dis);
 // if(re() == 1) return 2;
  if(remain_dis <= 0)
  {
    max_flag = -1;
    return 1;
  }
  else
  {
    return 0;
  }
}

/******************************************
*步进电机一步函数
*/

void setOutput(int out)
{
  for(int i = 0 ; i < 4 ; i++)
    digitalWrite(motorPin[i], bitRead(lookup[out], i));
}

/******************************************
*步进电机顺时针转动，输入转动圈数
*/

void clockwise(double r)
{
  while(count < r*512)
  {
    for(int i = 7; i >= 0; i--)
    {
      setOutput(i);
      delayMicroseconds(motorSpeed);
    }
    count++;
  }
  count = 0;
}

/******************************************
步进电机逆时针转动，输入同上*/

void anticlockwise(double r)
{
  while(count < r*512)
  {
    for(int i = 0; i < 8; i++)
   {
      setOutput(i);
      delayMicroseconds(motorSpeed);
   }
   count++;
  }
  count = 0;
}

/******************************************
 * 点击
 */

 void Click(double num)
 {
  anticlockwise(num);
  delay(500);
  clockwise(num);
 }

/******************************************
 * 检测是否回到检测空杯状态
 */

 int re()
 {
  if(dis >= 21 && dis <= 23) m++;
  if(m >= 3)
  {
    m = 0;
    return 1;
  }
  else return 0;
 }


/******************************************
*主程序
*/

void loop() {
  
  input = Serial.read();
  if(input == '1')
     Click(0.08);
  else if(input == '2')
    clockwise(0.08);
  else if(input == '3')
    anticlockwise(0.08);
    /*
  if(no_bottle() == 0)
  {
    digitalWrite(led, HIGH);
    delay(200);
    return;
  }
  else
  {
    bottle_flag = 1;
    if(!start_flag && start_to_end() == 0 && bottle_flag == 1)
    {
      Serial.println("start");
      start_flag = 1;
      Click(0.08);
    }
  }
  while(start_to_end() == 0 && bottle_flag == 1)
  {
    delay(200);
  }
  if(start_flag)
  {
    Serial.println("end");
    bottle_flag = 0;
    start_flag = 0;
    Click(0.08);
    max_flag = -1;
  }
  digitalWrite(led, LOW);
  delay(5000);
  return;
  */
}
