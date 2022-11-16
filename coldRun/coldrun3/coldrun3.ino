#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo servo;

int motor = 2;
int width = 0;
int angle = 40;
int count = 0;

void setup() {
  pinMode(motor, OUTPUT);
  servo.attach(5);
  Serial.begin(9600);
  //servo.write(angle);
  Serial.println("testo");
  pixy.init();
}

void loop() {
  servo.write(angle);
          int i;
    pixy.ccc.getBlocks();
    width = pixy.ccc.blocks[i].m_width;
    analogWrite(motor, 200);
    delay(50);
   // servo.write(angle);
   analogWrite(motor, 0);
    if (pixy.ccc.numBlocks){
      Serial.println("test");
   //   servo.write(angle);
   if(count < 2000){
          if(width < 156){
    Serial.println("left");
    angle = 80;
   }
    if(width > 156){
      Serial.println("right");
      angle = 54;
    }

   count ++;
    }
    if(count > 2010 && count < 4000){
             if(width < 156){
    Serial.println("left");
    angle = 70;
   }
    if(width > 156){
      Serial.println("right");
      angle = 54;
    }

      count ++;
    }
    if(count == 2000 || count == 2010){
      servo.write(60);
      if(count == 200){
        analogWrite(motor, 200);
        delay(1000);
        count ++;
      }
      if(width < 156 && count == 2010){
        count ++;
      }
    }
    if(count == 4000 || count == 4010){
      servo.write(55);
      if(count == 400){
        analogWrite(motor, 200);
        delay(1000);
        count ++;
      }
      if(width < 156 && count == 4010){
        count = 0;
      }
    }
    }
        else{
      angle = 80;
    }
    delay(10);
}
