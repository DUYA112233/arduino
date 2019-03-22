int redpin=11;//定义LED接口
int bluepin=10;
int greenpin=9;
int redval;//定义LED变量
int blueval;
int greenval;
int i=0;
void setup()
{
  pinMode(redpin,OUTPUT);//设置LED接口为输出接口
  pinMode(bluepin,OUTPUT);
  pinMode(greenpin,OUTPUT);  
  pinMode(redval,INPUT);//设置LED变量为输入值
  pinMode(blueval,INPUT);
  pinMode(greenval,INPUT);
  Serial.begin(9600);//连接到串行端口，波特率为9600
}
void loop()
{
  i++;
if(i<200)
{
  redval+=1;//红灯变亮
  greenval-=1;//绿灯变暗
  blueval=1;//黄灯不变
}
else if(i<400)
{
   redval-=1;//红灯变暗
  greenval=1;//绿灯不变
  blueval+=1;// 黄灯变亮
}
else if(i<600)
{
   redval=1;//红灯不变
  greenval+=1;//绿灯变亮
  blueval-=1; //黄灯变暗
}
else
{
  i=0;//重新给i赋值进行新循环
}
analogWrite(redpin,redval);//给LED接口付模拟值
analogWrite(bluepin,blueval);
analogWrite(greenpin,greenval);
Serial.print(i,DEC);//显示出i的值
Serial.print(   "     R:");//分别显示出各个LED的模拟值
Serial.print(redval,DEC);
Serial.print(    "    B:");
Serial.print(blueval,DEC);
Serial.print(    "    G:");
Serial.println(greenval,DEC);
}
