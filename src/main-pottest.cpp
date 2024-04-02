#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "slider.h"
#include "pot.h"

// put function declarations here:
Mux *mux1ptr = new Mux(13,27,14,12);

Pot p1(2,mux1ptr);
Pot p2(4,mux1ptr);
Pot p3(7,mux1ptr);
Pot p4(1,mux1ptr);
Pot p5(6,mux1ptr);
Pot p6(5,mux1ptr);

void setup() {
    Serial.begin(9600);
    Serial.println("Hello world");
}

void loop() {
  delay(100);
  Serial.print("Pot values: ");
  Serial.print(p1.readPot());
  Serial.print(" ");
  Serial.print(p2.readPot());
  Serial.print(" ");
  Serial.print(p3.readPot());
  Serial.print(" ");
  Serial.print(p4.readPot());
  Serial.print(" ");
  Serial.print(p5.readPot());
  Serial.print(" ");
  Serial.println(p6.readPot());
}

