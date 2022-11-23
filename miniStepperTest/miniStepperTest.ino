 #include <Stepper.h>

const float STEPS_PER_REV= 32;

const float GEAR_RED = 64;

const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

int StepsRequired;

Stepper steppermotor(STEPS_PER_REV, 38, 42, 40, 44);

void setup() {
  delay(15000);

}

void loop() {
  StepsRequired = STEPS_PER_OUT_REV;
  steppermotor.setSpeed(300);//1100
  steppermotor.step(-StepsRequired/2);
  delay(1000);
  steppermotor.step(-StepsRequired/2);
  delay(5000);

}
