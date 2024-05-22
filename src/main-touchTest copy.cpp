#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "capacitivetouch.h"

// put function declarations here:

Capacitivetouch t1(1);

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world");
}

void loop() {
  delay(100);
  Serial.print("Touch value: ");
  t1.update_nodeValue();
  Serial.println(t1.get_touchBool());
}

