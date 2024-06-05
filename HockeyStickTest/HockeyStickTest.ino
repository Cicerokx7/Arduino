#include <Stepper.h>

const float STEPS_PER_REV = 32;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV*GEAR_RED;
int StepsRequired;
short wormGearPointer = 0;
//Stepper wormGearOne(STEPS_PER_REV, 38, 42, 40, 44);
Stepper capDispenser(STEPS_PER_REV, 2, 4, 3, 12);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  capDispenser.setSpeed(50);
  StepsRequired = STEPS_PER_OUT_REV;
  capDispenser.step(-StepsRequired);
  delay(1000);
}
