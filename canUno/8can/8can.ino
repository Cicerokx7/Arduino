#include <HCSR04.h>
#include <Pixy2.h>
#include <Servo.h>

UltraSonicDistanceSensor rightLeftSensor(16, 19);
UltraSonicDistanceSensor frontRightSensor(15, 21);
UltraSonicDistanceSensor frontLeftSensor(A0, 20);
UltraSonicDistanceSensor rightRightSensor(17, 18);

int rightFMotor = 4;
int rightBMotor = 9;
//int leftMotor[2] = {7, 8};
int leftFMotor = 7;
int leftBMotor = 8;
int pwmpin[2] = {6, 5};
int pwmR = 6;
int pwmL = 5;
int i = 0;
int FRS = 0;
int FLS = 0;
int RRS = 0;
int RLS = 0;
int r = 0;
int l = 0;
int steps = 0;
int goal = 0;
int canW = 0;

Pixy2 pixy;
Servo gripper;

void setup() {
 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(13, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
 gripper.attach(14);
 gripper.write(50);// 160closed  50 open
  Serial.begin(9600);
  pixy.init();
}

void loop() {
    int i;
        pixy.ccc.getBlocks();
    canW = pixy.ccc.blocks[i].m_width;
    goal = round(158);
  FRS = frontRightSensor.measureDistanceCm();
  FLS = frontLeftSensor.measureDistanceCm();
  RRS = rightRightSensor.measureDistanceCm();
  RLS = rightLeftSensor.measureDistanceCm();

  if(FRS > 10 && FLS > 10 && steps == 0){
              digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
    delay(100);
                  digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
  }
  if(FRS < 5 || FLS < 5){
    if(steps == 0){
    steps = 1;
    }
  }
    if(steps == 1){
                   digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
    delay(100);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
  }
  if(RLS == RRS && steps == 1 && RLS < 20 && RRS < 20){
    steps = 2;
  }
  if(RLS > RRS && steps == 2){
                       digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 28);
    delay(100);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
  }
  if(RRS > RLS && steps == 2){
                       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 0);
    delay(100);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
  }
if(RRS == RLS && steps == 2){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
    delay(100);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
}

    if(pixy.ccc.numBlocks){
    if(canW < 299){
    if(pixy.ccc.blocks[i].m_x > goal){
               digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 50);//%60
    delay(100);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    }
      Serial.println("left");
    if(pixy.ccc.blocks[i].m_x == goal){
       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 50);
      Serial.println("go");
      delay(100);
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    }
    if(pixy.ccc.blocks[i].m_x < goal){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 50);
      Serial.println("right");
      delay(100);
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    }
    }
    if(canW >= 300){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
      Serial.println("can");
    }
    }
      
       /*   digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 100);
    analogWrite(pwmL, 100);
    */
    
      
// Serial.println(canW);
//delay(100);
}
