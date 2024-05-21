#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "IC_CD74HC165E.h"
#include "Updater.h"
#include "CD74HC165E_Button.h"
#include "Adafruit_ILI9341.h"


IC_CD74HC165E ic(37,36,35,1);
Updater u1; 
CD74HC165E_Button* b1 = new CD74HC165E_Button(5,&ic);
CD74HC165E_Button* b2 = new CD74HC165E_Button(0,&ic);
CD74HC165E_Button* b3 = new CD74HC165E_Button(6,&ic);
CD74HC165E_Button* b4 = new CD74HC165E_Button(7,&ic);

Button* givenButtons[4] = {b1,b2,b3,b4};






void setup() {
  u1.addNode(&ic);
  u1.addNode(b1);
  u1.addNode(b2);
  u1.addNode(b3);
  u1.addNode(b4);
  // The following sets up debug system and prints a message to check if initiated
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello world");
}


void loop() {
  u1.update_Components();
  Serial.print(b1->get_state());
  Serial.print(b2->get_state());
  Serial.print(b3->get_state());
  Serial.print(b4->get_state());
  Serial.print(" ");
  for (int i = 0; i < 4; i++) {
    Serial.print("  Button ");
    Serial.print(i);
    Serial.print(" state: ");
    givenButtons[i]->update_nodeValue();
    Serial.print(givenButtons[i]->get_state());
  }
  Serial.println();
}