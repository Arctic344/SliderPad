#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "slider.h"
#include "pot.h"

// put function declarations here:
Mux *mux1ptr = new Mux(9,21,20,19);

Pot p1(1,mux1ptr);

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world");
}

void loop() {
  delay(100);
  Serial.print("Pot value: ");
  Serial.println(p1.readPot());
}

