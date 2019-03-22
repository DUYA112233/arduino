#define RELAY 50

char temp = "";

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0)
  {
    temp = Serial.read();
    Serial.println(temp);
    if(temp == 'o')  digitalWrite(RELAY,LOW);
    else if(temp == 'e')  digitalWrite(RELAY,HIGH);
  }
}
