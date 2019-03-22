double getdata;
double min = 300;  //全湿300
double max = 1023; //全干待测

void setup() {
  Serial.begin(9600);
}

void loop() {
  getdata = analogRead(A0);
  Serial.print("Vol: ");
  Serial.println(getdata);
  Serial.print("Per: ");
  getdata = (1023-getdata)/(max-min)*100;
  if(getdata > 100) getdata = 100;
  else  if(getdata < 0) getdata = 0;
  Serial.print(getdata);
  Serial.println(" %");
  Serial.println();
  delay(1000);

}
