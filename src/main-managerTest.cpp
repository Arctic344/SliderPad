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


Manager* manager = nullptr;
  // define all the ICs
IC_CD74HC165E ic(37,36,35,1);
Adafruit_PWMServoDriver driver(0x60);
IC_MC14051 *mux1ptr = new IC_MC14051(9,21,20,19);

// define all components of a slider
Potentiometer* p1 = new MC14051_Potentiometer(1,mux1ptr);
Capacitivetouch* t1 = new Capacitivetouch(1);
Motor* m1 = new Motor(&driver,1);
// define slider
// define the 4 buttons

// create a list and add buttons b1 to b3
Button* givenButtons[3] = {
  new CD74HC165E_Button(0,&ic),
  new CD74HC165E_Button(6,&ic),
  new CD74HC165E_Button(7,&ic)};
// create another list with button b1 only
Button* menuButtons[1] = {
  new CD74HC165E_Button(5,&ic)
};
// create an empty list of sliders
Slider** sliders = nullptr;

SteppedSlider* s1 = new SteppedSlider(m1,p1,t1,0);

// create two menus
Menu exampleMenu1(69); //arbitrary ID
Menu exampleMenu2(420);
// create a list of menus
Menu* menus[2] = {&exampleMenu1,&exampleMenu2};

Display d1(0,1,2,3,4,5);
Updater u1;

void setup() {
  Wire.setPins(18,8);
  driver.begin();
  for (int i = 1; i < 16; i++) {
    driver.setPin(1,0);
  }

  u1.addNode(&ic);
  u1.addNode(givenButtons[0]);
  u1.addNode(givenButtons[1]);
  u1.addNode(givenButtons[2]);
  u1.addNode(menuButtons[0]);
  u1.addNode(t1);
  u1.addNode(p1);
  manager = new Manager(
    s1,
    menuButtons,
    1,
    &u1,
    menus,
    2,
    sliders,
    givenButtons,
    0,
    3,
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



