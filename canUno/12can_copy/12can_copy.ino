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
      //neck.write(45);
      count = 1;
    }
    }
  }
          if(count == 1){
           if(pixy.ccc.blocks[i].m_signature != 2){
            if(can == 0){
                  digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
            }
            if(can > 0){
               digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
            }
           }
           if(pixy.ccc.blocks[i].m_signature == 2){
            count = 2;
            if(can == 0){
              digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    delay(500);
           }
           if(can > 0){
            digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    delay(500);
           }
          }
        }
  }
  if(count > 1 && count < 6){
  FRS = frontRightSensor.measureDistanceCm();
  RRS = rightRightSensor.measureDistanceCm();
  RLS = rightLeftSensor.measureDistanceCm();
  FLS = frontLeftSensor.measureDistanceCm();
  barSwitch = digitalRead(A9);
  // change count&&goal-goalt{
if(count == 2){
  if(FLS != -1 && FRS != -1){
  if(FLS > FRS){
          digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  if(FLS < FRS){
          digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  if(FLS == FRS){
    count = 3;
  }
}
if(FLS == -1 || FRS == -1){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
}
}
  
  if(count == 3){
  if(FLS < goalt+10 || FRS < goalt+10){
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
  
    if(FLS > goalt-10 || FRS > goalt-10){
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
      if(FLS >= goalt-10 && FRS >= goalt-10 && FLS <= goalt+10 && FRS <= goalt+10){
        digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    delay(1000);
    count = 4;
      }
  }
    if(count == 4){
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
  count = 5;
      }
    }
    if(count == 5){
           if(RLS > goalt && RRS < goalt){
          digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  if(RLS < goalt && RRS > goalt){
          digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
  }
  if(RLS == goalt && RRS == goalt){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
  }
  if(RLS > goalt && RRS > goalt){
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
  if(RLS < goalt && RRS < goalt){
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
    gripper.write(gripperOpen);
    //neck.write(0);
    count = 6;
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
  if(count > 5){
    int i;
    pixy.ccc.getBlocks();
    canW = pixy.ccc.blocks[i].m_width;
    if(count == 6){
          if(pixy.ccc.blocks[i].m_signature == 1){
    if(canW > 250){
    if(pixy.ccc.blocks[i].m_x > goalo){
               digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);//%60
    }
    if(pixy.ccc.blocks[i].m_x == goalo){
       digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    if(pixy.ccc.blocks[i].m_x < goalo){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedeo);
    analogWrite(pwmL, spedeo);
    }
    }
    if(canW <= 100){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    count = 7;
    }
    thyme = 0;
    }
    if(pixy.ccc.blocks[i].m_signature != 1){
    thyme = thyme+1;
    }
    if(thyme > 30 && thyme < 100){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    if(thyme >= 100){
      count = 7;
    }
    }
    if(count == 7){
                 if(pixy.ccc.blocks[i].m_signature != 2){
                  digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
           }
           if(pixy.ccc.blocks[i].m_signature == 2){
            can = can+1;
            count = 0;
           }
    }
  }
  }
  if(can == 6){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
  }
}
