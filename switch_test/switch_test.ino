int switchPin = 9;
int swich = 0;

void setup() {
  pinMode(switchPin, INPUT);
Serial.begin(9600);
pinMode(13, OUTPUT);
}

void loop() {
  swich = digitalRead(switchPin);
Serial.println(swich);
if(swich == HIGH)
digitalWrite(13, HIGH);
else
digitalWrite(13,LOW);

}
