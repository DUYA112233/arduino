int get_num;
float vol;
int last_num;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  get_num = analogRead(A5);
  if(get_num > 890) return;  //大于4.35V认为异常
  if(get_num != last_num)
  {
    last_num = get_num;
    vol = get_num * 5.0 / 1023.0;
    Serial.print(vol);
    Serial.println("V$");
  }
  delay(500);
}
