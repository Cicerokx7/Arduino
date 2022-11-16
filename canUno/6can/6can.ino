#include <HCSR04.h>

UltraSonicDistanceSensor gripperSensor(16, A7);
UltraSonicDistanceSensor rightSensor(15, 21);
UltraSonicDistanceSensor leftSensor(14, 20);

//int rightMotor[2] = {4, 9};
int rightFMotor = 4;
int rightBMotor = 9;
//int leftMotor[2] = {7, 8};
int leftFMotor = 7;
int leftBMotor = 8;
int pwmpin[2] = {6, 5};
int pwmR = 6;
int pwmL = 5;
int i = 0;
int rightS = 0;
int leftS = 0;
int gripperS = 0;
int r = 0;
int l = 0;


void setup() {
 // pinMode(rightMotor[r], OUTPUT);
 // pinMode(leftMotor[l], OUTPUT);
 // pinMode(pwmpin[i], OUTPUT);
 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(13, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
  Serial.begin(9600);

}
//128
void loop() {
  rightS = rightSensor.measureDistanceCm();
  leftS = leftSensor.measureDistanceCm();
//  gripperS = gripperSensor.measureDistanceInch();
  if(rightS < 5 || rightS > 396){
    if(leftS < 5 || leftS > 396){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 35);
    analogWrite(pwmL, 25);//140%
    Serial.print("go");
    Serial.print(rightS);
    Serial.print("/");
    Serial.println(leftS);
  }
  }
  /*
  if(rightS > 5 && rightS < 330){
    if(leftS > 5 && leftS < 330){
   // r = 0;
   // l = 1;
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, 25);
    analogWrite(pwmL, 35);
    Serial.println("right");
    Serial.print(rightS);
    Serial.print("/");
    Serial.print(leftS);
  }
  }
  */
  else{
   // r = 0;
   // l = 1;
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, 28);
    analogWrite(pwmL, 20);
    Serial.println("right");
    Serial.print(rightS);
    Serial.print("/");
    Serial.print(leftS);
  }
  Serial.print(rightS);
    Serial.print("/");
    Serial.print(leftS);
  //  digitalWrite(rightMotor[r], HIGH);
   // digitalWrite(leftMotor[l], HIGH);
   
}
