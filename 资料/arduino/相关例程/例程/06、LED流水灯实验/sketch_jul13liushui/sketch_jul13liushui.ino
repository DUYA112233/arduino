const int ledCount=6;
int ledPins[]={ 2,3,4,5,6,7};
  void setup(){
    for(int thisLed=0;thisLed<ledCount;thisLed++){
      pinMode(ledPins[thisLed],OUTPUT);
      }
    }
    void loop(){
      for(int num=0;num<6;num++){
        digitalWrite(ledPins[num],LOW);
        delay(200);
        digitalWrite(ledPins[num],HIGH);
        }
      }
