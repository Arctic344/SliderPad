#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "MC14051_potentiometer.h"

// put function declarations here:
IC_MC14051 *mux1ptr = new IC_MC14051(9,21,20,19);

MC14051_Potentiometer p1(1,mux1ptr);

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world");
}

void loop() {
  delay(100);
  Serial.print("Pot value: ");
  p1.updatePotValue();
  Serial.println(p1.get_potValue());
}
