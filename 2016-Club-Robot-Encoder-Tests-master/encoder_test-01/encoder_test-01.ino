int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int right = 19;
int left = 18;
int rightI = 0;
int leftI = 0;

void setup(){
    for (int i=0; i<2; i++){
      pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
    }
    pinMode(19, INPUT);
    pinMode(18, INPUT);
}
void loop(){
  rightI = digitalRead(right);
  leftI = digitalRead(left);
  if(rightI == HIGH){
    digitalWrite(inBpin[0], HIGH);
    analogWrite(pwmpin[0], 100);
  }
if(rightI == LOW){
  digitalWrite(inBpin[0], LOW);
  analogWrite(pwmpin[0], 0);
  }
  if(leftI == HIGH){
   digitalWrite(inBpin[1], HIGH);
    analogWrite(pwmpin[1], 100);
  }
  if(leftI == LOW){
    digitalWrite(inBpin[1], LOW);
    analogWrite(pwmpin[1], 0);
  }
}  

