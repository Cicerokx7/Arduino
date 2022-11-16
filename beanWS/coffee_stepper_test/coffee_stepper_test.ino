#include <Servo.h>

Servo gripperServo;

//pin naming
const int YSwitchInput = 48;
int ySwitch = 0;
const int XSwitchInput = 44;
int xSwitch = 0;
const int XDir = 7;
const int XStep = 6;
const int YDir = 13;
const int YStep = 4;
const int LargeCup = 22;
const int SmallCup = 23;
const int Mixer = 18;


//stepper variables
int xLocation = 0;
long yLocation = 0;
short calibration = 0;
short count = 0;
//const int yMax = 5850;
const long yMax = 50000; // speed 1000
const int xMax = 500; // speed 10000
int stepSpeed = 1000;

//locations
const int XBigCupLocation = 27; // speed 10000  ^
const int YBigCupLocation = 3550; // speed 1000  ^
const int XSmallCupLocation = 87 ; // speed 10000
const int YSmallCupLocation = 2850; // speed 1000
const int XSyrupLocation = 150; // speed 10000
const int XPressLocation = 327; // speed 10000
const int XCapLocation = 415; // speed 10000
const int YCapLocation = 2400; //speed 1000
const int XMixerLocation = 503; // speed 10000  ^
const int YMixerLocation = 4485;  // speed 1000
const int XSpeed = 10000;
const int YSpeed = 1000;

//variables
const int GripperOpen = 78;
const int GripperClose = 60;
const int GripperStart = 40;
int mixerSpeed = 0;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Stepper test!");

    gripperServo.attach(21);
    gripperServo.write(GripperStart);
    //45-75

    pinMode(XSwitchInput, INPUT);
    pinMode(YSwitchInput, INPUT);
    pinMode(XDir, OUTPUT);
    pinMode(XStep, OUTPUT);
    pinMode(YDir, OUTPUT);
    pinMode(YStep, OUTPUT);
    pinMode(LargeCup, OUTPUT);
    pinMode(SmallCup, OUTPUT);
    pinMode(Mixer, OUTPUT);
    digitalWrite(LargeCup, LOW);
    digitalWrite(SmallCup, LOW);
    analogWrite(Mixer, 0);
}
//function prototypes
void xStepper(char, long, int); 
void yStepper(char, long, int);
void xAxis(long, int);
void yAxis(long, int);

void loop() {

  while(xLocation <= xMax){
    while(yLocation <= yMax){
    xSwitch = digitalRead(XSwitchInput);
    ySwitch = digitalRead(YSwitchInput);
    /***********************************

    STEPPER CALIBRATION
    
    ***********************************/
    //y axis setup
    if(calibration == 0){
            digitalWrite(YDir, LOW);
            digitalWrite(YStep, HIGH);
            delayMicroseconds(10);
            digitalWrite(YStep, LOW);
            delayMicroseconds(10);
            Serial.println(ySwitch);
    if(ySwitch == LOW){
      count = 0;
    }
    if(ySwitch == HIGH){
     count ++;
    }
    if(count == 3){
      count = 0;
      calibration = 1;
      Serial.println("stop");
    }
    }
    //x axis setup
    if(calibration == 1){
      if(xSwitch == LOW){
        Serial.println("please");
            digitalWrite(XDir, HIGH);
            digitalWrite(XStep, HIGH);
            delayMicroseconds(10000);
            digitalWrite(XStep, LOW);
            delayMicroseconds(10000);
      }
    if(xSwitch == HIGH){
           calibration = 2;
           delay(1000);
    }
    }
    /*********************
     * 
     * program begins
     * 
     **********************/
     //move gripper to start point
    if(calibration == 2){
      /*
         //xStepper('F', 23, 10000);
         xAxis(XBigCupLocation, XSpeed);
                     delay(1000);
            gripperServo.write(gripperOpen);
            delay(1000);
   // }
    // grab big cup and move and drop cup 
      gripperServo.write(gripperOpen);
      //yStepper('F', 3550, 1000);
      yAxis(YBigCupLocation, YSpeed);
      delay(1000);
      gripperServo.write(gripperClose);
      delay(1000);
      digitalWrite(LargeCup, HIGH);
      delay(50);
      digitalWrite(LargeCup, LOW);
      delay(1000);
      //yStepper('R', 3550, 1000);
      yAxis(0, 1000);
      delay(1000);
      //xStepper('F', 200, 10000);
      xAxis(223, 10000);
      delay(1000);
      gripperServo.write(gripperOpen);
      delay(1000);
      //gripperServo.write(25);
      //xStepper('R', 140, 10000);
      // grab small cup
      xAxis(XSmallCupLocation, XSpeed);
      //yStepper('F', 2950, 1000);
      yAxis(YSmallCupLocation, YSpeed);
      delay(1000);
      gripperServo.write(gripperClose);
      delay(1000);
      digitalWrite(SmallCup, HIGH);
      delay(50);
      digitalWrite(SmallCup, LOW);
      delay(1000);
      //yStepper('R', 3150, 1000);
      yAxis(0, 1000);
      */
      //mixerHigh();
      //analogWrite(Mixer, 50);
      gripperServo.write(GripperClose);
      xAxis(XBigCupLocation, XSpeed);
      yAxis(YBigCupLocation, YSpeed);
      delay(5000);
      yAxis(0, YSpeed);
      calibration = 4;
      xAxis(XSmallCupLocation, XSpeed);
      yAxis(YSmallCupLocation, YSpeed);
      delay(5000);
      yAxis(0, YSpeed);
      xAxis(XSyrupLocation, XSpeed);
      delay(1000);
      xAxis(XMixerLocation, XSpeed);
      yAxis(YSmallCupLocation, YSpeed);
      delay(5000);
      yAxis(0, YSpeed);
      xAxis(XCapLocation, XSpeed);
      yAxis(YCapLocation, YSpeed);
      delay(1000);
      yAxis(0,YSpeed);
      xAxis(XPressLocation, XSpeed);
      delay(1000);
      //analogWrite(Mixer, 0);
      //xAxis(0, XSpeed);
      }
    }
  }
}

void xStepper(char dir, long steps, int stepSpeed){
//  Serial.println(dir);
  //Serial.println(steps);
  //Serial.println(stepSpeed);
  if(dir == 'R'){
    for(int i = 0; i < steps; i++){
              digitalWrite(XDir, HIGH);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
            //  Serial.print("i:  ");
           //   Serial.println(i);
              /*
               for(int j = 0; j <= (steps/2); j++){
              digitalWrite(xDir, LOW);
              digitalWrite(xStep, HIGH);
              delayMicroseconds(stepSpeed*(steps/2)/j);
              digitalWrite(xStep, LOW);
              delayMicroseconds(stepSpeed*(steps/2)/j);
               }

               for(int j = 0; j <= (steps/2); j++){
              digitalWrite(xDir, LOW);
              digitalWrite(xStep, HIGH);
              delayMicroseconds((stepSpeed*(steps/2)/((steps/2)-j);
              digitalWrite(xStep, LOW);
              delayMicroseconds((stepSpeed*(steps/2)/((steps/2)-j);
               }
               */
    }
    xLocation += steps;
  }
  if(dir == 'F'){
    for(int i = 0; i < steps; i++){
              digitalWrite(XDir, LOW);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
           //   Serial.print("i:  ");
         //     Serial.println(i);
    }
    xLocation -= steps;
  }
  return;
}

void yStepper(char dir, long steps, int stepSpeed){
  //  Serial.println(dir);
 // Serial.println(steps);
 // Serial.println(stepSpeed);
    if(dir == 'F'){
    for(int i = 0; i < steps; i++){
              digitalWrite(YDir, HIGH);
              digitalWrite(YStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(YStep, LOW);
              delayMicroseconds(stepSpeed);
            //  Serial.print("i:  ");
          //    Serial.println(i);
    }
    yLocation += steps;
  }
  if(dir == 'R'){
    for(int i = 0; i < steps; i++){
              digitalWrite(YDir, LOW);
              digitalWrite(YStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(YStep, LOW);
              delayMicroseconds(stepSpeed);
             // Serial.print("i:  ");
             // Serial.println(i);
    }
    yLocation -= steps;
  }
  return;
}

void yAxis(long location, int stepSpeed){
  if(yLocation == location){
    return;
  }
  if(yLocation < location){
      for(int i = 0; i < (location-yLocation); i++){
              digitalWrite(YDir, HIGH);
              digitalWrite(YStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(YStep, LOW);
              delayMicroseconds(stepSpeed);
      }
          yLocation += location-yLocation;
    }
    if(yLocation > location){
        for(int i = 0; i < (yLocation-location); i++){
              digitalWrite(YDir, LOW);
              digitalWrite(YStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(YStep, LOW);
              delayMicroseconds(stepSpeed);
      }
          yLocation -= yLocation-location;
    }
    return;
}
void xAxis(long location, int stepSpeed){
    if(xLocation == location){
    return;
  }
  if(xLocation < location){
    for(int i = 0; i < (location-xLocation); i++){
              digitalWrite(XDir, LOW);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
    }
    xLocation += location-xLocation;
  }
    if(xLocation > location){
    for(int i = 0; i < (xLocation-location); i++){
              digitalWrite(XDir,HIGH);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
    }
    xLocation -= xLocation-location;
  }
  return;
}
/*void mixerHigh(){
  mixerSpeed = 200;
  for(int i = 0; i < 10; i++){
    analogWrite(Mixer, mixerSpeed);
    delay(500);
    mixerSpeed -= 17;
  }
}
*/
