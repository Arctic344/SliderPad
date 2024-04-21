#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "slider.h"

Adafruit_PWMServoDriver driver(0x60);

Motor m1(&driver,2);
Motor m2(&driver,3);

void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("Hello world");
  driver.begin();
  for (int i = 1; i < 16; i++) {
    driver.setPin(1,0);
  }
  
}

void loop() {
  Serial.println("Setting motor to fast");
  m1.setSpeed(500);
  m2.setSpeed(500);
  delay(2000);
  Serial.println("Setting motor to reverse");
  m1.setSpeed(-500);
  m2.setSpeed(-500);
  delay(2000);
  Serial.println("Setting motor to Stop");
  m1.setSpeed(0);
  m2.setSpeed(0);
  delay(2000);
  Serial.println("Setting motor to Short brake");
  m1.ShortBrakeDoubleHigh();
  m2.ShortBrakeDoubleHigh();
  delay(2000);
}
