#include <Pixy2.h>
#include <Servo.h>
#include <Encoder.h>
#include <HCSR04.h>

//Pixy2 pixy;
Servo servo;
Encoder myEnc(2, 3);
UltraSonicDistanceSensor distanceSensor(8, A0);
Pixy2 pixy;

int motor = 22;  
int width = 0;
int angle = 80;
int power = 255;
long oldSpeed = 0;
long newSpeed = 0;
long spede = 0;
int thyme = 0;

int rightBumper = 10;
int stopButton = 9;
int leftBumper = 11;
int right = 1;
int left = 1;
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
  pixy.init();
}
void loop() {
  if(power >= 0){
  analogWrite(motor, power);
  }
  // START!!!!!!!!!
 // if(thyme < power){
 //if(thyme == 0){
  //  Serial.println("stage 1");
    stap = digitalRead(stopButton);
      if(stap == LOW){
   // right = digitalRead(rightBumper);
   // left = digitalRead(leftBumper);
    if(right == HIGH && left == HIGH){
       if(distance < 5 && distance < 100){
    // analogWrite(motor, power);
  //  Serial.println("stage one");
       }
       
          if(distance > 5 && distance < 100){
            Serial.println("dist ");
    //  analogWrite(motor, 0);
    //  delay(1000);
      power = 5;
          }
    
    }
    if(right == LOW || left == LOW){
      Serial.println("bumper");
   //   analogWrite(motor, 0);
      delay(7000);
      power = 5;
    }
      }
      if(stap == HIGH){
        Serial.println("stop");
//  analogWrite(motor, 0);
  delay(30000);
  power = 4;
      }
//}

if(thyme == 0 && power <= 250){
  distance = distanceSensor.measureDistanceCm();
}
if(power > 200){
  distance = 1;
  Serial.print("too slow");
}

  //HALF WAY!!!!!!!!
  // if(thyme >= power && thyme < 3-power){
  //if(thyme > 0 && thyme < 2){
      int i;
  pixy.ccc.getBlocks();
    servo.write(angle);
  // analogWrite(motor, 0);
  // Serial.println("stage 2");
    if (pixy.ccc.numBlocks){
   width = pixy.ccc.blocks[i].m_height;
      servo.write(angle);
   angle = map(width, 0, 208, 90, 70);
    }
 //  }
   //END !!!!!!!!!!
      thyme = thyme+1;
  // if(thyme >= 6-power){
      newSpeed = myEnc.read();
    spede = newSpeed-oldSpeed;
   power = map(spede, 0, 1000, 255, 0);
      oldSpeed = myEnc.read();
      if(thyme == 1){
    thyme = 0;
   }
  Serial.println(spede);
}
