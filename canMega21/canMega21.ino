#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>
#include <Servo.h>
//#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include <Stepper.h>
#include <HCSR04.h>
#include <Pixy2.h>

Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

Servo gripper;

Pixy2 pixy;

//HUSKYLENS huskylens;
//SoftwareSerial mySerial(10, 11);

UltraSonicDistanceSensor distance(13, A7);

//#define LSM9DS1_SCK A5
//#define LSM9DS1_MISO 12
//#define LSM9DS1_MOSI A4
//#define LSM9DS1_XGCS 6
//#define LSM9DS1_MCS 5

double z = 0;
int angle = 0;
int fullAngle = 680;
int minAngle = 0;
int maxAngle = fullAngle/2;

int mode = 1;

int counter = 0;

const float STEPS_PER_REV = 32;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV*GEAR_RED;
int StepsRequired;
short wormGearPointer = 0;
//Stepper wormGearOne(STEPS_PER_REV, 38, 42, 40, 44);
Stepper stick(STEPS_PER_REV, 2, 4, 3, 12);

//void printResult(HUSKYLENSResult result);

int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;

int gripperClose = 120; 
int gripperOpen = 20;

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

int stepsArm = -28*64;
int stepsFire = -4*64;

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G, lsm.LSM9DS1_ACCELDATARATE_10HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G, lsm.LSM9DS1_ACCELDATARATE_119HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G, lsm.LSM9DS1_ACCELDATARATE_476HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G, lsm.LSM9DS1_ACCELDATARATE_952HZ);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
//  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);

pixy.init();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Void Setup");

if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();

 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
//mySerial.begin(9600);
//    while (!huskylens.begin(mySerial))
//    {
//        Serial.println(F("Begin failed!"));
//        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
//        Serial.println(F("2.Please recheck the connection."));
//        delay(100);
//    }
    gripper.attach(15);
    //flag.attach(12);
    Serial.println("Open Gripper");
    gripper.write(gripperOpen);
    delay(1000);
    stick.setSpeed(150);
    Serial.println("Arm Stick");
//    stick.step(stepsArm);
}

void loop() {

if(counter < 10){
  Serial.println("Read Sensor");
  lsm.read();  /* ask it to read in the data */ 

  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 
    z += g.gyro.z;
    angle = int(z)%fullAngle;
    if(angle > minAngle && angle < maxAngle){
      good = true;
    }
    else{
      good = false;
    }
  }
else if(counter < 20){
  if(mode == 1){
    Serial.println("Mode 1: Get Can");
//        if (!huskylens.request()) Serial.println(F("nothing"));
//    else if(!huskylens.isLearned()) Serial.println(F("Nothing"));
//    else if(!huskylens.available()){
int i;
  pixy.ccc.getBlocks();
  if(pixy.ccc.numBlocks)
    {
//      width = pixy.ccc.blocks[i].m_width;
//while (huskylens.available()){
//           HUSKYLENSResult result = huskylens.read();
            if(pixy.ccc.blocks[i].m_width < 300){
              if(pixy.ccc.blocks[i].m_width < 200){
                 spedeor = 35;
                 spedeol = 40;
              }
              if(pixy.ccc.blocks[i].m_width > 200){
                 spedeor = 35;
                 spedeol = 40;
              }
            if(pixy.ccc.blocks[i].m_x > 208){
              Serial.println("Right");
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}

if(pixy.ccc.blocks[i].m_x < 108){
  Serial.println("Left");
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}
if(pixy.ccc.blocks[i].m_x > 108 && pixy.ccc.blocks[i].m_x < 208){
   Serial.println("Straight");
  digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}
            }
if(pixy.ccc.blocks[i].m_width > 300){
  Serial.println("Grab Can");
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    gripper.write(gripperClose);
      mode = 3;
}
//        }
    }
    else{
      Serial.println("No Can");
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, spedeol);
    }
  }
  if(mode == 3){
    Serial.println("Mode 3");
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
    Serial.println("Mode 4");
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
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
//    stick.step(stepsFire);
    gripper.write(gripperOpen);
    delay(1000);
//    stick.step(stepsArm);
    mode = 1;
  }
  }
}
else{
  counter = 0;
}
counter ++;
}
