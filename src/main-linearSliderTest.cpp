#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "sliderclasses/linearslider.h"
#include <Wire.h>
#include "Updater.h"
#include "Adafruit_ILI9341.h"
#include "AdafruitIO_WiFi.h"

// The following sets up the driver for the Motors
Adafruit_PWMServoDriver driver(0x60);

IC_MC14051 *mux1ptr = new IC_MC14051(9,21,20,19);

MC14051_Potentiometer p1(1,mux1ptr);

Capacitivetouch t1(1);

Motor m1(&driver,1);

// set up the slider
LinearSlider slider1(&m1,&p1,&t1);

Updater u1; 






void setup() {
  u1.addNode(&t1);
  u1.addNode(&p1);
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
  Serial.println("calibrating Slider");
  slider1.calibrate();
  Serial.println("Calibration complete");
}

int n = 0;
#include <cstdlib> // Include the library for generating random numbers

void loop() {
  u1.update_Components();
  slider1.update_Device();
  n++;
  if (n > 800) {
    int goal = rand() % 101; // Generate a random number between 0 and 100
    slider1.set_goal(goal);
    Serial.print("Set goal to: ");
    Serial.println(goal);
    n = 0;
  }
}