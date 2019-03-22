#include <LiquidCrystal.h>//调用库文件
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//用到的的IO口
void setup() {
// 设置行列值
lcd.begin(16, 2);//16列，2行。1602 液晶可以显示2 行，每行显示16 个字符。
// 打印字符串
lcd.print("hello,YOUCHUANG!");//可自行输入想要的显示
}
void loop() {
// 设置光标到第二行第一列
// (注意：1 表示第二行，从0 开始数):
lcd.setCursor(0, 1);
// 打印复位后的运行秒值
lcd.print(millis()/1000);
lcd.print(" Second");
}
