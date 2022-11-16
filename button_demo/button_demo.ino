void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

digitalWrite(2, LOW);
digitalWrite(3, LOW);
}

void loop() {
  digitalWrite(2, HIGH);
  delay(15);
  digitalWrite(2, LOW);
  delay(200);
  digitalWrite(3, HIGH);
  delay(15);
  digitalWrite(3, LOW);
  delay(3000);

}
