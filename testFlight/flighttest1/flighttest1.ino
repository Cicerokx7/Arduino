#include <Pixy2.h>
#include <Servo.h>

int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;
int x = 0;
int y = 0;
int yI = 0;
int xI = 0;
int manual = 0;
int ato = 0;
int dist = 0;
int count = 0;
int countS = 1;
int goalo = 158;
int goaly = 104
int goalt = 90;
int spedeo = 30;
int spedet = 18;

Servo why;
Servo ex;

void setup() {
 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
 pinMode(yI, INPUT);
 pinMode(xI, INPUT);
 pinMode(manual, INPUT);
 pinMode(ato, INPUT);
 
 why.attach(2);
 ex.attach(3);

}

void loop() {
  why.write(x);
  ex.write(y)
  manual = digitalRead();
  ato = digitalRead();

  if(manual != HIGH){
        int i;
    pixy.ccc.getBlocks();
    dist = pixy.ccc.blocks[i].m_width;
        if(count == 0){
    if(pixy.ccc.blocks[i].m_signature != 1){
      count = count+1;
    }
  }
  if(count == 50){
    if(x == 0||x == 180){
      countS = countS*-1
    }
    x = x+countS
    y = 90;
  }
  
  while(pixy.ccc.blocks[i].m_signature == 1){
    if(pixy.ccc.blocks[i].m_x > goalo && x < 180){
       x = x+1;
    }
    if(pixy.ccc.blocks[i].m_x < goalo && x > 0){
      x = x-1;
    }
    if(pixy.ccc.blocks[i].m_y > goaly && y < 180){
      y = y+1;
    }
    if(pixy.ccc.blocks[i].m_x < goaly && y > 0){
      y = y-1;
    }
  }
  
  if(pixy.ccc.blocks[i].m_signature == 1){
    if(dist < 300){
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
        if(dist >= 300){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
        }
     }
  }
}

//make it go back, stop, and be controlled manualy!
