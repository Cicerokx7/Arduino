//#ifdef __AVR__
//#include <avr/power.h>
//#endif
//
//#define DELAYVAL 500

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>

Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5

double z = 0;
int angle = 0;
int fullAngle = 680;
int minAngle = fullAngle/4;
int maxAgnel = minAngle*3;

float now = 0;
int stage = 0;
int error = 2;
int goalO = 0;
int goalT = 0;
int place = 0;
int rotation = 1;
int can = 0;
int mode = 0;

int counter = 0;

void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G, lsm.LSM9DS1_ACCELDATARATE_10HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G, lsm.LSM9DS1_ACCELDATARATE_119HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G, lsm.LSM9DS1_ACCELDATARATE_476HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G, lsm.LSM9DS1_ACCELDATARATE_952HZ);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
//  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}

void setup() {
  Serial3.begin(9600);
//  Serial.begin(9600);
  pinMode(13, OUTPUT);
//  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
//  clock_prescale_set(clock_div_1);
//#endif
  //  gripper.attach(9);
    //flag.attach(12);
//    gripper.write(gripperOpen);
  //  flag.write(low);
//    delay(1);
//    Serial.print("starting");

if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS1. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS1 9DOF");

  // helper to just set the default scaling we want, see above!
  setupSensor();
}

void loop() {
//    if(mode == 0){
//  mode = 1;
////  Serial1.print("running");
//    }
if(counter < 1000){
  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 
    z += g.gyro.z;
    angle = int(z)%fullAngle;
  }
else{
  counter = 0;
String readString;
String Q;
 while (Serial3.available()){
  delay(1);
  if(Serial3.available()>0){
  char c = Serial3.read();
   if (isControl(c)){
  break;
  }
   readString += c;
  }
 
 }

 Q = readString;
// Serial.println(mode);
      if(Q=="on"){
        mode = 1;
        z = 0;
        }
        if(mode != 0 && (angle < minAngle || angle > maxAngle)){
          Serial3.println("good");
          }
}
count ++;
}
