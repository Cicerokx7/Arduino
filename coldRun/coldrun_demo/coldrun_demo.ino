#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo servo;

int motor = 4;
int width = 0;
int angle = 40;
int rightBumperP = 15;
int leftBumperP = 14;
int stopBP = 7;
int stopB = 0;
int leftBumper = 0;
int rightBumper = 0;

void setup() {
  pinMode(motor, OUTPUT);
  servo.attach(10);
  Serial.begin(9600);
  //servo.write(angle);
  Serial.println("testo");
  pixy.init();
  pinMode(stopBP, INPUT);
  pinMode(leftBumperP, INPUT);
  pinMode(stopBP, INPUT);
}

void loop() {
  
  rightBumper = digitalRead(rightBumperP);
  leftBumper = digitalRead(leftBumperP);
  stopB = digitalRead(stopBP);
  servo.write(angle);
  if(rightBumper == HIGH || leftBumper == HIGH){
    analogWrite(motor, 0);
  }
  if(stopB == HIGH){
    analogWrite(motor, 0);
    delay(30000);
  }
          int i;
      pixy.line.getMainFeatures();
      
    width = pixy.line.vectors->m_y1;
    if(rightBumper == LOW && leftBumper == LOW){
    analogWrite(motor, 155);
    }
    delay(100);
   //analogWrite(motor, 0);
   
      
     // Serial.println("test");
   if(width < 20){
    angle = 70;
   // Serial.print("left");
   }
   if(width > 20){
    angle = 100;
  //  Serial.print("Right");
   
    }
    if(width == 0){
      angle = 100;
    }
delay(10);
    Serial.println(width);
}
