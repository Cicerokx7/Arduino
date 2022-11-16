int side = 0;
int motor = 2;
int width = 0;
int angle = 40;

#include <Pixy2.h>
#include <Servo.h>

Pixy2 pixy;
Servo servo;

void setup() {
  pinMode(motor, OUTPUT);
  servo.attach(5);
  Serial.begin(9600);
  pixy.init();
}

void loop() {
  servo.write(angle);
          int i;
    pixy.ccc.getBlocks();
    width = pixy.ccc.blocks[i].m_x;
    analogWrite(motor, 175);
    delay(50);
   analogWrite(motor, 0);
    if (pixy.ccc.numBlocks){
               if(width < 145){
    Serial.println("left");
    angle = 80;
   }
    if(width > 145){
      Serial.println("right");
      angle = 50;
    }
}
    else{
      angle = 80;
    }
  
      /*
      if(pixy.ccc.blocks[i].m_signature != 1 && pixy.ccc.blocks[i].m_x < 158){
        side = 1;
      }
      if(pixy.ccc.blocks[i].m_signature != 1 && pixy.ccc.blocks[i].m_x > 158){
        side = 2;
      }
      if(pixy.ccc.blocks[i].m_signature != 1 && pixy.ccc.blocks[i].m_x > 158 && side == 1){
        side = 0;
      }
      if(pixy.ccc.blocks[i].m_signature != 1 && pixy.ccc.blocks[i].m_x < 158 && side == 2){
        side = 0;
      }
      
      if(side == 0){
         if(width < 156){
    Serial.println("left");
    angle = 80;
   }
    if(width > 156){
      Serial.println("right");
      angle = 54;
    }
}
    else{
      angle = 80;
    }
      }
     
      if(side == 1){
        width = width-30; 
   angle = map(width, 0, 316, 80, 42);
      }
      if(side == 2){
        width = width+30; 
   angle = map(width, 0, 316, 80, 42);
      }
      */
delay(10);
}
