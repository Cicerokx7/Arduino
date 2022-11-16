#include <Servo.h>

Servo servo;

void setup() {
  pinMode(2, OUTPUT);
  servo.attach(5);

}

void loop() {
  digitalWrite(2, LOW);
  servo.write(0);

}
