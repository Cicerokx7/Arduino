#include <Servo.h>
#include <Pixy2.h>

Servo gripper;
Servo flag;
Pixy2 pixy;

int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;

int goalSwitchPin = A5;

int gripperClose = 120;
int gripperOpen = 20;

int goalSwitch = 0;
int mode = 0;
int right = 1;
int left = 0;
int stap = 0;
int strait = 0;
int canW = 0;
int goalo = 158;
int spedeo = 30;
int spedet = 18;
int trigger = 0;
int high = 70;
int low = 180;
int can = 0;

void setup() {
       
  // put your setup code here, to run once:
   pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(13, OUTPUT); 
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
 pinMode(goalSwitchPin, INPUT);
Serial.begin(9600);
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
      char c = Serial.read();  //gets one byte from serial buffer
    if (isControl(c)) {
      //'Serial.println("it's a control character");
      break;
    }
      readString += c; //makes the string readString    
    }
 }   

 Q = readString;
 if(Q != "right" && mode == 0 && Q != "left"){
Serial.print("on");
 }
 if(mode == 0){
if(Q == "right" || Q == "left"){
mode = 1;
}
 }
if(Q == "right"){
  right = 1;
  left = 0;
  stap = 0;
}
if(Q == "left"){
  left = 1;
  right = 0;
  stap = 0;
}
if(Q == "stop"){
  right = 0;
  left = 0;
  stap = 1;
}
if(Q = "strait"){
  right = 1;
  left = 1;
  stap = 0;
}
if(Q = "trigger"){
  trigger = 1;
}

  if(mode < 3){
    int i;
    pixy.ccc.getBlocks();
    canW = pixy.ccc.blocks[i].m_width;
  if (pixy.ccc.numBlocks)
  {
    mode = 2;
    i++;
    if(canW < 250){
    if(pixy.ccc.blocks[i].m_x > goalo){
               digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);//%60
    }
    if(pixy.ccc.blocks[i].m_x == goalo){
       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    if(pixy.ccc.blocks[i].m_x < goalo){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    }
    if(canW >= 250){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
      gripper.write(gripperClose);
      Serial.print("one");
      mode = 3;
    }
    }
  else{
    if(mode == 1){
    if(right == 1){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(left == 1){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    }
  }
  }
  if(mode == 3){
    if(goalSwitch == HIGH){
    if(right == 1){
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    else{
    digitalWrite(leftFMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(left == 1){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    else{
      digitalWrite(rightFMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(stap == 1){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(trigger == 1){
      stap = 0;
    flag.write(high);
    trigger = 0;
    }
  }
  if(goalSwitch == LOW){
    mode = 4;
  }
  }
  if(mode == 4){
    can = can+1;
          gripper.write(gripperOpen);
      flag.write(low);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    delay(2000);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    Serial.print("can");
    if(can < 6){
    if(right == 1){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(left == 1){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(stap == 1){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    mode = 0;
    }
    }
    if(can == 6){
      flag.write(high);
    }
  }
//70 flag 180
}
