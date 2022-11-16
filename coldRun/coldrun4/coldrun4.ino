#include <Pixy2.h>
#include <Servo.h>
#include <Encoder.h>

Pixy2 pixy;
Servo servo;
Encoder myEnc(6, 5);

int motor = 22;
int width = 0;
int angle = 80;
long power = 50;
long oldSpeed = 0;
long newSpeed = 0;
long spede = 0;
int thyme = 0;

void setup() {
  pinMode(motor, OUTPUT);
  servo.attach(10);
  Serial.begin(9600);
  servo.write(angle);
  Serial.println("testo");
  pixy.init();
}
//long newSpeed = -999;
void loop() {
  
  int i;
  if(thyme < 1+power){
  servo.write(angle);
    pixy.ccc.getBlocks();
    analogWrite(motor, 255);
    Serial.println(thyme);
   // delay(power);
    newSpeed = myEnc.read();
    spede = newSpeed-oldSpeed;
   power = map(spede, 0, 1000, 5, 0);
      oldSpeed = myEnc.read();
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
   Serial.println(spede);
   thyme = thyme+1;
//delay(10);

}
