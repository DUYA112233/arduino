const int ledCount=8;
int ledPins[]={
  0,1,2,3,4,5,6,7,
  };
  void setup(){
    for(int thisLed=0;thisLed<ledCount;thisLed++){
      pinMode(ledPins[thisLed],OUTPUT);
      }
    }
    void loop(){
      for(int num=0;num<8;num++){
        digitalWrite(ledPins[num],LOW);
        delay(200);
        digitalWrite(ledPins[num],HIGH);
        }
      }
