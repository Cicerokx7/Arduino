#include <HCSR04.h>
#include <Pixy2.h>
#include <Servo.h>

UltraSonicDistanceSensor frontRightSensor(15, 19);
UltraSonicDistanceSensor frontLeftSensor(14, A8);
UltraSonicDistanceSensor rightLeftSensor(16, 20);
UltraSonicDistanceSensor rightRightSensor(17, 18);

int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;
int goalo = 158;
int goalt = 106;
int canW = 0;
int count = 0;
int can = 0;
int beacon = 0;
int FRS = 0;
int FLS = 0;
int RRS = 0;
int RLS = 0;
int spedeo = 30;
int spedet = 18;
int barSwitch = 0;
int thyme = 0;
int gripperClose = 120;
int gripperOpen = 20;
Pixy2 pixy;
Servo gripper;
//Servo neck;

void setup() {
   pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(13, OUTPUT); 
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
 pinMode(A9, INPUT);
  Serial.begin(9600);
  pixy.init();
  gripper.attach(21);
 // neck.attach(x);
  gripper.write(gripperOpen);
 // neck.write(0);
}

void loop() {
  if(can < 6){
  if(count < 2){
    int i;
    pixy.ccc.getBlocks();
    canW = pixy.ccc.blocks[i].m_width;
      Serial.println(canW);
    if(count == 0){
    if(thyme == 0){
      
    if(pixy.ccc.blocks[i].m_signature != 1){
      thyme = thyme+1;
    }
    }
         if(thyme == 50){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }

        if(pixy.ccc.blocks[i].m_signature == 1 && thyme == 50)
        delay(500);

        if(pixy.ccc.blocks[i].m_signature == 1){
      thyme = 0;
    if(canW < 250){
    if(pixy.ccc.blocks[i].m_x > goalo){
               digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, (canW/7)+18);
    analogWrite(pwmL, (canW/7)+18);//%60
    }
    if(pixy.ccc.blocks[i].m_x == goalo){
       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, (canW/4)+18);
    analogWrite(pwmL, (canW/4)+18);
    }
    if(pixy.ccc.blocks[i].m_x < goalo){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, (canW/4)+18);
    analogWrite(pwmL, (canW/4)+18);
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
      //neck.write(45);
      count = 1;
    }
    }
  }
  }
  }
}
