#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include "IC_CD74HC165E.h"
#include "Updater.h"
#include "CD74HC165E_Button.h"
#include "MC14051_Potentiometer.h"
#include "IC_MC14051.h"
#include "Capacitivetouch.h"
#include "Motor.h"
#include "sliderclasses/steppedslider.h"
#include "Menu.h"
#include "Manager.h"
#include "AdafruitIO_WiFi.h"
#include "Adafruit_ILI9341.h"
// include the menus you would like to
#include "examplemenu1.h"
#include "examplemenu2.h"
#include "examplemenu3.h"

// hardware definitions
// Start with adding the managerPointer for later use
Manager* manager = nullptr;



// define all ICs present (This is Motor drivers, CD74HC165E, and MC14051)
IC_CD74HC165E ic(37,36,35,1);
Adafruit_PWMServoDriver driver(0x60);
IC_MC14051 *mux1ptr = new IC_MC14051(9,21,20,19);




// define all components of all sliders present in the system
Potentiometer* p1 = new MC14051_Potentiometer(1,mux1ptr);
Capacitivetouch* t1 = new Capacitivetouch(1);
Motor* m1 = new Motor(&driver,1);
Potentiometer* p2 = new MC14051_Potentiometer(2,mux1ptr);
Capacitivetouch* t2 = new Capacitivetouch(2);
Motor* m2 = new Motor(&driver,2,1);



// create the definitions for all buttons given to the menus
#define givenButtonCount 3
Button* givenButtons[givenButtonCount] = {
  new CD74HC165E_Button(0,&ic),
  new CD74HC165E_Button(6,&ic),
  new CD74HC165E_Button(7,&ic)};


// create the definitions for all buttons given to the manager
#define menuButtonCount 1
Button* menuButtons[menuButtonCount] = {
  new CD74HC165E_Button(5,&ic)
};



// create the list of sliders for the manager
#define givenSliderCount 1
Slider* sliders[givenSliderCount] = {
  new SteppedSlider(m2,p2,t2,3)
};


// create a list of all your display (should only be 1)
Display d1(0,1,2,3,4,5);
Updater u1;

Adafruit_NeoPixel stripof12(12, 4, NEO_GRB + NEO_KHZ800);
Strip strip1(&stripof12,0,2);
Strip strip2(&stripof12,2,10);

// allocate your MenuSelectionSlider (must have exactly 1)
SteppedSlider* s1 = new SteppedSlider(m1,p1,t1,0);

// create the array with the menus you would like to use
// create a list of menus
#define menuCount 2
Menu* menus[menuCount] = {
  new Example1(),
  new Example2(),
};



void setup() {
  Wire.setPins(18,8);
  driver.begin();
  stripof12.begin();
  for (int i = 1; i < 16; i++) {
    driver.setPin(1,0);
  }

  u1.addNode(&ic);
  for (int i = 0; i < givenButtonCount; i++) {
    u1.addNode(givenButtons[i]);
  }
  for (int i = 0; i < menuButtonCount; i++) {
    u1.addNode(menuButtons[i]);
  }
  u1.addNode(t1);
  u1.addNode(p1);
  u1.addNode(t2);
  u1.addNode(p2);
  u1.setStrip(&stripof12);
  manager = new Manager(
    s1,
    menuButtons,
    menuButtonCount,
    &u1,
    menus,
    menuCount,
    sliders,
    givenSliderCount,
    givenButtons,
    givenButtonCount,
    &strip1,
    &strip2,
    &d1
  );

  // create updater and add updater to list

  Serial.begin(115200);
  Serial.println("Hello world");
  s1->calibrate();
}


void loop() {
  manager->update_device();
}



