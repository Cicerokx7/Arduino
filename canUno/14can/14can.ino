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
int leftAngle = 270;
float frontCheck = 0;
float backCheck = 0;
int error = 2;
int rightCount = 0;
int leftCount = 0;
int frontCount = 0;
int backCount = 0;
int angleb = 0;
int red = 0;
int blue = 0;
int counterSpeed = 0;
int wiseSpeed = 0;
int ledCount = 0;
int goalO = 0;
int goalT = 0;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  lidar.begin(Serial1);
  pinMode(13, OUTPUT);
  pinMode(RPLIDAR_MOTOR, OUTPUT);
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
pixels.begin();
    pixels.setPixelColor(0, pixels.Color(25, 0, 0));
    delay(1);
    Serial.print("begining");
    pinMode(8, OUTPUT);
    pinMode(8, HIGH);
}

void loop() {
    if(ledCount < 2500){
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle = lidar.getCurrentPoint().angle; //anglue value in degree
    bool startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
 angleb = rightAngle;
  if (IS_OK(lidar.waitPoint())) {
    

  
    if(angle > rightAngle-error && angle < rightAngle+error){
      rightWidth = distance;
      rightCount = 1;
    }
    if(angle > leftAngle-error && angle < leftAngle+error){
      leftWidth = distance;
      leftCount = 1;
    }
    if(angle > rightAngle-4-error && angle < rightAngle-4+error){
      frontCheck = distance;
      frontCount = 1;
    }
    if(angle > rightAngle+4-error && angle < rightAngle+4+error){
      backCheck = distance;
      backCount = 1;
    }
if(rightCount == 1){

 rightCount = 0;
}
    /*
        if(rightCount == 1 && leftCount == 1){
    now = rightWidth+leftWidth;
    rightCount = 0;
    leftCount = 0;
   // Serial.println(now);
             if(stage == 0){
      width = now;
      stage = 1;
    }
      if(width+1000 > now && width-1000 < now){
      //  Serial.println("it's working");
      red = 0;
      blue = 25;
      }
      else{
  red = 25;
  blue = 0;
      }
    }
    */


    
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
      
      red = 0;
      blue = 25;
          Serial.println(rightAngle);
    }
    }
   // Serial.println(rightAngle);
  }
  else {
    analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor
    
    // try to detect RPLIDAR... 
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) {
       // detected...
       lidar.startScan();
       
       // start motor rotating at max allowed speed
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}
  //15
  //14
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
if(goalO == 1){
  pixels.setPixelColor(2, pixels.Color(0, 25, 0));
  pixels.setPixelColor(8, pixels.Color(0, 0, 0));
}
if(goalT == 1){
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));
  pixels.setPixelColor(8, pixels.Color(0, 25, 0));
}

      pixels.show();
      Serial.println("led ON");
    ledCount = 0;
  }





  
           if(rightAngle <= 5 && rightAngle >= 0){
            rightAngle = 350;
          }
          if(rightAngle >= 355 && rightAngle <= 360){
            rightAngle = 10;
          }
/*if(Q == "2"){
  pixels.setPixelColor(2, pixels.Color( 0, 0, 0));
      pixels.setPixelColor(7, pixels.Color( 0, 25, 0));
}*/


String readString;
String Q;

//-------------------------------Check Serial Port---------------------------------------
 
 while (Serial2.available()){
  delay(1);
  if(Serial2.available()>0){
  char c = Serial2.read();
   if (isControl(c)){
  break;
  }
   readString += c;
  }
 
 }

 Q = readString;
//--------Checking Serial Read----------
      if(Q=="on"){
        goalO = 1;
        goalT = 0;
        if(rightAngle > 80 && rightAngle < 100){
          Serial.print("please");
          Serial2.print("on");
        }

        }
      if(Q=="off"){
  goalO = 0;
  goalT = 1;
        if(rightWidth < 1000){
          Serial.print("please");
          Serial2.print("off");
        }
      }
}
