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
const int XDir = 6;
const int XStep = 7;
const int YDir = 12;
const int YStep = 4;
const int YEnable = 38;
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
const int MixerCleaner = 5;
//Cap Dispenser
const float STEPS_PER_REV = 32;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV*GEAR_RED;
int StepsRequired;
short wormGearPointer = 0;
//Stepper wormGearOne(STEPS_PER_REV, 38, 42, 40, 44);
Stepper capDispenser(STEPS_PER_REV, 38, 42, 40, 44);//37, 34, 35, 36);
//Stepper wormGearThree(STEPS_PER_REV, 39, 43, 41, 45);


/*********************************
 *       stepper variables       *
 *********************************/
int xLocation = 0;
long yLocation = 0;
short calibration = 0;
short count = 0;
//const int yMax = 5850;
const long YMax = 5725; // speed 1000
const int XMax = 500; // speed 10000
const int XSpeed = 1500;
const int YSpeed = 675;//can run at least 625 speed but strength and reliability become impractical

/*************************
 *       locations       *
 *************************/
//Gripper
const int GripperPartialOpen = 75;//70
const int GripperOpen = 165;//150
const int GripperClose = 60;//30
const int GripperFullClose = 60;//30
//Cap Press
const float PressMax = 957.0;
const float PressStart = 0.0;
const float PressHoldLargeCup = 35.0;
const float PressLargeCup = 10.0;
const float PressSmallCup = 2.0;
const float PressMin = 1.09;
//Stepper Motors
const int XBigCupLocation = 45; // speed 10000  ^
const int YBigCupLocation = 3600; // speed 1000  ^
const int XSmallCupLocation = 315; // speed 10000
const int YSmallCupLocation = 3090; // speed 1000
const int XSyrupLocation = 405; // speed 10000
const int XMixerLocation = 1190; // speed 10000  ^
const int YMixerLocation = 2900;  // speed 1000
const int XCapLocation = 1473; // speed 10000
const int YCapLocation = 1095;//2300; //speed 1000
const int XPresssStopLocation = 1650; // speed 10000'
const int YPressLocation = 500;//2300; //speed 1000
const int YPressReleaseLocation = 200;//speed 1000
const int XPressLocation = 1810; // speed 10000
int testError = 0;


/*************************
 *       variables       *
 *************************/
int mixerSpeed = 0;
long pressLocationCount = 0;
int pressCount = 0;
/*************************
 *       Resources       *
 ************************/
 int largeCups = 17;
 int caps = 20;
// int syrupOne = 1000;

void setup() {
  //PC Comunication
  Serial.begin(9600);
  Serial.println("Stepper test!");
  
  //Gripper
    gripperServo.attach(21);
    //45-75
    
    /***********************
     *       PinMode       *
     ***********************/
    //Stepper Motors
    pinMode(XSwitchInput, INPUT);
    pinMode(YSwitchInput, INPUT);
    pinMode(XDir, OUTPUT);
    pinMode(XStep, OUTPUT);
    pinMode(YEnable, OUTPUT);
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
    pinMode(MixerCleaner, OUTPUT);

    /**********************
     *       Preset       *
     **********************/
    //Stepper Motors
    digitalWrite(XDir, LOW);
    digitalWrite(XStep, LOW);
    digitalWrite(YEnable, HIGH);
    digitalWrite(YDir, LOW);
    digitalWrite(YStep, LOW);
    //Cap Press
    analogWrite(PressPWM, 0);
    digitalWrite(PressUp, LOW);
    digitalWrite(PressDown, LOW);
    //Dispensers
    digitalWrite(LargeCup, LOW);
    digitalWrite(SmallCup, LOW);
    digitalWrite(34, LOW);
    digitalWrite(35, LOW);
    digitalWrite(36, LOW);
    digitalWrite(37, LOW);
    //Syrup
    analogWrite(SyrupOnePWM, 0);
    digitalWrite(SyrupOneIn, LOW);
    digitalWrite(SyrupOneOut, LOW);
    //Mixer
    analogWrite(MixerPWM, 0);
    digitalWrite(MixerCW, LOW);
    digitalWrite(MixerCCW, LOW);
    digitalWrite(MixerCleaner, LOW);
    
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
    Serial.println("test");
    capPress(PressMax);
    Serial.println("testOne");
    calibration = 1;
  }
  if(calibration == 1){
    StepsRequired = STEPS_PER_OUT_REV;
    capDispenser.setSpeed(300);
    calibration = 2;
  }
  if(calibration == 2){
    digitalWrite(YEnable, LOW);
    digitalWrite(YDir, LOW);
    for(int i = 0; i < 50; i++){
      digitalWrite(YStep, HIGH);
      delayMicroseconds(YSpeed);
      digitalWrite(YStep, LOW);
      delayMicroseconds(YSpeed);
    }
    if(ySwitch == LOW){
      count = 0;
    }
    if(ySwitch == HIGH){
     count ++;
    }
    if(count == 3){
      count = 0;
      digitalWrite(YEnable, LOW);
      calibration = 3;
    }
  }
    //press setup
  if(calibration == 3){
    calibration = 4;
  }
  //y axis setup
  if(calibration == 4){
    delay(1000);
    calibration = 5;
  }
  if(calibration == 5){
    gripperServo.write(GripperFullClose);
    if(xSwitch == LOW){
      digitalWrite(XDir, LOW);
      digitalWrite(XStep, HIGH);
      delayMicroseconds(XSpeed*2);
      digitalWrite(XStep, LOW);
      delayMicroseconds(XSpeed*2);
    }
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
    if(largeCups < 1 || caps < 1){
      calibration = -1;
    }
    else{
      calibration = 7;
    }
  }
  if(calibration == 7){
    /******************************
     *       grab large cup       *
     ******************************/
    calibration = 8;
    xAxis(XBigCupLocation, XSpeed);
    gripperServo.write(GripperPartialOpen);
    yAxis(YBigCupLocation, YSpeed);
    gripperServo.write(GripperClose);
    delay(1000);
    yAxis(YBigCupLocation+200, YSpeed);
    digitalWrite(LargeCup, HIGH);
    yAxis(YBigCupLocation, YSpeed);
    digitalWrite(LargeCup, LOW);
    largeCups --;
    
    //add syrup
    yAxis(0, YSpeed);
    xAxis(XSyrupLocation, XSpeed);
    syrup(1, 3000);
    //mix
    xAxis(XMixerLocation, XSpeed);
    yAxis(YMixerLocation, YSpeed);
    mixer(50, 2000);
    
    
    //cap dispense
    xAxis(XCapLocation, XSpeed);
    yAxis(YCapLocation, YSpeed);
    capDispenser.setSpeed(300);
    capDispenser.step(-StepsRequired/2);
    caps --;
    yAxis(0,YSpeed);
      
    //cap press
    xAxis(XPresssStopLocation, XSpeed);
    yAxis(YPressLocation,YSpeed);
    xAxis(XPressLocation, XSpeed);
    delay(5000);
    yAxis(YPressReleaseLocation,YSpeed);
    capPress(PressHoldLargeCup);
    gripperServo.write(GripperOpen);
    capPress(PressLargeCup);
    capPress(PressMax);
    calibration = 8;
  }
  if(calibration == 8){
    digitalWrite(MixerCleaner, HIGH);
    mixer(50, 1000);
    digitalWrite(MixerCleaner, LOW);
    delay(5000);
    gripperServo.write(GripperClose);
    yAxis(0,YSpeed);
    delay(1000);
    calibration = 6;
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
              digitalWrite(XDir, LOW);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
    }
    xLocation += steps;
  }
  if(dir == 'F'){
    for(int i = 0; i < steps; i++){
              digitalWrite(XDir, HIGH);
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
    digitalWrite(YEnable, LOW);
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
  digitalWrite(YEnable, HIGH);
  return;
}

void yAxis(long location, int stepSpeed){
  if(yLocation == location){
    return;
  }
  digitalWrite(YEnable, LOW);
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
    digitalWrite(YEnable, HIGH);
    return;
}
void xAxis(long location, int stepSpeed){
  if(xLocation == location){
    return;
  }
  if(xLocation < location){
    for(int i = 0; i < (location-xLocation); i++){
              digitalWrite(XDir, HIGH);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
    }
    xLocation += location-xLocation;
  }
    if(xLocation > location){
    for(int i = 0; i < (xLocation-location); i++){
              digitalWrite(XDir,LOW);
              digitalWrite(XStep, HIGH);
              delayMicroseconds(stepSpeed);
              digitalWrite(XStep, LOW);
              delayMicroseconds(stepSpeed);
    }
    xLocation -= xLocation-location;
  }
  Serial.println(xLocation);
  return;
}

/*************************
 *       Cap Press       *
 *************************/
 void capPress(float location){
  while(pressCount < 600){
  pressLocation = analogRead(PressLocationInput);
    pressLocationCount += pressLocation;
    pressCount ++;
    if(pressCount == 500){
      pressLoc = pressLocationCount/500.0;
      pressLocationCount = 0;
      pressCount = 0;
  if(pressLoc < location){
    while(pressLoc < location){
      pressLocation = analogRead(PressLocationInput);
      if(pressCount == 100){
       pressLoc = pressLocationCount/100.0;
       pressLocationCount = 0;
        pressCount = 0;
      }
      pressLocationCount += pressLocation;
      pressCount ++;
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
      pressLocation = analogRead(PressLocationInput);
       if(pressCount == 100){
         pressLoc = pressLocationCount/100.0;
         pressLocationCount = 0;
         pressCount = 0;
       }
       pressLocationCount += pressLocation;
       pressCount ++;
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
