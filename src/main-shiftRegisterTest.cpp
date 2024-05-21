#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "IC_CD74HC165E.h"
#include "Updater.h"
#include "Adafruit_ILI9341.h"
#include "AdafruitIO_WiFi.h"


IC_CD74HC165E ic(37,36,35,1);
Updater u1; 






void setup() {
  u1.addNode(&ic);
  // The following sets up debug system and prints a message to check if initiated
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello world");
}


void loop() {
  u1.update_Components();
  Serial.print("Values:");
  for (int i = 0; i < 8; i++) {
    Serial.print(ic.get_storedBool(i));
  }
  Serial.println("");
  
}