#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "slider.h"

// put function declarations here:
int myFunction(int, int);

void setup() {

  Mux *mux1ptr = new Mux(1,2,3,4);

  Adafruit_PWMServoDriver *driver1ptr = new Adafruit_PWMServoDriver(0x60);
  Adafruit_PWMServoDriver *driver2ptr = new Adafruit_PWMServoDriver(0x61);

  Pot p1(4,mux1ptr);
  Pot p2(6,mux1ptr);
  Pot p3(7,mux1ptr);
  Pot p4(5,mux1ptr);
  Pot p5(2,mux1ptr);
  Pot p6(1,mux1ptr);

  Capacitivetouch t1(22);
  Capacitivetouch t2(23);
  Capacitivetouch t3(24);
  Capacitivetouch t4(25);
  Capacitivetouch t5(26);
  Capacitivetouch t6(27);

  Motor m1(driver1ptr,0);
  Motor m2(driver1ptr,1);
  Motor m3(driver1ptr,2);
  Motor m4(driver2ptr,0);
  Motor m5(driver2ptr,1);
  Motor m6(driver2ptr,2);

  Slider s1(p1,m1,t1);
  Slider s2(p2,m2,t2);
  Slider s3(p3,m3,t3);
  Slider s4(p4,m4,t4);
  Slider s5(p5,m5,t5);
  Slider s6(p6,m6,t6); // Sliders cool



}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}