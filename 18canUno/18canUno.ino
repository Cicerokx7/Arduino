#include <Servo.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

Servo gripper;

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11);

#include <Stepper.h>

const float STEPS_PER_REV = 32;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV*GEAR_RED;
int StepsRequired;
short wormGearPointer = 0;
//Stepper wormGearOne(STEPS_PER_REV, 38, 42, 40, 44);
Stepper stick(STEPS_PER_REV, 2, 3, 4, 5);

#include <HCSR04.h>

UltraSonicDistanceSensor distance(14, A7);

void printResult(HUSKYLENSResult result);

int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;

int gripperClose = 80; 
int gripperOpen = 60;

int mode = 0;
int canW = 0;
int spedeor = 70;
int spedeol = 50;
int rspeder = 21;
int rspedel = 21;
int trigger = 0;
int high = 10;
int low = 100;
int can = 0;

bool right = true;
bool good = false;

int stepsArm = 28;
int stepsFire = 4;

void setup() {
       
  // put your setup code here, to run once:
 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
Serial.begin(9600);
mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    gripper.attach(8);
    //flag.attach(12);
    gripper.write(gripperOpen);
    delay(1000);
    stick.setSpeed(300);
    stick.step(stepsArm);
//flag.write(low);
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
String readString;
String Q;

//-------------------------------Check Serial Port---------------------------------------
 while (Serial.available()) {
      delay(1);
    if (Serial.available() > 0) {
      char c = Serial.read();//gets one byte from serial buffer
    if (isControl(c)) {
      //'Serial.println("it's a control character");
      break;
    }
      readString += c; //makes the string readString    
    }
 }   

 Q = readString;
 Serial.println("on");
 if(mode == 0){
  if(Q != "good"){
//    Serial.println("on");
  }
  else{
    mode = 1;
  }
 }
 if(Q == "good"){
  good = true;
 }
 else{
  good = false;
 }
  if(mode == 1){
        if (!huskylens.request()) Serial.println(F("nothing"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing"));
    else if(!huskylens.available()){
      spedeor = 25;
                 spedeol = 25;
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
    else
    {
while (huskylens.available()){
           HUSKYLENSResult result = huskylens.read();
                          mode = 2;
            if(result.width < 220){
              if(result.width < 200){
                 spedeor = 45;
                 spedeol = 45;
              }
              if(result.width > 200){
                 spedeor = 45;
                 spedeol = 45;
              }
            if(result.xCenter > 170){
          //    Serial.println("test");
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}

if(result.xCenter < 100){
  //Serial.println("test");
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}
if(result.xCenter > 100 && result.xCenter < 170){
   //Serial.println("test");
  digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}
            }
if(result.width > 220){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    gripper.write(gripperClose);
      mode = 3;
}
        }
    }
  }
  if(mode == 3){ 
  if(right){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
  }
  else{
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
  }
  if(good){
    mode = 4;
    }
  }
  if(mode == 4){
    if(right){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
  }
  else{
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
  }
  if(good == false){
    right = !right;
    mode = 3;
  }
  if(good && distance.measureDistanceCm() < 0){
    stick.step(stepsFire);
    gripper.write(gripperOpen);
    delay(1000);
    stick.step(stepsArm);
    mode = 1;
  }
  }
}
