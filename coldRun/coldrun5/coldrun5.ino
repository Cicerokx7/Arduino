#include <Pixy2.h>
#include <Servo.h>
#include <Encoder.h>
#include <HCSR04.h>

Pixy2 pixy;
Servo servo;
Encoder myEnc(2, 3);
UltraSonicDistanceSensor distanceSensor(4, A0);

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
int distance = 0;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(rightBumper, INPUT);
  pinMode(leftBumper, INPUT);
  pinMode(stopButton, INPUT);
  servo.attach(10);
  Serial.begin(9600);
  servo.write(angle);
 // Serial.println("testo");
  pixy.init();
}
//long newSpeed = -999;
void loop() {
  stap = digitalRead(stopButton);
  if(stap == LOW){
  int i;
  pixy.ccc.getBlocks();
  if(thyme < 1+power){
    distance = distanceSensor.measureDistanceCm();
    right = digitalRead(rightBumper);
    left = digitalRead(leftBumper);

    if(distance == -1 && right == HIGH && left == HIGH){
      if(angle < 90 && angle > 70){
  servo.write(angle);
      }
    analogWrite(motor, 255);
   // Serial.println(thyme);
   // delay(power);
    newSpeed = myEnc.read();
    spede = newSpeed-oldSpeed;
   power = map(spede, 0, 1000, 5, 0);
      oldSpeed = myEnc.read();
    }
  
    if(distance != -1 || right == LOW || left == LOW){
      analogWrite(motor, 0);
      delay(7000);
      power = 5;
      Serial.println("bumper");
    }
 
  }
   if(spede > 0){
  // Serial.println(spede);
   }
   oldSpeed = myEnc.read();
   // delay(50);
   if(thyme >= 1+power && thyme < 13-power){
    servo.write(angle);
   analogWrite(motor, 0);
    if (pixy.ccc.numBlocks){
   width = pixy.ccc.blocks[i].m_height;
     // Serial.println("test");
      servo.write(angle);
   angle = map(width, 0, 208, 90, 70);
    }
   }
   if(thyme >= 13-power){
    thyme = 0;
   }
  // Serial.println(thyme);
 //  Serial.println(power);
   thyme = thyme+1;
//delay(10);
  }
if(stap == HIGH){
  analogWrite(motor, 0);
  delay(30000);
  power = 4;
  Serial.println("stop");
}
}
