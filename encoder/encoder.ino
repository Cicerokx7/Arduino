#define BRAKEVCC 0
#define CW   1
#define CCW  2
#define BRAKEGND 3
#define CS_THRESHOLD 100

int inApin[2] = {7, 4};  // INA: Clockwise input
int inBpin[2] = {8, 9}; // INB: Counter-clockwise input
int pwmpin[2] = {5, 6}; // PWM input
int blocks = 0;
int right = 18;
int left = 19;
int rightI = 0;
int leftI = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Basic Encoder Test:");
  // Initialize digital pins as outputs
  for (int i=0; i<2; i++)
  {
    pinMode(right, INPUT);
    pinMode(left, INPUT);
    pinMode(inApin[i], OUTPUT);
    pinMode(inBpin[i], OUTPUT);
    pinMode(pwmpin[i], OUTPUT);
  }
      digitalWrite(inApin[0], LOW);
    digitalWrite(inApin[1], LOW);
    digitalWrite(inBpin[0], LOW);
    digitalWrite(inBpin[1], LOW);
    analogWrite(pwmpin[0], 0);
    analogWrite(pwmpin[1], 0);
}
void loop(){
  rightI = digitalRead(right);
  leftI = digitalRead(left);  

  if(leftI == HIGH){
    Serial.print("left;  ");
    digitalWrite(inApin[0], HIGH);
    analogWrite(pwmpin[0], 255);
  }
  if(leftI == LOW){
    digitalWrite(inApin[0], LOW);
    analogWrite(pwmpin[0], 0);
  }
  if(rightI == HIGH){
    Serial.print("right;  ");
    digitalWrite(inApin[1], HIGH);
    analogWrite(pwmpin[1], 255);
  }
  if(rightI == LOW){
    digitalWrite(inApin[1], LOW);
    digitalWrite(pwmpin[1], 0);
  }
  }

