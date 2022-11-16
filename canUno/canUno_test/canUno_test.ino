#include <Servo.h>

Servo gripper;
Servo flag;

void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
      pinMode(7, OUTPUT);
        pinMode(8, OUTPUT);
gripper.attach(3);
flag.attach(11);
}

void loop() {
          analogWrite(5, 75);
          analogWrite(6, 100);
  // put your main code hee, to run repeatedly:
  delay(2000);
digitalWrite(4, HIGH);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
  delay(2000);
digitalWrite(4, LOW);
digitalWrite(7, HIGH);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
  delay(2000);
digitalWrite(4, LOW);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
  delay(50);
digitalWrite(4, LOW);
digitalWrite(7, LOW);
digitalWrite(8, HIGH);
digitalWrite(9, LOW);
delay(2000);
digitalWrite(4, LOW);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
  delay(50);
digitalWrite(4, LOW);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
digitalWrite(9, HIGH);
delay(2000);
digitalWrite(4, LOW);
digitalWrite(7, LOW);
digitalWrite(8, LOW);
digitalWrite(9, LOW);
  delay(50);
gripper.write(50);
delay(2000);
gripper.write(80);
delay(2000);
flag.write(180);
delay(2000);
flag.write(70);

}
