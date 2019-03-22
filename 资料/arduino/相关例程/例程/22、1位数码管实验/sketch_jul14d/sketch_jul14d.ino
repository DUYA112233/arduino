int ledCount=8;
const unsigned char
dofly_DuanMa[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int ledPins[] = {0,1,2, 3, 4, 5, 6, 7, };
void setup()
{
  for (int thisLed = 0; thisLed < ledCount; thisLed++)
   {
    pinMode(ledPins[thisLed], OUTPUT);
    }
  }
  void deal(unsigned char value)
  {
    for(int i=0;i<8;i++)
digitalWrite(ledPins[i],bitRead(value,i));
    }
    void loop()
    {
      for(int i=0;i<10;i++)
    {
      deal(dofly_DuanMa[i]);
      delay(1000);
      }
      }

