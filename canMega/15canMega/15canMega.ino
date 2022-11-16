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
int place = 0;
int rotation = 1;
int can = 0;
int mode = 0;

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
float minDistance = 100000;
float angleAtMinDist = 0;
void loop() {
  analogWrite(RPLIDAR_MOTOR, 255);
    if(can < 6){
    if(ledCount < 2500){
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle = lidar.getCurrentPoint().angle; //anglue value in degree
    bool startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
 angleb = rightAngle;
  if (IS_OK(lidar.waitPoint())) {
    
Serial.print(distance);
  
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
  pixels.setPixelColor(14, pixels.Color(0, 25, 0));
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
        mode = 1;
        }
        if(mode < 5 && mode != 0){
          if(mode == 1){
            Serial2.print("right");
          }
        if(rightAngle > 80 && rightAngle < 100){
          mode = 2;
        }
        if(mode == 2){
          Serial2.print("left");
        }
        if(rightAngle > 260 && rightAngle < 280){
          mode = 1;
        }
        if(Q == "one"){
          mode = 3;
        }
        }
        if(mode == 3){
          if(rightCount == 1){
            if(rightWidth < 100){
              mode = 30;
            }
            if(rightWidth > 130){
              mode = 60;
            }
            rightCount = 0;
          }
        }
         if(mode == 30){
        if(rightAngle > 190){
          Serial2.print("right");
        }
        if(rightAngle < 170){
          Serial2.print("left");
        }
        if(rightAngle < 190 && rightAngle > 170){
         mode = 40;
          Serial2.print("strait");
        }
         }
         if(mode = 60){
                  if(rightAngle > 350){
          Serial2.print("right");
        }
        if(rightAngle < 10){
          Serial2.print("left");
        }
        if(rightAngle < 10 && rightAngle > 350){
         mode = 80;
          Serial2.print("strait");
        }
         }
        if(mode == 40){
          if(rightCount == 1){
            if(rightWidth > 100){
mode = 5;
}
rightCount = 0;
  }
 }
 if(mode == 80){
            if(rightCount == 1){
            if(rightWidth < 130){
mode = 5;
}
rightCount = 0;
  }
 }
 if(mode == 5 || mode == 6){
 if(rightAngle > 100){
  Serial2.print("left");
 }
 if(rightAngle < 80){
  Serial2.print("right");
 }
 if(rightAngle > 80 && rightAngle < 100){
  Serial.print("strait");
  mode = 6;
 }
  if(mode = 6){
  Serial.print("trigger");
  if(Q == "can"){
    mode = 7;
    can = can+1;
  }
 }
 }
if(mode == 7){
  if(rightAngle < 80){
    Serial.print("right");
  }
  if(rightAngle >= 80){
    Serial.print("stap");
    mode = 0;
  }
}
    }
if(can == 6){
  pixels.clear();
    pixels.setPixelColor(place+0, pixels.Color(25, 0, 0));
  pixels.setPixelColor(place+1, pixels.Color(22, 3, 0));
  pixels.setPixelColor(place+2, pixels.Color(19, 6, 0));
  pixels.setPixelColor(place+3, pixels.Color(16, 9, 0));
  pixels.setPixelColor(place+4, pixels.Color(13, 12, 0));
  pixels.setPixelColor(place+5, pixels.Color(9, 16, 0));
  pixels.setPixelColor(place+6, pixels.Color(6, 18, 0));
  pixels.setPixelColor(place+7, pixels.Color(3, 21, 0));
  pixels.setPixelColor(place+8, pixels.Color(0, 25, 0));
  pixels.setPixelColor(place+9, pixels.Color(0, 22, 3));
  pixels.setPixelColor(place+10, pixels.Color(0, 19, 6));
  pixels.setPixelColor(place+11, pixels.Color(0, 16, 9));
  pixels.setPixelColor(place+12, pixels.Color(0, 13, 12));
  pixels.setPixelColor(place+13, pixels.Color(0, 9, 16));
  pixels.setPixelColor(place+14, pixels.Color(0, 6, 19));
  pixels.setPixelColor(place+15, pixels.Color(0, 3, 22));
  pixels.setPixelColor(place+16, pixels.Color(0, 0, 25));
  pixels.setPixelColor(place+17, pixels.Color(3, 0, 22));
  pixels.setPixelColor(place+18, pixels.Color(6, 0, 19));
  pixels.setPixelColor(place+19, pixels.Color(9, 0, 16));
  pixels.setPixelColor(place+20, pixels.Color(12, 0, 13));
  pixels.setPixelColor(place+21, pixels.Color(16, 0, 9));
  pixels.setPixelColor(place+22, pixels.Color(19, 0, 6));
  pixels.setPixelColor(place+23, pixels.Color(22, 0, 3));
  place = place+rotation;
  delay(25);
    pixels.show();
    if(place > 23 || place < -23){
      rotation = rotation*-1;
    }
}
}
