int ledCount=8;
int segCount=4;
long previousMillis = 0;
const unsigned char
dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int ledPins[] = {
12,8,5, 3, 2, 11, 6, 4, };
int segPins[]={13,10,9,7};
unsigned char displayTemp[4];//显示缓冲区
void setup() {
// 循环设置，把对应的端口都设置成输出
for (int thisLed = 0; thisLed < ledCount; thisLed++) {
pinMode(ledPins[thisLed], OUTPUT); }
for (int thisSeg = 0; thisSeg < segCount; thisSeg++) {
pinMode(segPins[thisSeg], OUTPUT);
}
}
void deal(unsigned char value){
for(int i=0;i<8;i++)
digitalWrite(ledPins[i],bitRead(value,i));//使用了bitWrite 函数，非常简单
// !bitRead(value,i)
}
void loop() {
static unsigned int num;//定义一个数据
static unsigned long lastTime=0;
if (millis() - lastTime >= 1000) {
lastTime = millis();
//serialOutput();
num++;
}
displayTemp[0]=dofly_DuanMa[1]; //静态显示
displayTemp[1]=dofly_DuanMa[2];
displayTemp[2]=dofly_DuanMa[3];
displayTemp[3]=dofly_DuanMa[4];
static int i;
unsigned long currentMillis = millis();
if(currentMillis - previousMillis > 0) {
previousMillis = currentMillis;
deal(0);// 清除“鬼影”
for(int a=0;a<4;a++)
digitalWrite(segPins[a],1);//
digitalWrite(segPins[i],0);//
deal(displayTemp[i]);//读取对应的段码值
i++;
if(i==4) //4 位结束后重新循环
i=0;
}
}
