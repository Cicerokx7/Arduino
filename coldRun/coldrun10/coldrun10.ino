 #include <Pixy2.h>
#include <Servo.h>
#include <Encoder.h>
#include <HCSR04.h>

Servo servo;
Encoder myEnc(3, 2);
UltraSonicDistanceSensor distanceSensor(8, A0);
Pixy2 pixy;

int motor = 6;  
int width = 0;
int angle = 90;
int power = 255;
long oldSpeed = 0;
long newSpeed = 0; 
long spede = 0;
int thyme = 0;

int rightBumper = 10;
int stopButton = 9;
int leftBumper = 12;
int right = 1;
int left = 1;
int stap = 0;
int distance = -1;
int test = 0;
int alarm = 0;
int cash = 0;
int jkl = 0;
int bumperGo = 0;
int stopGo = 0;
int off = 0;

void setup() {
  pinMode(motor, OUTPUT);
  pinMode(rightBumper, INPUT);
  pinMode(leftBumper, INPUT);
  pinMode(stopButton, INPUT);
  servo.attach(5);
  Serial.begin(9600);
  servo.write(angle);
  pixy.init();
}
void loop() {
  if(test < 8){
    stap = digitalRead(stopButton);
    right = digitalRead(rightBumper);
    left = digitalRead(leftBumper);
  if(right == HIGH && test == 0){
    Serial.println("push right bumper");
    test = 1;
  }
    if(right == LOW && test == 1){
      test = 2;
      angle = 70;
  }
  if(left == HIGH && test == 2){
    Serial.println("push left bumper");
    test = 3;
  }
    if(left == LOW && test == 3){
      test = 4;
      angle = 80;
    }
  if(stap == LOW && test == 4){
    Serial.println("push stop");
    test = 5;
  }
    if(stap == HIGH && test == 5){
      test = 6;
      angle = 70;
      delay(100);
  }
  if(test > 5){
    distance = distanceSensor.measureDistanceCm();
  if(distance < 5 && test == 6){
    Serial.println("cover eyes");
    test = 7;
  }
    if(distance > 5 && test == 7){
      test = 8;
      angle = 70;
    }
  }
}
  if(test == 8){
    
    stap = digitalRead(stopButton);
      if(stap == LOW){
     //   Serial.println("stop pass");
    right = digitalRead(rightBumper);
    left = digitalRead(leftBumper);
    if(right == HIGH || left == HIGH){
    //  Serial.println("bumper pass");
       if(power >= 0){
        if(off < 100){
  analogWrite(motor, power);
//  Serial.print("go");
        }
  }
  }
      }
          
          
          if(distance > 5 && distance < 50){
            analogWrite(motor, 0);
            delay(100);
            Serial.println("dist");
     // power = 5;
          }
          
    
        if(right == LOW || left == LOW){
      Serial.println("bumper");
      analogWrite(motor, 0);
      delay(7000);
   //   power = 5;
    }
      if(stap == HIGH){
        Serial.println("stop");
  analogWrite(motor, 0);
  delay(30000);
 // power = 4;
      }
thyme = thyme + 1;
if(thyme == 20){
  distance = distanceSensor.measureDistanceCm();
  thyme = 0;
  Serial.println(distance);
}
      int i;
  pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks){
      off = 0;
   width = pixy.ccc.blocks[i].m_height;
   angle = map(width, 0, 158, 105, 60);
  // delay(100);
    //}
     newSpeed = myEnc.read();
         spede = newSpeed-oldSpeed;
    oldSpeed = newSpeed;
  // power = map(spede, 0, 800, 255, 0)5
      if(spede < 125 && power < 245){
      power = power+10;
    }
  if(spede < 175 && power < 255){
    power = power+1;
  }
  if(spede > 175 && power > 0){
    power = power-1;
  }
  if(spede > 225 && power > 10){
    power = power-10;
  }
  Serial.println(spede);
  Serial.println(power);
    }
    /*
    if(pixy.ccc.numBlocks == false){
     off += 1;
    }
    if(off > 100){
      angle = 80;
      analogWrite(motor, 0);
    }
    */
  }
  //analogWrite(motor, power);
    if(angle <= 100 && angle >= 60){
  servo.write(angle);
  }
}
