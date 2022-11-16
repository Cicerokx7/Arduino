#include <Pixy2.h>
#include <Servo.h>
#include <Encoder.h>
#include <HCSR04.h>

//Pixy2 pixy;
Servo servo;
Encoder myEnc(2, 3);
UltraSonicDistanceSensor distanceSensor(7, A12);
Pixy2 pixy;

int motor = 22;  
int width = 0;
int angle = 80;
long power = 5;
long oldSpeed = 0;
long newSpeed = 0;
long spede = 0;
int thyme = 0;

int rightBumper = 15;
int stopButton = 16;
int leftBumper = 14;
int right = 0;
int left = 0;
int stap = 0;
int distance = -1;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(rightBumper, INPUT);
  pinMode(leftBumper, INPUT);
  pinMode(stopButton, INPUT);
  servo.attach(24);
  Serial.begin(9600);
  servo.write(angle);
 // Serial.println("testo");
  pixy.init();
}
//long newSpeed = -999;
void loop() {
  newSpeed = myEnc.read();
    spede = newSpeed-oldSpeed;
   power = map(spede, 0, 1000, 5, 0);
      oldSpeed = myEnc.read();
  // START!!!!!!!!!
  if(thyme < 1+power){
    Serial.println("stage 1");
    stap = digitalRead(stopButton);
      if(stap == LOW){
    right = digitalRead(rightBumper);
    left = digitalRead(leftBumper);
    if(right == HIGH && left == HIGH){
       if(distance < 5){
    analogWrite(motor, 255);
    Serial.println("stage one");
   // Serial.println(thyme);
   // delay(power);
    
 // /*
       }
       
          if(distance > 5){
      analogWrite(motor, 0);
      delay(1000);
      power = 5;
      Serial.println("bumper");
          
          }
    
    
    if(right == LOW || left == LOW){
      analogWrite(motor, 0);
      delay(7000);
      power = 5;
      Serial.println("bumper");
    }
 //*/
      if(stap == HIGH){
  analogWrite(motor, 0);
  delay(30000);
  power = 4;
  Serial.println("stop");
      }
    }
}
}
  //HALF WAY!!!!!!!!/*
   // delay(50);
   // */HALF WAY!!!!!!!
   if(thyme >= 1+power && thyme < 13-power){
      int i;
  pixy.ccc.getBlocks();
    servo.write(angle);
   analogWrite(motor, 0);
   Serial.println("stage 2");
    if (pixy.ccc.numBlocks){
   width = pixy.ccc.blocks[i].m_height;
     // Serial.println("test");
      servo.write(angle);
   angle = map(width, 0, 208, 90, 70);
    }
   }
   //END !!!!!!!!!!
   if(thyme >= 13-power){
    distance = distanceSensor.measureDistanceCm();
    thyme = 0;
   }
  // Serial.println(thyme);
 //  Serial.println(power);
   thyme = thyme+1;
//delay(10);
//Serial.println(distance);
  //Serial.print(distanceSensor.measureDistanceCm());
  //}
  Serial.println(oldSpeed);
}
