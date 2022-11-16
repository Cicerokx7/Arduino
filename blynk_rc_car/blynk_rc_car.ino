#define BLYNK_PRINT Serial

#define BLYNK_USE_DIRECT_CONNECT

#include <BlynkSimpleSerialBLE.h>
#include <SPI.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// SHARED SPI SETTINGS (see adafruit webpages for details)
#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              4    // Optional but recommended, set to -1 if unused
#define BLUEFRUIT_VERBOSE_MODE         true

// Create ble instance, see pinouts above
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);

//pin name
const int  forwardL = 11;
const int  rearL = 10;
const int  forwardR = 5;
const int  rearR = 6;

long Speed;
long SpeedL, SpeedR;

BLYNK_WRITE(V0) {
  long x = param[0].asInt();
  long y = param[1].asInt();

  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);

  Speed = sqrt(x*x+y*y);
  if(Speed > 255){
    Speed = 255;
  }
  Serial.print("  Speed: ");
  Serial.println(Speed);

  if(y >= 0){
    if(x >= 0){
      SpeedL = 0;
      SpeedR = abs(x);
    }else{
      SpeedL = abs(x);
      SpeedR = 0;
    }
    analogWrite(forwardL, Speed - SpeedL);
    analogWrite(rearL, 0);
    analogWrite(forwardR, Speed - SpeedR);
    analogWrite(rearR, 0);
  }else{
    if(x >= 0){
      SpeedL = 0;
      SpeedR = abs(x);
    }else{
      SpeedL = abs(x);
      SpeedR = 0;
    }
    analogWrite(forwardL, 0);
    analogWrite(rearL, Speed - SpeedL);
    analogWrite(forwardR, 0);
    analogWrite(rearR, Speed - SpeedR);
  }
}

void setup() {
  Serial.begin(9600);

  Blynk.begin(auth, ble);
  ble.begin(BLUEFRUIT_VERBOSE_MODE);
  ble.factoryReset(); // Optional
  ble.setMode(BLUEFRUIT_MODE_DATA);
}

void loop() {
  Blynk.run();
}
