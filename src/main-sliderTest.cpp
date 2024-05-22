#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "slider.h"
#include <Wire.h>

// The following sets up the driver for the Motors
Adafruit_PWMServoDriver driver(0x60);

IC_MC14051 *mux1ptr = new IC_MC14051(9,21,20,19);

MC14051_Potentiometer p1(1,mux1ptr);

Capacitivetouch t1(1);

// The following sets up the motors
Motor m1(&driver,1);

Slider s1(p1,m1,t1);

void setup() {
  // The following sets up debug system and prints a message to check if initiated
  Serial.begin(9600);
  delay(500);
  Serial.println("Hello world");

  // The following sets up the I2C communication ports
  Wire.setPins(11,12);

  // The following sets up the Motor Driver/s and sets all the pins to 0 to reset the device
  driver.begin();
  for (int i = 1; i < 16; i++) {
    driver.setPin(1,0);
  }
  
}

void loop() {
  Serial.println("calibrating Slider");
  s1.calibrate();
  delay(5000);
  
}