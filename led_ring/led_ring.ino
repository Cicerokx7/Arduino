// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 24 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int red = 250;
int green = 20;
int blue = 0;
int place = 0;
int rotation = 1;
int fade = 0;
float test = 1;

void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'

  // The first NeoPixel in a strand is #0, second is 1, all the way up
  // to the count of pixels minus one. // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    // Here we're using a moderately bright green color:
    /*
    pixels.setPixelColor(0, pixels.Color(25, 0, 0));
    pixels.setPixelColor(11, pixels.Color(0, 0, 0));
    pixels.show();
    delay(500);
    pixels.setPixelColor(11, pixels.Color(0, 0, 25));
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    delay(500);*/
    /*
  pixels.setPixelColor(0, pixels.Color(red, green, blue));
  pixels.setPixelColor(1, pixels.Color(red, green, blue));
  pixels.setPixelColor(2, pixels.Color(red, green, blue));
  pixels.setPixelColor(3, pixels.Color(red, green, blue));
  pixels.setPixelColor(4, pixels.Color(red, green, blue));
  pixels.setPixelColor(5, pixels.Color(red, green, blue));
  pixels.setPixelColor(6, pixels.Color(red, green, blue));
  pixels.setPixelColor(7, pixels.Color(red, green, blue));
  pixels.setPixelColor(8, pixels.Color(red, green, blue));
  pixels.setPixelColor(9, pixels.Color(red, green, blue));
  pixels.setPixelColor(10, pixels.Color(red, green, blue));
  pixels.setPixelColor(11, pixels.Color(red, green, blue));
  pixels.setPixelColor(12, pixels.Color(red, green, blue));
  pixels.setPixelColor(13, pixels.Color(red, green, blue));
  pixels.setPixelColor(14, pixels.Color(red, green, blue));
  pixels.setPixelColor(15, pixels.Color(red, green, blue));
  pixels.setPixelColor(16, pixels.Color(red, green, blue));
  pixels.setPixelColor(17, pixels.Color(red, green, blue));
  pixels.setPixelColor(18, pixels.Color(red, green, blue));
  pixels.setPixelColor(19, pixels.Color(red, green, blue));
  pixels.setPixelColor(20, pixels.Color(red, green, blue));
  pixels.setPixelColor(21, pixels.Color(red, green, blue));
  pixels.setPixelColor(22, pixels.Color(red, green, blue));
  pixels.setPixelColor(23, pixels.Color(red, gren, blue));*/
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
