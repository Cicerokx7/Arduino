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
const int XSpeed = 175;
const int YSpeed = 675;//can run at least 625 speed but strength and reliability become impractical

/*************************
 *       locations       *
 *************************/
//Gripper
const int GripperPartialOpen = 80;//70
const int GripperOpen = 170;//150
const int GripperClose = 60;//30
const int GripperFullClose = 60;//30
//Cap Press
const float PressMax = 957.0;
const float PressStart = 0.0;
const float PressLargeCup = 15.0;
const float PressSmallCup = 2.0;
const float PressMin = 1.09;
//Stepper Motors
const int XBigCupLocation = 85; // speed 10000  ^
const int YBigCupLocation = 3600; // speed 1000  ^
const int XSmallCupLocation = 315; // speed 10000
const int YSmallCupLocation = 3090; // speed 1000
const int XSyrupLocation = 405; // speed 10000
const int XMixerLocation = 1210; // speed 10000  ^
const int YMixerLocation = 2900;  // speed 1000
const int XCapLocation = 1475; // speed 10000
const int YCapLocation = 1100;//2300; //speed 1000
const int XPresssStopLocation = 1650; // speed 10000'
const int YPressLocation = 500;//2300; //speed 1000
const int YPressReleaseLocation = 200;//speed 1000
const int XPressLocation = 1800; // speed 10000


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
    //gripperServo.write(GripperOpen);
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
//    digitalWrite(CapDispenser, LOW);
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
//capDispenser
//void capDispenser(short);
//void capDispenser(int, int);
 int x = 0;
 int xPast = 0;
 int y = 0;
 int yPast = 0;
 int state = 0;

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
    /*
    capPress(100);
    capPress(PressMax);
    Serial.println("testOne");
    */
    calibration = 1;
  }
  if(calibration == 1){
//    Serial.println("testTwo");
    StepsRequired = STEPS_PER_OUT_REV;
    capDispenser.setSpeed(300);
    /*
    Serial.println("testThree");
    capDispenser.step(-StepsRequired/2);
    //calibrate cap dispenser steppers;
    /*
    steppermotor.step(-StepsRequired/2);
    delay(1000);
    steppermotor.step(-StepsRequired/2);
    delay(5000);
    */
    calibration = 2;
  }
  if(calibration == 2){
//    Serial.println("Stepper Calibration");
//    Serial.println(calibration);
    digitalWrite(YEnable, LOW);
    digitalWrite(YDir, LOW);
    for(int i = 0; i < 50; i++){
      digitalWrite(YStep, HIGH);
      delayMicroseconds(YSpeed);
      digitalWrite(YStep, LOW);
      delayMicroseconds(YSpeed);
    }
//    Serial.println(ySwitch);
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
//      Serial.println("stop");
    }
  }
    //press setup
  if(calibration == 3){
//    Serial.println("Stepper Calibration");
//    Serial.println(calibration);
    calibration = 4;
  }
  //y axis setup
  if(calibration == 4){
//    Serial.println("Stepper Calibration");
//    Serial.println(calibration);
    delay(1000);
    calibration = 5;
  }
  //x axis setup
  if(calibration == 5){
    gripperServo.write(GripperFullClose);
    if(xSwitch == LOW){
//      Serial.println("please");
      digitalWrite(XDir, LOW);
      digitalWrite(XStep, HIGH);
      delayMicroseconds(XSpeed*2);
      digitalWrite(XStep, LOW);
      delayMicroseconds(XSpeed*2);
//      Serial.println(xSwitch);
    }
//    Serial.println("test");
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
    String naim = "";  
    String Mobile = "";  
    String Address = "";  
    String Email = "";  
    String Q = "";
    int val = 0;
    Serial.println("Enter Command:");  
    while (Serial.available() == 0) {}  
    Q = Serial.readString();
    Serial.print(Q);
//    String Q;
//    while (Serial.available()){
//      Q = Serial.read();
//    }
//      Serial.println("Enter command:");
//      Serial.println(Q);
//      if(Q == "xpc"){
//        x += 100;
//      }
//      else if(Q == "xpl"){
//        x += 50;
//      }
//      else if(Q == "xpx"){
//        x += 10;
//      }
//      else if(Q == "xpv"){
//        x += 5;
//      }
//      else if(Q == "xpi"){
//        x += 1;
//      }
//      else if(Q == "xmc"){
//        x -= 100;
//      }
//      else if(Q == "xml"){
//        x -= 50;
//      }
//      else if(Q == "xmx"){
//        x -= 10;
//      }
//      else if(Q == "xmv"){
//        x -= 5;
//      }
//      else if(Q == "xmi"){
//        x -= 1;
//      }
//      else if(Q == "ypm"){
//        y += 1000;
//      }
//      else if(Q == "ypd"){
//        y += 500;
//      }
//      else if(Q == "ypc"){
//        y += 100;
//      }
//      else if(Q == "ypl"){
//        y += 50;
//      }
//      else if(Q == "ypx"){
//        y += 10;
//      }
//      else if(Q == "ypv"){
//        y += 5;
//      }
//      else if(Q == "ypi"){
//        y += 1;
//      }
//      else if(Q == "ymm"){
//        y -= 1000;
//      }
//      else if(Q == "ymd"){
//        y -= 500;
//      }
//      else if(Q == "ymc"){
//        y -= 100;
//      }
//      else if(Q == "yml"){
//        y -= 50;
//      }
//      else if(Q == "ymx"){
//        y -= 10;
//      }
//      else if(Q == "ymv"){
//        y -= 5;
//      }
//      else if(Q == "ymi"){
//        y -= 1;
//      }
      val = Q.toInt();
      if(val == 1){
        state = 1;
      }
      else if(val == 2){
        state = 2;
      }
      if(state == 1){
        Serial.println("In X");
        if(val != 0){
          x = val;
        }
        else if(val == 0){
          Serial.println("In Y");
          state = 2;
        }
      }
      else if(state == 2){
        Serial.println("In Y");
        if(val != 0){
          y = val;
        }
        else if(val == 0){
          Serial.println("In X");
          state = 1;
        }
      }
      if(xPast != x || yPast != y){
        Serial.print("X: ");
        Serial.print(x);
        Serial.print(";  Y: ");
        Serial.print(y);
        Serial.println(";");
        if(xPast != x){
          xAxis(x, XSpeed);
        }
        else{
          yAxis(y, YSpeed);
        }
      xPast = x;
      yPast = y;
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
//              Serial.println(xLocation);
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
//              Serial.println(xLocation);
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
