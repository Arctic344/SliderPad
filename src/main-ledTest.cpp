#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
#include "Adafruit_ILI9341.h"
#include "AdafruitIO_WiFi.h"

// put function declarations here:

Adafruit_NeoPixel strip(12, 4, NEO_GRB + NEO_KHZ800);

void setup() {
    Serial.begin(115200);
    Serial.println("Hello world");
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  for(int i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0)); // Red color
  }
  strip.show(); // Update LED strip
  Serial.println("RED");
  delay(1000); // Wait for 1 second
  
  for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 255, 0)); // Red color
  }
  strip.show(); // Update LED strip
  Serial.println("GREEN");
  delay(1000); // Wait for 1 second

  for(int i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0, 0, 255)); // Red color
  }
  strip.show(); // Update LED strip
  Serial.println("BLUE");
  delay(1000); // Wait for 1 second
}

