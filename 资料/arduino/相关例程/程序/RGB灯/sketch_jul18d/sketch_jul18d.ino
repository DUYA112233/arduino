int redPin = 11;  // R 红色LED 控制引脚 连接到Arduino的 11脚 
int greenPin = 9;  // G绿色LED 控制引脚 连接到Arduino的 9脚
int bluePin = 10;  // B蓝色LED 控制引脚 连接到Arduino的 11脚   
void setup()    
{   
     pinMode(redPin, OUTPUT); //设置redPin对应的管脚11为输出
     pinMode(greenPin, OUTPUT); //设置greenPin,对应的管脚9为输出
     pinMode(bluePin, OUTPUT); //设置bluePin对应的管脚10为输出
}    
       
void loop()  // run over and over again  
{    
     // Basic colors:  
    color(255, 0, 0); // 红色亮
    delay(1000); // 延时一秒 
    color(0,255, 0); //绿色亮
delay(1000); //延时一秒
color(0, 0, 255); // 蓝色灯亮  
    delay(1000); //延时一秒
     
  // Example blended colors:  
    color(255,255,0); // 黄色  
    delay(1000); //延时一秒
  color(255,255,255); // 白色  
    delay(1000); //延时一秒
  color(128,0,255); // 紫色  
    delay(1000); //延时一秒
    color(0,0,0); // t关闭led  
    delay(1000); //延时一秒  
}     
    
void color (unsigned char red, unsigned char green, unsigned char blue)  //颜色控制函数 
{    
      analogWrite(redPin, 255-red);   
      analogWrite(greenPin, 255-green); 
      analogWrite(bluePin,255-blue);
}
