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
int goal = 158;
int canW = 0;
int count = 0;
int can = 0;
int beacon = 0;
int FRS = 0;
int FLS = 0;
int RRS = 0;
int RLS = 0;

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
  Serial.begin(9600);
  pixy.init();
  gripper.attach(21);
  gripper.write(0);
}

void loop() {
  
                 FRS = frontRightSensor.measureDistanceCm();
  RRS = rightRightSensor.measureDistanceCm();
  RLS = rightLeftSensor.measureDistanceCm();
  FLS = frontLeftSensor.measureDistanceCm();
  /*
          int i;
    pixy.ccc.getBlocks();
    canW = pixy.ccc.blocks[i].m_width;
    if(can == 0){
    if(pixy.ccc.blocks[i].m_signature != 1){
      count = count+1;
    }
    
     if(count == 50){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 30);
    
    }
    
    if(pixy.ccc.blocks[i].m_signature == 1){
      count = 0;
    if(canW < 299){
    if(pixy.ccc.blocks[i].m_x > goal){
               digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 40);
    analogWrite(pwmL, 40);//%60
    Serial.println("left");
    }
    if(pixy.ccc.blocks[i].m_x == goal){
       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 40);
    analogWrite(pwmL, 40);
      Serial.println("go");
    }
    if(pixy.ccc.blocks[i].m_x < goal){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 40);
    analogWrite(pwmL, 40);
      Serial.println("right");
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
      gripper.write(150);
      can = 1;
    }
    
    }
    }
    
    
    if(can == 1){
      if(beacon == 0){
           if(pixy.ccc.blocks[i].m_signature != 2){
                  digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 20);
    Serial.print("right");
           }
      }
           if(pixy.ccc.blocks[i].m_signature == 2){
            beacon = 1;
           }
           if(beacon == 1){
               FRS = frontRightSensor.measureDistanceCm();
  RRS = rightRightSensor.measureDistanceCm();
  RLS = rightLeftSensor.measureDistanceCm();
             if(FRS > 30 && count == 0){
                  digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
           }
             if(FRS < 30){
    if(count == 0){
    count = 1;
    }
  }
      if(count == 1){
                   digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
        if(RLS == RRS && count == 1 && RLS < 40 && RRS < 40){
    count = 2;
  }
  }
  if(count == 2){
    if(RLS > RRS){
                       digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 30);
  }
    if(RRS > RLS){
                       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 30);
  }
if(RRS == RLS){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
}
if(FRS < 30){
  count = 3;
}
  }
    if(count == 3){
                         digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
        if(RLS == RRS && RLS < 20 && RRS < 20){
    count = 4;
  }
  }
  if(count == 4){
    if(RLS > RRS){
                       digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 30);
  }
    if(RRS > RLS){
                       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 30);
    analogWrite(pwmL, 30);
  }
if(RRS == RLS){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 20);
    analogWrite(pwmL, 28);
}
    }

      Serial.println("can");
      gripper.write(150);
    }
 Serial.println(can);   
}
*/
Serial.println(FLS);
}
