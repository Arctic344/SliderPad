#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "IC_CD74HC165E.h"
#include "Updater.h"
#include "CD74HC165E_Button.h"
#include "SPI.h"
#include "Adafruit_ILI9341.h"
#include "AdafruitIO_WiFi.h"


IC_CD74HC165E ic(37,36,35,1);
Updater u1; 
CD74HC165E_Button b1(5,&ic);
CD74HC165E_Button b2(0,&ic);
CD74HC165E_Button b3(6,&ic);
CD74HC165E_Button b4(7,&ic);

#define TFT_MOSI 41  // Replace 11 with your MOSI pin
#define TFT_MISO 45  // Replace 12 with your MISO pin
#define TFT_SCLK 42  // Replace 13 with your SCK pin
#define TFT_CS   38  // Replace 10 with your CS pin
#define TFT_DC   40  // Replace 9 with your DC pin
#define TFT_RST  39  // Replace 8 with your RESET pin
#define SPI_FREQUENCY  27000000

TFT_eSPI tft = TFT_eSPI();  



void setup() {
  u1.addNode(&ic);
  u1.addNode(&b1);
  u1.addNode(&b2);
  u1.addNode(&b3);
  u1.addNode(&b4);
  tft.init();
  // The following sets up debug system and prints a message to check if initiated
  Serial.begin(115200);
  delay(500);
  Serial.println("Hello world");
}


void loop() {
  u1.update_Components();
  if (b1.get_state() == 1){
    tft.fillScreen(TFT_RED);
  } else {
    tft.fillScreen(TFT_BLACK);
  }
  Serial.print("Button state1: ");
  Serial.print(b1.get_state());
  Serial.print(" Button state2: ");
  Serial.print(b2.get_state());
  Serial.print(" Button state3: ");
  Serial.print(b3.get_state());
  Serial.print(" Button state4: ");
  Serial.println(b4.get_state());
}