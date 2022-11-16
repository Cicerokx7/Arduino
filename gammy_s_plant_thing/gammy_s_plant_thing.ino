int sensorPin = A0;
int sensorValue = 1;
int red = 3;
int yellow = 5;
int green = 6;
int redO = 0;
int yellowO = 0;
int greenO = 0;
int yellowT = 0;
int redT = 0;
int greenT = 0;
int yellowTh = 0;
int yellowF = 0;
int redTh = 0;
void setup() {
    Serial.begin(9600);
    pinMode(red, OUTPUT);
    pinMode(yellow, OUTPUT);
    pinMode(green, OUTPUT);
}

void loop() {
    sensorValue = analogRead(sensorPin);
    Serial.println(sensorValue);
    
    redO = map(sensorValue, 0, 87, 153, 0);
    yellowO = map(sensorValue, 87, 175, 0, 153);
    yellowT = map(sensorValue, 175, 262, 153, 0);
    greenO = map(sensorValue, 262, 350, 0, 153);
    yellowTh = map(sensorValue, 387, 425, 0, 153);
    yellowF = map(sensorValue, 425, 462, 153, 0);
    redTh = map(sensorValue, 462, 500, 0, 153);
    
    if(redO <= 153 && sensorValue <= 87)
    analogWrite(red, redO);
    
    if(yellowO <= 153 && sensorValue >= 87 &&sensorValue <= 175)
    analogWrite(yellow, yellowO);

    if(yellowT <= 153 && sensorValue >= 175 && sensorValue <= 262)
    analogWrite(yellow, yellowT);

    if(greenO <= 153 && sensorValue >= 262 && sensorValue <= 350)
    analogWrite(green, greenO);

    if(sensorValue >= 350)
    analogWrite(green, 153);
    
    if(yellowTh <= 153 && sensorValue >= 387 && sensorValue <= 425)
    analogWrite(yellow, yellowTh);

    if(yellowF <= 153 && sensorValue >= 425 && sensorValue <= 462)
    analogWrite(yellow, yellowF);

    if(redTh <= 153 && sensorValue >= 462 && sensorValue <= 500)
    analogWrite(red, redTh);



    if(sensorValue > 87 && sensorValue < 462)
    digitalWrite(red, LOW);

    if(sensorValue < 87 || sensorValue > 462){
      digitalWrite(yellow, LOW);
    }
    if(sensorValue > 262 && sensorValue < 387){
      digitalWrite(yellow, LOW);
    }
    if(sensorValue < 262){
      digitalWrite(green, LOW);
    }
  }
