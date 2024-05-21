#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "capacitivetouch.h"
#include "Adafruit_ILI9341.h"

// put function declarations here:

Capacitivetouch t1(1);

void setup() {
    Serial.begin(115200);
    Serial.println("Hello world");
}

void loop() {
  delay(100);
  Serial.print("Touch value: ");
  t1.update_nodeValue();
  Serial.println(t1.get_touchBool());
}

