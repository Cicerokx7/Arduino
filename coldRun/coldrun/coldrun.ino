#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo servo;

int motor = 2;
int width = 0;
int angle = 40;

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
    width = pixy.ccc.blocks[i].m_height;
    analogWrite(motor, 255);
    delay(100);
   // servo.write(angle);
   analogWrite(motor, 0);
    if (pixy.ccc.numBlocks){
      Serial.println("test");
   //   servo.write(angle);
   angle = map(width, 0, 208, 80, 42);
   /*
   if(width < 52){
    Serial.println("left");
    angle = 80;
   }
    else if(width < 104){
      Serial.println("left");
      angle = 68;
    }
    else if(width > 104){
      Serial.println("right");
      angle = 54;
    }
    else if(width > 156){
      Serial.println("right");
      angle = 42;
    }
    else{
      angle = 42;
    }
    }
    else{
      angle = 80;
    }
    */
    }
delay(10);
Serial.println(width);
}
