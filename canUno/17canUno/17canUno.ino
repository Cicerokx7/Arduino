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
  goalSwitch = digitalRead(goalSwitchPin);
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
 if(Q != "right" && mode == 0 && Q != "left"){
Serial.println("on");
      //digitalWrite(rightFMotor, HIGH);
      //analogWrite(pwmR, 255);
 }
 if(mode == 0){
 // gripper.attach(3);
   // flag.attach(12);
  //  gripper.write(gripperOpen);
//flag.write(low);
if(Q == "right" || Q == "left"){
mode = 1;
}
 }
if(Q == "right"){
  right = 1;
  left = 0;
 // stap = 0;
 // trigger = 0;
}
if(Q == "left"){
  left = 1;
  right = 0;
 // stap = 0;
 // trigger = 0;
}
if(Q == "stap"){
  stap = 1;
  trigger = 0;
}
if(Q == "strait"){
  right = 1;
  left = 1;
  stap = 0;
  trigger = 0;
}
if(Q == "trigger"){
  trigger = 1;
  stap = 0;
}
  if(mode < 3 && mode != 0){
      //  gripper.attach(13);
        //  flag.attach(13);
        if (!huskylens.request()) Serial.println(F("nothing"));
    else if(!huskylens.isLearned()) Serial.println(F("Nothing"));
    else if(!huskylens.available()){
      if(mode == 1){
    if(right == 1){
      spedeor = 25;
                 spedeol = 25;
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
    if(left == 1){
      spedeor = 25;
                 spedeol = 25;
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
    }
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
      Serial.println("test");
      mode = 3;
}
        }
    }
  }
  if(mode == 3 || mode == 4 || mode == 5 || mode == 6 || mode == 7){ 
       // gripper.attach(3);
       //   flag.attach(12);
    if(goalSwitch == HIGH){
      Serial.println("test");
      //    gripper.write(gripperClose);
          if(mode == 3){
              Serial.println("test");
              if(stap == 1){
                mode = 4;
              }
          }
          if(mode == 4){
              if(right == 1){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
  //  Serial.print("right");
    }
    if(left == 1){
    digitalWrite(leftFMotor, LOW);
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
   // Serial.print("left");
    }
    if(trigger == 1){
      stap = 0;
          digitalWrite(leftFMotor, LOW);
      digitalWrite(rightFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
   // flag.write(high);
    delay(1000);
    trigger = 0;
    mode = 5;
    }
    }
          if(mode == 5){
    if(right == 1){
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
  //  Serial.print("right");
    }
    else{
    digitalWrite(leftFMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
    if(left == 1){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
  //  Serial.print("left");
    }
    else{
      digitalWrite(rightFMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
    if(stap == 1){
      mode = 6;
    }
          }
    if(mode == 6){
         if(right == 1){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
  //  Serial.print("right");
    }
    if(left == 1){
    digitalWrite(leftFMotor, LOW);
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
   // Serial.print("left");
    }
    }
    if(trigger == 1 && mode == 6){
      stap = 0;
          digitalWrite(leftFMotor, LOW);
      digitalWrite(rightFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
   // flag.write(high);
    delay(1000);
    trigger = 0;
    mode = 7;
    }
  }

  if(mode == 7){
    spedeor = 40;
                 spedeol = 40;
    if(right == 1){
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
  //  Serial.print("right");
    }
    else{
    digitalWrite(leftFMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
    if(left == 1){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
  //  Serial.print("left");
    }
    else{
      digitalWrite(rightFMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
  }
  }
  if(mode == 8){
        digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    can = can+1;
    //      gripper.write(gripperOpen);
    //  flag.write(low);
      delay(1000);
           //   gripper.attach(13);
         // flag.attach(13);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    delay(1000);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    Serial.println("can");
    mode = 9;
  }
  if(goalSwitch == LOW && mode == 7){
    mode = 100;
    Serial.println("can");
    delay(100);
    Serial.println("can");
    delay(100);
    Serial.println("can");
    delay(100);
    Serial.println("can");
  }
  if(mode == 9){
        Serial.println("can");
    if(can < 6){
    if(right == 1){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
    }
    if(left == 1){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
   
     analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
    }
    if(stap == 1){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    stap = 0;
    mode = 0;
    }
    }
    if(can == 6){
            //  gripper.attach(3);
         // flag.attach(12);
    //  flag.write(high);
    }
  }
//70 flag 180&
  if(mode == 100){
    mode = 8;
    Serial.println("can");
    delay(100);
    Serial.println("can");
    delay(100);
    Serial.println("can");
    delay(100);
    Serial.println("can");
  }
}
