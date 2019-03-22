const unsigned char
dofly_DuanMa[16]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
int CLK = 2;
int DAT = 3;//A or B
void setup() {
// 循环设置，把对应的端口都设置成输出
pinMode(CLK, OUTPUT);
pinMode(DAT, OUTPUT);
Serial.begin(9600);
}
void SendByte(unsigned char dat)
{
static unsigned char i;
for(i=0;i<8;i++)
{
digitalWrite(CLK,0);
digitalWrite(DAT,bitRead(dat,7-i));//高位先输出。这里也可以用arduino 自带的
digitalWrite(CLK,1);
}
}
// 主循环
void loop() {
// 循环显示0-9 数字
for(int i=0;i<16;i++){
SendByte(dofly_DuanMa[i]);
delay(1000); //调节延时，2 个数字之间的停留间隔
}
}
