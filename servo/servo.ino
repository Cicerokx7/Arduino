#include <Servo.h>
Servo servo;

void setup() {
  servo.attach(3);
  //pinMode(5, OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
//  digitalWrite(2, HIGH);
  servo.write(120);
  delay(1000);
  servo.write(70);
  delay(1000);
  //50
  //30
  //0
  // put your main code here, to run repeatedly:

}
