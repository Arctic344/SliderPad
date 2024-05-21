#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "sliderclasses/litlinearslider.h"
#include <Wire.h>
#include "Updater.h"
#include "Strip.h"
#include "Adafruit_NeoPixel.h"

// The following sets up the driver for the Motors
Adafruit_PWMServoDriver driver(0x60);

IC_MC14051 *mux1ptr = new IC_MC14051(9,21,20,19);

MC14051_Potentiometer p1(1,mux1ptr);

Capacitivetouch t1(1);

Motor m1(&driver,1);

Adafruit_NeoPixel stripof12(12, 4, NEO_GRB + NEO_KHZ800);
Strip strip1(&stripof12,2,8);
// set up the slider
LitLinearSlider slider1(&m1,&p1,&t1,&strip1);

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
  stripof12.begin();
}

void loop() {
  u1.update_Components();
  slider1.update_Device();
  stripof12.show();
}