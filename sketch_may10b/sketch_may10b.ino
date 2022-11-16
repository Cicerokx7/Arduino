void setup() {
  // put your setup code here, to run once:
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);

}

void loop() {
  digitalWrite(3,HIGH);
  delay(100);
  digitalWrite(3, LOW);
  delay(3000);

}
