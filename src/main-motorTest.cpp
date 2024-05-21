#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "slider.h"
#include <Wire.h>
#include "Adafruit_ILI9341.h"

// The following sets up the driver for the Motors
Adafruit_PWMServoDriver driver(0x60);

// The following sets up the motors
Motor m1(&driver,2,1);

void setup() {
  // The following sets up debug system and prints a message to check if initiated
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello world");

  // The following sets up the I2C communication ports
  Wire.setPins(18,8);

  // The following sets up the Motor Driver/s and sets all the pins to 0 to reset the device
  driver.begin();
  for (int i = 1; i < 16; i++) {
    driver.setPin(1,0);
  }
  
}

void loop() {
  Serial.println("Setting motor to fast");
  m1.setSpeed(70);
  delay(200);
  Serial.println("Setting motor to reverse");
  m1.setSpeed(-70);
  delay(200);
  Serial.println("Setting motor to Stop");
  m1.setSpeed(0);
  delay(2000);
}