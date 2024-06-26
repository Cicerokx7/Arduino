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

float width = 0;
float rightWidth = 0;
float leftWidth = 0;
float now = 0;
int stage = 0;
int rightAngle = 90;
int frontAngle = 0;
int backAngle = 180;
int leftAngle = 270;
float frontDist = 0;
float backDist = 0;
float frontCheck = 0;
float backCheck = 0;
float fRCheck = 0;
float bRCheck = 0;
float fFCheck = 0;
float bFCheck = 0;
float fLCheck = 0;
float bLCheck = 0;
float fBCheck = 0;;
float bBCheck = 0;
int error = 2;
int frontCount = 0;
int backCount = 0;
int frontCount = 0;
int backCount = 0;
int fRCount = 0;
int bRCount = 0;
int fFCount = 0;
int bFCount = 0;
int fLCount = 0;
int bLCount = 0;
int fBCount = 0;
int bBcount = 0;
int angleb = 0;
int red = 0;
int blue = 0;
int counterSpeed = 0;
int wiseSpeed = 0;
int ledCount = 0;
int goalO = 0;
int goalT = 0;
int place = 0;
int rotation = 1;
int can = 0;
int mode = 0;
int lidarcount = 0;
int right = 0;
int left = 0;

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
    if(mode == 100){
  mode = 0;
  Serial1.print("running");
    }
    if(mode == 3 || mode == 30 || mode == 40 || mode == 60 || mode == 80){
      if(angle > rightAngle-error && angle < rightAngle+error){
         rightWidth = distance;
         rightCount = 1;
      }
    }
    if(angle > rightAngle-4-error && angle < rightAngle-4+error){
      fRCheck = distance;
      fRCount = 1;
    }
    if(angle > rightAngle+4-error && angle < rightAngle+4+error){
      bRCheck = distance;
      bRCount = 1;
    }
    if(fRCount == 1 $$ bRCount == 1 && fRCount-bRCount < 1000){
      frontCheck += fRCount;
      backCheck += bRCount
    }

if(rightCount == 1 && mode == 3 ){
  //1067
  if(rightWidth < 1067){
    Serial1.println(rightWidth);
    blue = 25;
    red = 0;
    mode = 30;
  }
  if(rightWidth > 1067){
    Serial1.println(rightWidth);
    blue = 0;
    red = 25;
    mode = 60;
  }
  rightCount = 0;
}
    
    if(frontCount == 1 && backCount == 1){
      if(frontCheck > 0 && backCheck > 0){
         backCount = 0;
         frontCount = 0;
      
      if(frontCheck > backCheck || frontCheck < backCheck){
        if(frontCheck > backCheck){
          if(frontCheck-backCheck > 10){
  rightAngle = rightAngle+5;
leftAngle = leftAngle+5;
        }
        if(frontCheck-backCheck < 10){
          rightAngle = rightAngle+1;
          leftAngle = leftAngle+1;
        }
        }
        if(frontCheck < backCheck){
          if(backCheck-frontCheck > 10){
          rightAngle = rightAngle-5;
leftAngle = leftAngle-5;
          }
          if(backCheck-frontCheck < 10){
            rightAngle = rightAngle-1;
            leftAngle = leftAngle-1;
          }
        }
      }
    }
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
if(mode < 3){
  pixels.setPixelColor(8, pixels.Color(0, 25, 0));
  pixels.setPixelColor(20, pixels.Color(0, 25, 0));
}
if(mode == 30 || mode == 40){
  pixels.setPixelColor(2, pixels.Color(0, 25, 0));
}
if(mode == 60 || mode == 80){
  pixels.setPixelColor(14, pixels.Color(0, 25, 0));
}
if(mode > 4 && mode < 7){
  pixels.setPixelColor(20, pixels.Color(0, 25, 0));
}
if(mode == 7){
  pixels.setPixelColor(7, pixels.Color(0, 25, 0));
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
    }

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
 Serial.println(mode);
      if(Q=="on"){
        mode = 1;
        Serial.println("ON!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        }
        if(mode < 5 && mode != 0){
          if(mode == 1){
            Serial.println("right");
            Serial3.println("right");
          }
        if(rightAngle > 80 && rightAngle < 180){
          mode = 2;
        }
        if(mode == 2){
          
          Serial.println("left");
          Serial3.println("left");
        }
        if(rightAngle > 180 && rightAngle < 280){ 
          mode = 1;
        }

}
lidarcount = lidarcount+1;
}
