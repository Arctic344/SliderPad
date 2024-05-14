#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "IC_CD74HC165E.h"
#include "Updater.h"
#include "CD74HC165E_Button.h"


IC_CD74HC165E ic(37,36,35,1);
Updater u1; 
CD74HC165E_Button b1(5,&ic);
CD74HC165E_Button b2(0,&ic);
CD74HC165E_Button b3(6,&ic);
CD74HC165E_Button b4(7,&ic);






void setup() {
  u1.addNode(&ic);
  u1.addNode(&b1);
  u1.addNode(&b2);
  u1.addNode(&b3);
  u1.addNode(&b4);
  // The following sets up debug system and prints a message to check if initiated
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello world");
}


void loop() {
  u1.update_Components();
  Serial.print("Button state1: ");
  Serial.print(b1.get_state());
  Serial.print(" Button state2: ");
  Serial.print(b2.get_state());
  Serial.print(" Button state3: ");
  Serial.print(b3.get_state());
  Serial.print(" Button state4: ");
  Serial.println(b4.get_state());
  
}