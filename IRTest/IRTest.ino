

void setup() {
  pinMode(3, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(3, HIGH);
  delay(50);
  if(digitalRead(A0) == HIGH){
    digitalWrite(13, HIGH);
    Serial.println("ON!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  }
  digitalWrite(3, LOW);
  delay(50);
  Serial.println("end");
}
