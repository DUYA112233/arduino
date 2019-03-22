float temp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = analogRead(1) * 5 * 100 /1024.00;
  Serial.print("The temperature is ");
  Serial.println(temp);
  if(temp > 26)
  {
    digitalWrite(7,HIGH);
  }
  else
  {
    digitalWrite(7,LOW);
  }
  delay(500);
}
