#include <Servo.h>

Servo gripper;

int gripperClose = 130;
int gripperOpen = 80;

void setup() {
  gripper.attach(9);

}

void loop() {
  gripper.write(gripperClose);
  delay(1000);
  gripper.write(gripperOpen);
  delay(1000);
}
