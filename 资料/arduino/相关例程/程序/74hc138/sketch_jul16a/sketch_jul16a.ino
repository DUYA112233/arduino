//int 74HC138_A = 2;
//int 74HC138_B = 3;
//int 74HC138_C = 4;

int segCount = 3;
int segPins[] = { 
  2,3,4 };   // A,B,C

void setup() {
// 循环设置，把对应的端口都设置成输出
  for (int thisSeg = 0; thisSeg < segCount; thisSeg++) {
    pinMode(segPins[thisSeg], OUTPUT); 

  }
}
// 数据处理，把需要处理的byte数据写到对应的引脚端口。
void deal(unsigned char value){
 for(int i=0;i<3;i++)
   digitalWrite(segPins[i],bitRead(value,i));//使用了bitWrite函数，非常简单
   // !bitRead(value,i)，这里前面加！(非运算符号)，取决于使用的是共阴还是共阳数码管。
}
// 主循环
void loop() {
  // 循环输出0-7，在138的输出端是Y0-Y7依次为0,138任何时刻只有1个脚为低电平。
  for(int i=0;i<8;i++){
     deal(i);//
   delay(1000);//延时1秒
   }
  }
