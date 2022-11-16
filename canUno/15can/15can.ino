//UNTESTED
//LIDAR VERSION
//UNTESTED
#include <RPLidar.h>
#include <Pixy2.h>
#include <Servo.h>

RPLidar lidar;

#define RPLIDAR_MOTOR 3 

float width = 0;
float rightWidth = 0;
float leftWidth = 0;
float now = 0;
int rightAngle = 90;
int leftAngle = 270;
float frontCheck = 0;
float backCheck = 0;
int error = 2;
int rightCount = 0;
int leftCount = 0;
int frontCount = 0;
int backCount = 0;

int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;
int gripperClose = 120;
int gripperOpen = 20;
Pixy2 pixy;
Servo gripper;
Servo flag;

int count = 0;
int can = 0;
int canW = 0;
int spedeo = 30;
int spedet = 18;
int thyme = 0;
int goalo = 158;

void setup() {
    pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  lidar.begin(Serial1);
  Serial.begin(9600);
  Serial.print("help");
  pinMode(RPLIDAR_MOTOR, OUTPUT);

     pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(13, OUTPUT); 
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
 pinMode(A9, INPUT);
  Serial.begin(9600);
  pixy.init();
  gripper.attach(5);
  flag.attach(9);
  gripper.write(gripperOpen);
  flag.write(0);
}

void loop() {
  if(can < 6){
  if (IS_OK(lidar.waitPoint())) {
    float distance = lidar.getCurrentPoint().distance; //distance value in mm unit
    float angle = lidar.getCurrentPoint().angle; //anglue value in degree
    bool startBit = lidar.getCurrentPoint().startBit; //whether this point is belong to a new scan
    byte quality  = lidar.getCurrentPoint().quality; //quality of the current measurement

    if(angle > rightAngle-error && angle < rightAngle+error){
      rightWidth = distance;
      rightCount = 1;
    }
    if(angle > leftAngle-error && angle < leftAngle+error){
      leftWidth = distance;
      leftCount = 1;
    }
    if(angle > rightAngle+4-error && angle < rightAngle+4+error){
      frontCheck = distance;
      frontCount = 1;
    }
    if(angle > rightAngle-4-error && angle < rightAngle-4+error){
      backCheck = distance;
      backCount = 1;
    }
    if(backCount == 1 && frontCount == 1){
      backCount = 0;
      frontCount = 0;
      if(frontCheck < backCheck+20 && frontCheck > backCheck-20){
      //  Serial.println(rightAngle );
        /*    if(rightAngle > 90){
     // Serial.println("turn right");
    }
    if(rightAngle < 90){
    //  Serial.println("turn left");
    }*/
    if(count == 2){
      if(rightAngle > 180){
     // Serial.println("turn right");
     digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet-50);
    analogWrite(pwmL, spedet);
    }
    if(rightAngle < 180){
    //  Serial.println("turn left");
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet-50);
    }
    }
    if(count == 3){
            if(rightAngle > 90){
     // Serial.println("turn right");
     digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    if(rightAngle < 90){
    //  Serial.println("turn left");
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    }
    if(count == 5){
      if(rightAngle > 0){
     // Serial.println("turn right");
     digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    if(rightAngle < 0){
    //  Serial.println("turn left");
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    if(rightAngle > -10 && rightAngle < 10){
      can = 1;
      count = 1;
    }
    }
      }
      if(frontCheck > backCheck+20 || frontCheck < backCheck-20){
        if(frontCheck > backCheck){
          rightAngle = rightAngle-1;
          leftAngle = leftAngle-1;
        }
        if(frontCheck < backCheck){
          rightAngle = rightAngle+1;
          leftAngle = leftAngle+1;
        }
      }
    }
    if(rightCount == 1 && leftCount == 1){
    now = rightWidth+leftWidth;
    rightCount = 0;
    leftCount = 0;
    Serial.println(now);
     if(count == 0){
      width = now;
      count = 1;
    }
    if(count = 2){
      if(rightWidth < width/2+50 && rightWidth > width/2-50){
       count = 3;
      }
    }
    }
    /*
    if(width+10 < now && width-10 > now){
      delay(100);
    }
    */
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

  if(count == 1){
        int i;
    pixy.ccc.getBlocks();
    canW = pixy.ccc.blocks[i].m_width;
    if(pixy.ccc.blocks[i].m_signature != 1 && thyme == 0){
      thyme = thyme+1;
    }
           if(thyme == 50){
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    }
    if(pixy.ccc.blocks[i].m_signature == 1 && thyme == 50){
      delay(500);
    }
    if(pixy.ccc.blocks[i].m_signature == 1){
      thyme = 0;
  }
  if(canW < 250){
    if(pixy.ccc.blocks[i].m_x > goalo){
               digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, (canW/7)+18);
    analogWrite(pwmL, (canW/7)+18);//%60
    }
    if(pixy.ccc.blocks[i].m_x == goalo){
       digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, (canW/4)+18);
    analogWrite(pwmL, (canW/4)+18);
    }
    if(pixy.ccc.blocks[i].m_x < goalo){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, (canW/4)+18);
    analogWrite(pwmL, (canW/4)+18);
    }
    }
    if(canW >= 250){
      digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
      gripper.write(gripperClose);
      //neck.write(45);
      count = 2;
    }
  }
  if(count == 3){
    flag.write(90);
    if(A0 == HIGH){
      count = 4;
    }
  }
  if(count == 4){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
    flag.write(0);
    gripper.write(gripperOpen);
    count = 5;
  }
  if(count == 5){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    delay(100);
  }
}
if(can == 6){
  digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    delay(100);
    digitalWrite(rightFMotor, HIGH);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, spedet);
    analogWrite(pwmL, spedet);
    flag.write(90);
    delay(100);
    flag.write(0);
    delay(100);
    flag.write(90);
    delay(100);
    flag.write(0);
    delay(100);
    flag.write(90);
    delay(100);
    flag.write(0);
    delay(100);
    flag.write(90);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
}
}
