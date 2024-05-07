#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "capacitivetouch.h"

// put function declarations here:



void setup() {
    Serial.begin(9600);
    Serial.println("Hello world");
}

void loop() {
  delay(100);
  Serial.print("Touch value: ");
  Serial.println(t1.readTouchBool());
}

