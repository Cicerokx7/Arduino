#include <Servo.h>
#include <RPLidar.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN        6

#define NUMPIXELS 24

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500

RPLidar lidar;

#define RPLIDAR_MOTOR 3 

Servo gripper;
Servo flag;

int unsafe = 100;
int rightAngle = 90;
int angleb = 0;
int red = 50;
int blue = 0;
int ledCount = 0;
int mode = 0;
int lidarcount = 0;



//servos
int gripperClose = 130;
int gripperOpen = 80;
int high = 10;
int low = 100;

void setup() {
  Serial3.begin(9600);
  lidar.begin(Serial1); 
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
pixels.begin();
    pixels.setPixelColor(0, pixels.Color(25, 0, 0));
    gripper.attach(9);
    flag.attach(12);
    gripper.write(gripperOpen);
    flag.write(low);
    delay(1);
    Serial.print("starting");
}
float minDistance = 100000;
float angleAtMinDist = 0;

void loop() {
  analogWrite(RPLIDAR_MOTOR, 255);
    if(ledCount < 2500){
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle = lidar.getCurrentPoint().angle; //anglue value in degree
  //  bool startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
  //  byte quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
 angleb = rightAngle;
  if (IS_OK(lidar.waitPoint())) {
    if(distance < 900){
      unsafe = 0;
      angleb = angle;
    }
    if(distance >= 900 && unsafe < 100){
      unsafe ++;
    }
  }
  else {
    analogWrite(RPLIDAR_MOTOR, 0);
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}
  ledCount = ledCount+1;
  if(ledCount == 2500){
          if(angleb >= 0 && angleb < 15){
    pixels.clear();
    pixels.setPixelColor(14, pixels.Color(red, 0, blue));
  }
  if(angleb >= 15 && angleb < 30){
    pixels.clear();
    pixels.setPixelColor(15, pixels.Color(red, 0, blue));
  }
  if(angleb >= 30 && angleb < 45){
    pixels.clear();
    pixels.setPixelColor(16, pixels.Color(red, 0, blue));
  }
  if(angleb >= 45 && angleb < 60){
    pixels.clear();
    pixels.setPixelColor(17, pixels.Color(red, 0, blue));
  }
  if(angleb >= 60 && angleb < 75){
    pixels.clear();
    pixels.setPixelColor(18, pixels.Color(red, 0, blue));
  }
  if(angleb >= 75 && angleb < 90){
    pixels.clear();
    pixels.setPixelColor(19, pixels.Color(red, 0, blue));
  }
  if(angleb >= 90 && angleb < 105){
    pixels.clear();
    pixels.setPixelColor(20, pixels.Color(red, 0, blue));
  }
  if(angleb >= 105 && angleb < 120){
    pixels.clear();
    pixels.setPixelColor(21, pixels.Color(red, 0, blue));
  }
  if(angleb >= 120 && angleb < 135){
    pixels.clear();
    pixels.setPixelColor(22, pixels.Color(red, 0, blue));
  }
  if(angleb >= 135 && angleb < 150){
    pixels.clear();
    pixels.setPixelColor(23, pixels.Color(red, 0, blue));
  }
  if(angleb >= 150 && angleb < 165){
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(red, 0, blue));
  }
  if(angleb >= 165 && angleb < 180){
    pixels.clear();
    pixels.setPixelColor(1, pixels.Color(red, 0, blue));
  }
  if(angleb >= 180 && angleb < 195){
    pixels.clear();
    pixels.setPixelColor(2, pixels.Color(red, 0, blue));
  }
  if(angleb >= 195 && angleb < 210){
    pixels.clear();
    pixels.setPixelColor(3, pixels.Color(red, 0, blue));
  }
  if(angleb >= 210 && angleb < 225){
    pixels.clear();
    pixels.setPixelColor(4, pixels.Color(red, 0, blue));
  }
  if(angleb >= 225 && angleb < 240){
    pixels.clear();
    pixels.setPixelColor(5, pixels.Color(red, 0, blue));
  }
  if(angleb >= 240 && angleb < 255){
    pixels.clear();
    pixels.setPixelColor(6, pixels.Color(red, 0, blue));
  }
  if(angleb >= 255 && angleb < 270){
    pixels.clear();
    pixels.setPixelColor(7, pixels.Color(red, 0, blue));
  }
  if(angleb >= 270 && angleb < 285){
    pixels.clear();
    pixels.setPixelColor(8, pixels.Color(red, 0, blue));
  }
  if(angleb >= 285 && angleb < 300){
    pixels.clear();
    pixels.setPixelColor(9, pixels.Color(red, 0, blue));
  }
  if(angleb >= 300 && angleb < 315){
    pixels.clear();
    pixels.setPixelColor(10, pixels.Color(red, 0, blue));
  }
  if(angleb >= 315 && angleb < 330){
    pixels.clear();
    pixels.setPixelColor(11, pixels.Color(red, 0, blue));
  }
  if(angleb >= 330 && angleb < 345){
    pixels.clear();
    pixels.setPixelColor(12, pixels.Color(red, 0, blue));
  }
  if(angleb >= 345 && angleb < 360){
    pixels.clear();
    pixels.setPixelColor(13, pixels.Color(red, 0, blue));
  }
      pixels.show();
    ledCount = 0;
  }




  
           if(rightAngle <= 5 && rightAngle >= 0){
            rightAngle = 350;
          }
          if(rightAngle >= 355 && rightAngle <= 360){
            rightAngle = 10;
          }
    //}

if(lidarcount == 100){
  lidarcount = 0;
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
      if(Q=="on"){
        mode = 1;
        Serial3.println("on");
        }
        if(mode == 1){
          if(unsafe == 100){
            Serial3.println(angleb);
          }
          else{
            Serial3.println("go");
          }
        }
      }
lidarcount = lidarcount+1;
}
