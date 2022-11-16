
#include <RPLidar.h>



RPLidar lidar;

#define RPLIDAR_MOTOR 3 

float start = 0;
float ind = 0;
float startD = 0;
float indD = 0;
float ang = 0;
float rad = 0;
float dis = 0;
float test = 0;
int front = 0;
void setup() {
  lidar.begin(Serial1);
  Serial.begin(9600);
  
  pinMode(RPLIDAR_MOTOR, OUTPUT);
}

void loop() {
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle    = lidar.getCurrentPoint().angle; //anglue value in degree
    bool  startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte  quality  = lidar.getCurrentPoint().quality; //quality of the current measurement
    if(angle > front && angle < front+10){
      if(distance < 50){
        Serial.print("found it");
      }
      else{
        if(front != 360){
        front = front+1;
        }
      else{
        front = 0;
      }
      }
    }
//    Serial.println(distance);

    /*
    //perform data processing here... 
    if(distance <= 1000 && start == 0 && distance != 0){
      start = angle;
      startD = distance;
    }
    if(distance >= 1000 && start != 0 && ind == 0 && distance != 0){
      ind = angle;
      indD = distance;
      //ang = sqrt(sq(start-ind));
     if(ind > start){
      if(ind-start < 180){
      ang = ind-start;
      }
     }
     
     if(ind < start){
         if(ind+360-start < 180){  
        ang = ind+360-start;
         }
     }
     
     ang = ang*100;
    ang = map(ang, 0, 36000, 0, 628);
    ang = ang/100;
    //  test = sqrt(2*sq(startD)-2*indD*startD*cos(ang));
    test = 2*sin(ang/2)*startD;
//if(start > 315 || start < 45){
  //Serial.println(test);
  if(test > 400 && test < 500){
  if(start == 0){
    Serial.println("strait");
  }
  if(start > 180){
    Serial.println("left");
  }
  if(start < 180){
    Serial.println("right");
  }
  }
    else{
  }
  /*
  if(test > 250 && test < 450){
    Serial.println("hello jack");
  }
  else{
    Serial.println("not Jack");
  }
   
//}
//if(test != 0)
//Serial.println(test);

      ind = 0;
      start = 0;
    //  Serial.println(startD);
//Serial.println(ind);
    }
    */
    
  } else {
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
