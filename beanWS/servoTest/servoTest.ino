#include <Servo.h>

Servo gripperServo;

//Gripper
const int GripperPartialOpen = 80;//70
const int GripperOpen = 165;//150
const int GripperClose = 60;//30
const int GripperFullClose = 60;//30

void setup() {
  gripperServo.attach(21);
}

void loop() {
//  gripperServo.write(GripperFullClose);
  gripperServo.write(GripperPartialOpen);
//  gripperServo.write(GripperOpen);
//  gripperServo.write(GripperClose);
}
