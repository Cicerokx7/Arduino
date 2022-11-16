//#include <Servo.h>
#include <RPLidar.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define DELAYVAL 500

RPLidar lidar;

#define RPLIDAR_MOTOR 3 

//Servo gripper;
//Servo flag;

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
int mode = 100;
int lidarcount = 0;
int right = 0;
int left = 0;


//servos
int gripperClose = 140;
int gripperOpen = 60;
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
  //  gripper.attach(9);
    //flag.attach(12);
//    gripper.write(gripperOpen);
  //  flag.write(low);
    delay(1);
    Serial.print("starting");
}
float minDistance = 100000;
float angleAtMinDist = 0;

void loop() {
  analogWrite(RPLIDAR_MOTOR, 255);
    if(can < 6){
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
   // if(angle > leftAngle-error && angle < leftAngle+error){
   //   leftWidth = distance;
   //   leftCount = 1;
   // }
    if(angle > rightAngle-4-error && angle < rightAngle-4+error){
      frontCheck = distance;
      frontCount = 1;
    }
    if(angle > rightAngle+4-error && angle < rightAngle+4+error){
      backCheck = distance;
      backCount = 1;
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


  
           if(rightAngle <= 5 && rightAngle >= 0){
            rightAngle = 350;
          }
          if(rightAngle >= 355 && rightAngle <= 360){
            rightAngle = 10;
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
        if(Q == "test"){
          mode = 3;
//          gripper.write(gripperClose);
        }
        }
         if(mode == 30 || mode == 40){
        if(rightAngle > 180){
         // Serial1.println("right");
          Serial3.println("right");
        }
        if(rightAngle < 180){
         // Serial1.println("left");
          Serial3.println("left");
        }
        if(rightAngle < 190 && rightAngle > 170){
         mode = 40;
           }
         }
         if(mode == 60 || mode == 80){
                  if(rightAngle > 180){
         // Serial1.println("left");
          Serial3.println("left");
        }
        if(rightAngle < 180){
         // Serial1.println("right");
          Serial3.println("right");
        }
        if(rightAngle < 10 || rightAngle > 350){
         mode = 80;
        }
         }
        if(mode == 40){
          if(rightCount == 1){
            //1067
            if(rightWidth > 1067){
              Serial3.println("stap");
              mode = 5;
            }
            rightCount = 0;
          }
        }
        if(mode == 80){
           if(rightCount == 1){
            if(rightWidth < 1067){
              Serial3.println("stap");
              blue = 25;
              red = 0;
              mode = 5;
            }
            rightCount = 0;
          }
        }
        if(mode == 5 || mode == 6){
           if(mode == 5){
              Serial3.println("stap");
    //          flag.write(high);
           }
           if(rightAngle > 90 && rightAngle < 270){
               // Serial1.println("right");
               Serial3.println("right");
           }
           if(rightAngle < 90 || rightAngle > 270){
              // Serial1.println("left");
              Serial3.println("left");
           }
           if(rightAngle > 80 && rightAngle < 100 && mode == 5){
              mode = 6;
             // pixels.setPixelColor(4, pixels.Color(25, 25, 0));
             // pixels.show();
           }
           if(mode == 6){
              // Serial1.println("trigger");
              Serial3.println("trigger");
           if(Q == "can"){
        //      gripper.write(gripperOpen);
      //        flag.write(low);
              mode = 7;
              can = can+1;
           }
         }
       }
       if(mode == 7){
          if(rightAngle > 0 && rightAngle < 270){
              // Serial1.println("right");
              Serial3.println("right");
          }
          if(rightAngle > 270 && rightAngle < 360){
              // Serial1.println("stap");
              Serial3.println("stap");
              mode = 0;
          }
        }
}
lidarcount = lidarcount+1;
}
