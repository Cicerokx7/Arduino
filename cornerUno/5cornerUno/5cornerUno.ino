//#include <Servo.h>
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

//Servo gripper;
//Servo flag;
HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11);

void printResult(HUSKYLENSResult result);

int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;

int goalSwitchPin = A5;

int gripperClose = 80; 
int gripperOpen = 60;

int goalSwitch = 0;
int mode = 0;
int right = 0;
int left = 0;
int stap = 0;
int strait = 0;
int canW = 0;
int spedeor = 70;
int spedeol = 50;
int rspeder = 21;
int rspedel = 21;
int trigger = 0;
int high = 10;
int low = 100;
int can = 0;
int count = 0;

void setup() {
       
  // put your setup code here, to run once:
 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
 pinMode(goalSwitchPin, INPUT);
Serial.begin(9600);
mySerial.begin(9600);
    while (!huskylens.begin(mySerial))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>Serial 9600)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    //gripper.attach(3);
    //flag.attach(12);
    //gripper.write(gripperOpen);
//flag.write(low);
delay(5000);
}

void loop() {
        if (!huskylens.request()) Serial.println(F("nothing"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing"));
    else if(!huskylens.available()){
      count ++;
      if(count == 50){
        //Serial.println("test");
        spedeor = 45;
                 spedeol = 45;
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    count = 0;
      }
    }
    else
    {
while (huskylens.available()){
           HUSKYLENSResult result = huskylens.read();
                 spedeor = 45;
                 spedeol = 45;
            if(result.xCenter > 20){
          //    Serial.println("test");
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}

if(result.xCenter < 20){
  //Serial.println("test");
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}
/*
if(result.xCenter > 100 && result.xCenter < 170){
   //Serial.println("test");
  digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
}
*/
    }
  }
}
