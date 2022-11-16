#include <HCSR04.h>

UltraSonicDistanceSensor rightSensor(16, 19);
UltraSonicDistanceSensor frontSensor(15, 21);
UltraSonicDistanceSensor leftSensor(14, 20);
UltraSonicDistanceSensor backSensor(17, 18);

int rightFMotor = 4;
int rightBMotor = 9;
//int leftMotor[2] = {7, 8};
int leftFMotor = 7;
int leftBMotor = 8;
int pwmpin[2] = {6, 5};
int pwmR = 6;
int pwmL = 5;
int i = 0;
int frontS = 0;
int rightS = 0;
int leftS = 0;
int backS = 0;
int r = 0;
int l = 0;
int lD = 0;
int lllD = 0;
int lDP = 0;
int lllDP = 0;
int pathag = 0;
int test = 0;
int lP = 0;
int lllP = 0;
int lC = 0;
int lllC = 0;
int front = 0;
void setup() {
 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(13, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
  Serial.begin(9600);
}

void loop() {
    frontS = frontSensor.measureDistanceCm();
  rightS = rightSensor.measureDistanceCm();
  leftS = leftSensor.measureDistanceCm();
  backS = backSensor.measureDistanceCm();
  if(frontS&&rightS&&leftS&&backS){
 lDP = frontS+backS;
 lllDP = rightS+leftS;
 lllD = sq(lDP)+sq(lllDP);
 pathag = lD+lllDP;
          digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, 15);
    analogWrite(pwmL, 21);
 //    Serial.println(lllDP);
 Serial.println(leftS);
  }
delay(1000);
}
