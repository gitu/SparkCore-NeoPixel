/*-------------------------------------------------------------------------
  Spark Core library to control WS2812 based RGB
  LED devices such as Adafruit NeoPixel strips.
  Currently handles 800 KHz bitstream on Spark Core, 
  with LEDs wired for GRB color order.

  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
  Modified to work with Spark Core by Technobly.
  Contributions by PJRC and other members of the open source community.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!
  --------------------------------------------------------------------*/
/* ======================= Spark_StrandTest.cpp ======================= */

#include "Spark_NeoPixel.h"

#define PIN D0

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Pixels are wired for GRB bitstream
// 800 KHz bitstream (e.g. High Density LED strip) - WS2812 (6-pin part)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, PIN);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Some example procedures showing how to display to the pixels:
  // Do not run more than one of these at a time, or the b/g tasks will be blocked.
  //-------------------------------------------------------------------------------
  //strip.setPixelColor(0, strip.Color(255, 0, 255));
  //strip.show();
  
  //colorWipe(strip.Color(255, 0, 0), 50); // Red
  
  //colorWipe(strip.Color(0, 255, 0), 50); // Green
  
  //colorWipe(strip.Color(0, 0, 255), 50); // Blue
  
  rainbow(20);
  
  //rainbowCycle(20);
  
  //colorAll(strip.Color(0, 255, 255), 50); // Magenta
}

// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;
  
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}

// Fill the dots one after the other with a color, wait (ms) after each one
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout, then wait (ms)
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) { // 1 cycle of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}