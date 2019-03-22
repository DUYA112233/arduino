int pushButton = 2;
int led = 13;
void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(led, OUTPUT);
}
void loop() 
{
  int buttonState = digitalRead(pushButton);
  digitalWrite(led, buttonState);
  Serial.println(buttonState);
  delay(10);
  }
