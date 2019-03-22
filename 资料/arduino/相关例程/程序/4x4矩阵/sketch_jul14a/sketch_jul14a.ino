const int numRows = 4;//定义4 行
const int numCols = 4;//定义4 列
const int debounceTime = 20;//去抖动时间长度
const char keymap[numRows][numCols]= {//键值，可以按需要更改
{ '1','2','3','A' },
{'4','5','6','B' },
{'7','8','9','C' },
{'*','0','#','D' }
};
const int rowPins[numRows] = {4,5,6,7};//设置硬件对应的引脚
const int colPins[numCols] = {8,9,10,11};
//初始化功能
void setup(){
Serial.begin(9600);
for(int row = 0; row < numRows; row++){
pinMode(rowPins[row],INPUT);
digitalWrite(rowPins[row],HIGH);
}
for(int column = 0;column < numCols; column++){
pinMode(colPins[column],OUTPUT);
digitalWrite(colPins[column],HIGH);
}
}
//主循环
void loop() {
// 添加其他的程序，循环运行
char key = getkey();
if(key !=0)
{
Serial.print("Got key ");//串口打印键值
Serial.println(key);
}
}
//读取键值程序
char getkey(){
char key = 0;
for(int column = 0;column < numCols; column++){
digitalWrite(colPins[column],LOW);
for(int row = 0 ;row < numRows; row++){
if(digitalRead(rowPins[row]) == LOW){ //是否有按键按下
delay(debounceTime);
while(digitalRead(rowPins[row]) == LOW)
;//等待按键释放
key = keymap[row][column];
}
}
digitalWrite(colPins[column],HIGH); //De-active the current column
}
return key;
}
