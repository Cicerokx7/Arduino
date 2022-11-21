#include <Servo.h>
#include <Stepper.h>

Servo gripperServo;

/**************************
 *       pin naming       *
 **************************/
//Stepper Calibration
const int YSwitchInput = 48;
int ySwitch = 0;
const int XSwitchInput = 46;
int xSwitch = 0;
//Stepper
const int XDir = 7;
const int XStep = 6;
const int YDir = 12;
const int YStep = 4;
//Cup Dispensers
const int LargeCup = 52;
const int SmallCup = 23;
//const int CapDispenser = 50;
//Syrup
const int SyrupOnePWM = 8;//8
const int SyrupOneIn = 26;//28
const int SyrupOneOut = 27;//29
//Cap Press
const int PressPWM = 9;//9
const int PressUp = 25;
const int PressDown = 24;
const int PressLocationInput = A0;
int pressLocation = 0;
float pressLoc = 0;
//Mixer
const int MixerPWM = 10;
const int MixerCW = 28;
const int MixerCCW = 29;
//Cap Dispenser
const float STEPS_PER_REV = 32;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV*GEAR_RED;
int StepsRequired;
Stepper steppermotor(STEPS_PER_REV, 35, 39, 37, 41);


/*********************************
 *       stepper variables       *
 *********************************/
int xLocation = 0;
long yLocation = 0;
short calibration = 6;//-1
short count = 0;
//const int yMax = 5850;
const long YMax = 5725; // speed 1000
const int XMax = 500; // speed 10000
int stepSpeed = 1000;
const int XSpeed = 10000;
const int YSpeed = 1000;

/*************************
 *       locations       *
 *************************/
//Gripper
const int GripperPartialOpen = 82;//70
const int GripperOpen = 170;//150
const int GripperClose = 65;//30
const int GripperFullClose = 60;//30
//Cap Press
const float PressMax = 957.0;
const float PressStart = 0.0;//
const float PressLargeCup = 25.0;
const float PressSmallCup = 2.0;
const float PressMin = 1.09;
//Stepper Motors
const int XBigCupLocation = 29; // speed 10000  ^
const int YBigCupLocation = 3550; // speed 1000  ^
const int XSmallCupLocation = 87 ; // speed 10000
const int YSmallCupLocation = 2850; // speed 1000
const int XSyrupLocation = 150; // speed 10000
const int XPressLocation = 327; // speed 10000
const int XCapLocation = 420; // speed 10000
const int YCapLocation = 400;//2300; //speed 1000
const int XMixerLocation = 503; // speed 10000  ^
const int YMixerLocation = 4485;  // speed 1000


/*************************
 *       variables       *
 *************************/
int mixerSpeed = 0;
long pressLocationCount = 0;
int pressCount = 0;

void setup() {
  //PC Comunication
  Serial.begin(9600);
  Serial.println("Stepper test!");
  
  //Gripper
    gripperServo.attach(21);
    gripperServo.write(GripperOpen);
    //45-75
    
    /***********************
     *       PinMode       *
     ***********************/
    //Stepper Motors
    pinMode(XSwitchInput, INPUT);
    pinMode(YSwitchInput, INPUT);
    pinMode(XDir, OUTPUT);
    pinMode(XStep, OUTPUT);
    pinMode(YDir, OUTPUT);
    pinMode(YStep, OUTPUT);
    //Cap Press
    pinMode(PressLocationInput, INPUT);
    pinMode(PressPWM, OUTPUT);
    pinMode(PressUp, OUTPUT);
    pinMode(PressDown, OUTPUT);
    //Dispensers
//    pinMode(CapDispenser, OUTPUT);
    pinMode(LargeCup, OUTPUT);
    pinMode(SmallCup, OUTPUT);
    //Syrup
    pinMode(SyrupOnePWM, OUTPUT);
    pinMode(SyrupOneIn, OUTPUT);
    pinMode(SyrupOneOut, OUTPUT);
    //Mixer
    pinMode(MixerPWM, OUTPUT);
    pinMode(MixerCW, OUTPUT);
    pinMode(MixerCCW, OUTPUT);

    /**********************
     *       Preset       *
     **********************/
    //Stepper Motors
    digitalWrite(XDir, LOW);
    digitalWrite(XStep, LOW);
    digitalWrite(YDir, LOW);
    digitalWrite(YStep, LOW);
    //Cap Press
    analogWrite(PressPWM, 0);
    digitalWrite(PressUp, LOW);
    digitalWrite(PressDown, LOW);
    //Dispensers
//    digitalWrite(CapDispenser, LOW);
    digitalWrite(LargeCup, LOW);
    digitalWrite(SmallCup, LOW);
    //Syrup
    analogWrite(SyrupOnePWM, 0);
    digitalWrite(SyrupOneIn, LOW);
    digitalWrite(SyrupOneOut, LOW);
    //Mixer
    analogWrite(MixerPWM, 0);
    digitalWrite(MixerCW, LOW);
    digitalWrite(MixerCCW, LOW);
}

/***********************************
 *       function prototypes       *
 ***********************************/
//Stepper Motors
void xStepper(char, long, int); 
void yStepper(char, long, int);
void xAxis(long, int);
void yAxis(long, int);
//Cap Press
void capPress(float);
//Syrup
void syrup(int, int);
//Mixer
void mixer(int, int);

void loop() {
  while(xLocation <= XMax){
    while(yLocation <= YMax){
     /******************************
      *       Set Input Vars       *
      ******************************/
    xSwitch = digitalRead(XSwitchInput);
    
    ySwitch = digitalRead(YSwitchInput);
    /***********************************
    *                                  *
    *       STEPPER CALIBRATION        *
    *                                  *
    ***********************************/
    if(calibration == 0){
      capPress(100);
      capPress(PressMax);
      calibration = 1;
    }
    if(calibration == 1){
      StepsRequired = STEPS_PER_OUT_REV;
      steppermotor.setSpeed(300);
      //calibrate cap dispenser steppers;
      steppermotor.step(-StepsRequired/2);
      delay(1000);
      steppermotor.step(-StepsRequired/2);
      delay(5000);
      calibration = 2;
    }
    if(calibration == 2){
          Serial.println("Stepper Calibration");
    Serial.println(calibration);
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
      calibration = 3;
      Serial.println("stop");
    }
    }
    //press setup
    if(calibration == 3){
      Serial.println("Stepper Calibration");
    Serial.println(calibration);
      calibration = 4;
    }
    //y axis setup
    if(calibration == 4){
      Serial.println("Stepper Calibration");
    Serial.println(calibration);
      delay(1000);
      calibration = 5;
    }
    //x axis setup
    if(calibration == 5){
      gripperServo.write(GripperFullClose);
      if(xSwitch == LOW){
        Serial.println("please");
            digitalWrite(XDir, HIGH);
            digitalWrite(XStep, HIGH);
            delayMicroseconds(10000);
            digitalWrite(XStep, LOW);
            delayMicroseconds(10000);
            Serial.println(xSwitch);
      }
      Serial.println("test");
    if(xSwitch == HIGH){
           calibration = 6;
           gripperServo.write(GripperFullClose);
           delay(1000);
    }
    }
    /*********************
     * 
     * program begins
     * 
     **********************/
    if(calibration == 6){
      Serial.println("calibration 4 please work");
      /******************************
       *       grab large cup       *
       ******************************/
       /*
      calibration = 5; 
      xAxis(XBigCupLocation, XSpeed);
      gripperServo.write(GripperPartialOpen);
      yAxis(YBigCupLocation, YSpeed);
      gripperServo.write(GripperClose);
      delay(1000);
      yAxis(YBigCupLocation+200, YSpeed);
      digitalWrite(LargeCup, HIGH);
      //delay(110);
      yAxis(YBigCupLocation, YSpeed);
      digitalWrite(LargeCup, LOW);
      //delay(1000);
      
      //add syrup
      yAxis(0, YSpeed);
      /*
      xAxis(XSyrupLocation, XSpeed);
      syrup(1, 30000);
      
      //mix
      xAxis(XMixerLocation, XSpeed);
      yAxis(YSmallCupLocation, YSpeed);
      mixer(50, 10000);
      */
      //cap dispense
      /*
      xAxis(XCapLocation, XSpeed);
      yAxis(YCapLocation, YSpeed);
      */
//      digitalWrite(CapDispenser, HIGH);
//      delay(50);
//      digitalWrite(CapDispenser, LOW);
//      delay(1000);
      .step(-StepsRequired/2);
      delay(1000);
      steppermotor.step(-StepsRequired/2);
      delay(5000);
      yAxis(0,YSpeed);
      
      //cap press
      xAxis(XPressLocation, XSpeed);//
      gripperServo.write(GripperOpen);
      
      capPress(PressLargeCup);
      capPress(PressMax);
      calibration = 7;
      
      }
      /*
      if(calibration == 7){
      xAxis(XBigCupLocation, XSpeed);
      gripperServo.write(GripperPartialOpen);
      yAxis(YBigCupLocation, YSpeed);
      gripperServo.write(GripperClose);
      delay(1000);
      yAxis(YBigCupLocation+200, YSpeed);
      digitalWrite(LargeCup, HIGH);
      //delay(110);
      yAxis(YBigCupLocation, YSpeed);
      digitalWrite(LargeCup, LOW);
      //delay(1000);
      
      //add syrup
      yAxis(0, YSpeed);
      }
      */
    }
  }
}

/*********************************************************
 *                                                       *
 *                      functions                        *
 *                                                       *
 *********************************************************/

 /******************************
  *       Stepper Motors       *
  ******************************/
void xStepper(char dir, long steps, int stepSpeed){
  if(dir == 'R'){
    for(int i = 0; i < steps; i++){
              digitalWrite(XDir, HIGH);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
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
    }
    xLocation -= steps;
  }
  return;
}

void yStepper(char dir, long steps, int stepSpeed){
    if(dir == 'F'){
    for(int i = 0; i < steps; i++){
              digitalWrite(YDir, HIGH);
              digitalWrite(YStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(YStep, LOW);
              delayMicroseconds(stepSpeed);
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

/*************************
 *       Cap Press       *
 *************************/
 void capPress(float location){
  while(pressCount < 600){
  pressLocation = analogRead(PressLocationInput);
    pressLocationCount += pressLocation;
    Serial.println(pressCount);
    pressCount ++;
    if(pressCount == 500){
      pressLoc = pressLocationCount/500.0;
      pressLocationCount = 0;
      pressCount = 0;
  if(pressLoc < location){
    while(pressLoc < location){
      Serial.print(location);
      Serial.print(", ");
      Serial.println(pressLoc);
      pressLocation = analogRead(PressLocationInput);
      if(pressCount == 100){
       pressLoc = pressLocationCount/100.0;
       pressLocationCount = 0;
        pressCount = 0;
      }
      pressLocationCount += pressLocation;
      pressCount ++;
      //Serial.println(pressLoc);
     // Serial.println(location);
          analogWrite(PressPWM, 255);
          digitalWrite(PressUp, HIGH);
          digitalWrite(PressDown, LOW);
    }
    analogWrite(PressPWM, 0);
    digitalWrite(PressUp, LOW);
    digitalWrite(PressDown, LOW);
    return;
  }
  else if(pressLoc > location){
    while(pressLoc > location){
      Serial.print(location);
      Serial.print(", ");
      Serial.println(pressLoc);
      pressLocation = analogRead(PressLocationInput);
       if(pressCount == 100){
         pressLoc = pressLocationCount/100.0;
         pressLocationCount = 0;
         pressCount = 0;
       }
       pressLocationCount += pressLocation;
       pressCount ++;
    //  Serial.println(pressLoc);
     // Serial.println(location);
      analogWrite(PressPWM, 255);
      digitalWrite(PressUp, LOW);
      digitalWrite(PressDown, HIGH);
    }
    analogWrite(PressPWM, 0);
    digitalWrite(PressUp, LOW);
    digitalWrite(PressDown, LOW);
    return;
  }
  else{
    return;
  }
    }
  }
 }

/*********************
 *       Syrup       *
 *********************/
 void syrup(int num, int timer){
  switch(num){
    case 1:
      analogWrite(SyrupOnePWM, 255);
      digitalWrite(SyrupOneOut, HIGH);
      digitalWrite(SyrupOneIn, LOW);
      delay(timer);
      analogWrite(SyrupOnePWM, 255);
      digitalWrite(SyrupOneOut,LOW);
      digitalWrite(SyrupOneIn, HIGH);
      delay(1000);
      analogWrite(SyrupOnePWM, 0);
      digitalWrite(SyrupOneOut, LOW);
      digitalWrite(SyrupOneIn, LOW);
      break;
     default:
      Serial.println("ERROR");
      break;
  }
  return;
 }

/*********************
 *       Mixer       *
 *********************/
void mixer(int power, int timer){
      analogWrite(MixerPWM, power);
      digitalWrite(MixerCW, HIGH);
      digitalWrite(MixerCCW, LOW);
      delay(timer);
      analogWrite(MixerPWM, 0);
      digitalWrite(MixerCW, LOW);
      digitalWrite(MixerCCW, LOW);
      yAxis(0, YSpeed);
      return;
}
