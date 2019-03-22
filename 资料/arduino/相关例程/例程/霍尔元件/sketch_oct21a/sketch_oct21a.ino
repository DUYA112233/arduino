void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int temp = analogRead(A5);
  Serial.println(temp);
  delay(200);
}
