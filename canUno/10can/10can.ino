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
int goal = 106;
int canW = 0;
int count = 0;
int can = 0;
int beacon = 0;
int FRS = 0;
int FLS = 0;
int RRS = 0;
int RLS = 0;
int spedeo = 35;
int spedet = 25;
int barSwitch = 0;

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

}

void loop() {
                 FRS = frontRightSensor.measureDistanceCm();
  RRS = rightRightSensor.measureDistanceCm();
  RLS = rightLeftSensor.measureDistanceCm();
  FLS = frontLeftSensor.measureDistanceCm();
  barSwitch = digitalRead(A9);
  
  Serial.print("FLS");
  Serial.println(FLS);
  Serial.print("FRS");
  Serial.println(FRS);
  Serial.print("RLS");
  Serial.println(RLS);
  Serial.print("RRS");
  Serial.println(RRS);
  Serial.println(count);
  Serial.println(barSwitch);
  
if(count == 0){
  if(FLS > FRS){
          digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
  }
  if(FLS < FRS){
          digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
  }
  if(FLS == FRS){
    count = 1;
  }
}
  
  if(count == 1){
  if(FLS < goal+10 || FRS < goal+10){
      if(FLS > FRS){
          digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  if(FLS < FRS){
          digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  }
  
    if(FLS > goal-10 || FRS > goal-10){
      if(FLS < FRS){
          digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
      }
      if(FLS > FRS){
        digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
      }
    }
      if(FLS >= goal-10 && FRS >= goal-10 && FLS <= goal+10 && FRS <= goal+10){
        digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    delay(300);
    count = 2;
      }
  }
    if(count == 2){
if(RLS != RRS || RLS == -1 || RRS == -1){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
}
if(RLS == RRS && RLS != -1 && RRS != -1){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
  count = 3;
 // goal = (RLS+RRS)/2;
}
    }
    if(count == 3){
           if(RLS > goal && RRS < goal){
          digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  if(RLS < goal && RRS > goal){
          digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  if(RLS == goal && RRS == goal){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
  }
  if(RLS > goal && RRS > goal){
    if(RLS >= RRS){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(RLS < RRS){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
  }
  if(RLS < goal && RRS < goal){
    if(RLS > RRS){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    if(RLS <= RRS){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
  }
  if(barSwitch == LOW){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    count = 4;
  }
  /*if(RLS < 4 || RRS < 4){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    count = 0;
  }*/
    }
}
