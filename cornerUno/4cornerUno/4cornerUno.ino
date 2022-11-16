int rightFMotor = 4;
int rightBMotor = 9;
int leftFMotor = 7;
int leftBMotor = 8;
int pwmR = 6;
int pwmL = 5;

int mode = 0;
int right = 0;
int left = 0;
int stap = 0;
int strait = 0;
int spedeor = 70;
int spedeol = 50;
int rspeder = 35;
int rspedel = 25;
int go = 0;

void setup() {
       
  // put your setup code here, to run once:
 pinMode(rightFMotor, OUTPUT);
 pinMode(rightBMotor, OUTPUT);
 pinMode(leftFMotor, OUTPUT);
 pinMode(leftBMotor, OUTPUT);
 pinMode(pwmR, OUTPUT);
 pinMode(pwmL, OUTPUT);
 pinMode(goalSwitchPin, INPUT);
Serial.begin(9600);
delay(5000);
}

void loop() {
String readString;
String Q;

//-------------------------------Check Serial Port---------------------------------------
 while (Serial.available()) {
      delay(1);
    if (Serial.available() > 0) {
      char c = Serial.read();//gets one byte from serial buffer
    if (isControl(c)) {
      //'Serial.println("it's a control character");
      break;
    }
      readString += c; //makes the string readString    
    }
 }   

 Q = readString;
 if(Q != "right" && mode == 0 && Q != "left"){
Serial.println("on");
 }
 if(mode == 0){
if(Q == "right" || Q == "left"){
mode = 1;
}
 }
if(Q == "right"){
  right = 1;
  left = 0;
  stap = 0;
  go = 0;
}
if(Q == "left"){
  left = 1;
  right = 0;
  stap = 0;
  trigger = 0;
}
if(Q == "stap"){
  stap = 1;
  go = 0;
}
if(Q == "strait"){
  right = 1;
  left = 1;
  stap = 0;
  go = 0;
}
if(Q == "go"){
  go = 1;
  stap = 0;
}

  if(go == 1){
   mode = 1; 
  }
  if(stap == 2){
    digitalWrite(leftFMotor, LOW);
    digitalWrite(rightFMotor, LOW);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, 0);
    analogWrite(pwmL, 0);
   // flag.write(high);
    delay(1000);
    mode = 2
  }
  if(mode == 1){
    if(right == 1){
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
  //  Serial.print("right");
    }
    else{
    digitalWrite(leftFMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
    if(left == 1){
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
  //  Serial.print("left");
    }
    else{
      digitalWrite(rightFMotor, LOW);
    analogWrite(pwmR, spedeor);
    analogWrite(pwmL, spedeol);
    }
  }
  if(mode == 2){
    if(right == 1){
    digitalWrite(rightFMotor, LOW);
    digitalWrite(leftFMotor, HIGH);
    digitalWrite(rightBMotor, HIGH);
    digitalWrite(leftBMotor, LOW);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
  //  Serial.print("right");
    }
    if(left == 1){
    digitalWrite(leftFMotor, LOW);
      digitalWrite(rightFMotor, HIGH);
    digitalWrite(rightBMotor, LOW);
    digitalWrite(leftBMotor, HIGH);
    analogWrite(pwmR, rspeder);
    analogWrite(pwmL, rspedel);
   // Serial.print("left");
    }
  }
}
