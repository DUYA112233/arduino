const int ledPin=12;
int ledState=LOW;
long previousMills=0;
long interval=500;
void setup(){
  pinMode(ledPin,OUTPUT);
}
void loop(){
  unsigned long currentMills=millis();
  if(currentMills-previousMills>interval){
    previousMills=currentMills;
    if(ledState==LOW)
    ledState=HIGH;
    else
    ledState=LOW;
    digitalWrite(ledPin,ledState);
    }
  }

