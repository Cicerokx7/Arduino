#include <Servo.h>

Servo pan;
Servo tilt;

int leftO = 10;
int rightO = 8;
int blocks = 0;
int leftVal = 0;
int rightVal = 0;
int forVal = 0;
int stopB = 0;
int guideB = 0;
int sb = 0;
int gb = 5;
int panV = 0;
//int tiltV = 0;
int panR = A0;
//int tiltR = 0;
int PPservo = 90;
int PTservo = 90;
int panOn = 7;
//int tiltOn = 0;

void setup() {
  Serial.begin(9600);
Serial.print("starting;  ");
pan.attach(3);
tilt.attach(5);
pinMode(rightO, OUTPUT);
pinMode(leftO, OUTPUT);
pinMode(sb, INPUT);
pinMode(gb, INPUT);
pinMode(3, OUTPUT);
pinMode(5, INPUT);
//pinMode(tiltOn, OUTPUT);
//digitalWrite(tiltOn, HIGH);
pan.write(90);
tilt.write(90);
}

void loop() {
  Serial.print("starting;  ");
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];
    stopB = digitalRead(sb);
  guideB = digitalRead(gb);
  panV = analogRead(panR);

    //if(guideB == LOW){
   digitalWrite(panOn, LOW);

        if(panV < 200){
          digitalWrite(rightO, HIGH);
          digitalWrite(leftO, LOW);
        }
        if(panV > 200 && panV < 275){
          digitalWrite(rightO, HIGH);
          digitalWrite(leftO, HIGH);
        }
        if(panV > 275){
          digitalWrite(rightO, LOW);
          digitalWrite(leftO, HIGH);
        }     
  //    }
      if(guideB == HIGH){
        digitalWrite(rightO, LOW);
        digitalWrite(leftO, LOW);
      }
  }
