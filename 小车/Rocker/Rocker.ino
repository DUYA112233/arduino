#include <Servo.h>
Servo myservo;

#define SERVOPIN   3   //转向舵机控制口

#define SERVOMIN 90
#define SERVOMID 110        //the angle of servo
#define SERVOMAX 130
#define TURNLEFT myservo.write(SERVOMIN)  //turn left
#define TURNMID myservo.write(SERVOMID)   //turn middle
#define TURNRIGHT myservo.write(SERVOMAX)  //turn right

bool EnableRockerR = 1;
bool EnableRockerL = 1;
int RMid = 0 ;
int LStop = 0 ;

void setup() 
{
  Serial.begin(9600);
  myservo.attach(SERVOPIN);
  TURNMID;                     // Servo middle
  Serial.println("set up over");
}

  /***********************************************************************
   Rocker program
   Through the rocker arm around before and after the change of
   resistance for motor speed control
   Up and Left（0 - 127）
   Down and Right （129 - 255）
   摇杆比例控制程序
      通过摇杆前后左右阻值的变化实现电机转速控制
      上左范围（0 - 127） 
      下右范围（129 - 255）
***********************************************************************/
/*
void serialEvent()
{
   if (Serial.read() == 'l') //Left pressed
  {            
    Serial.println("turn left");        //will be TRUE if button was JUST pressed
    TURNLEFT;
    EnableRockerR = 0;
  } 

  else if (ps2x.ButtonReleased(PSB_SQUARE)) //Left released
  {    
    Serial.println("Square just released");       //will be TRUE if button was JUST released
    TURNMID;
    EnableRockerR = 1;
    RMid = 0;
  }

  
  else if (Serial.read() == 'r') //Right pressed
  {             
    Serial.println("turn right");  //will be TRUE if button was JUST pressed
    TURNRIGHT;
    EnableRockerR = 0;
  } 
  /*
  else if (ps2x.ButtonReleased(PSB_CIRCLE)) //Right released
  {     
    Serial.println("Circle just released");
    TURNMID;
    EnableRockerR = 1;
    RMid = 0;
  }
  */

/*
  if (EnableRockerL) //Left and Right
  {
    if (0 <= ps2x.Analog(PSS_LY) && ps2x.Analog(PSS_LY) <= 115) 
    {
      digitalWrite(DIR, LOW);
      analogWrite(PWM, map(ps2x.Analog(PSS_LY), 0,115,255,0));
      LStop = 0;
    } 
    else if (255 >= ps2x.Analog(PSS_LY) && ps2x.Analog(PSS_LY) >= 140) 
    {
      digitalWrite(DIR, HIGH);
      analogWrite(PWM, map(ps2x.Analog(PSS_LY), 140,255,0,255));
      LStop = 0;
    } 
    else 
    {
      if(LStop == 0)
      {
        MOTORSTOP;
        LStop ++;
      }
    }
  }
  
  if (EnableRockerR) 
  {                              
    if (0 <= ps2x.Analog(PSS_RX) && ps2x.Analog(PSS_RX) <= 115) 
    {
      myservo.write(map(ps2x.Analog(PSS_RX), 0, 115, 40,88));
      RMid = 0;
    } 
    else if (255 >= ps2x.Analog(PSS_RX) && ps2x.Analog(PSS_RX) >= 140) 
    {
      myservo.write(map(ps2x.Analog(PSS_RX), 140, 255, 92,120));
      RMid = 0;
    }
    else 
    {
      if(RMid == 0)
      {
        TURNMID;
        RMid ++;
      }
    }
  }

  if (ps2x.NewButtonState(PSB_CROSS)) //Stop
  {             
    Serial.println("X just changed");              //will be TRUE if button was JUST pressed OR released
    MOTORSTOP;
  }
  delay(50);
}
*/

/*
 *  输入字符串，确定从第几位开始解析后面多少位
 *  input:需解析的字符串
 *  Matching:匹配样本
 *  num_start:从第几位开始解析（第一位为字符串开始）
 *  flag:输出1为匹配成功，0为失败
 */
bool AnalysisGetString(String input, String Matching, int num_start)
{
  bool flag = 1;
  int len = Matching.length();
  for(int i = 0; i < len; i++)
  {
    if(input[num_start+i-1] != Matching[i])
    {
      flag = 0;
      break;
    }
    else continue;
  }
  return flag;
}

void loop() 
{
  if (Serial.available())
  {
    char c = Serial.read(); //读取一字节数据
    if (c == 'l') //Left pressed
    {            
       Serial.println("turn left");
      TURNLEFT;
    } 
    else if (c == 'r') //Right pressed
    {             
      Serial.println("turn right");
      TURNRIGHT;
    } 
    else if (c == 'm') //Right pressed
    {             
      Serial.println("turn middle");
      TURNMID; 
    } 
  }
}
