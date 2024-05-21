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

void setup() {
  // define all the ICs
  IC_CD74HC165E ic(37,36,35,1);
  Adafruit_PWMServoDriver driver(0x60);
  IC_MC14051 *mux1ptr = new IC_MC14051(9,21,20,19);

  // define all components of a slider
  MC14051_Potentiometer p1(1,mux1ptr);
  Capacitivetouch t1(1);
  Motor m1(&driver,1);
  // define slider
  // define the 4 buttons
  CD74HC165E_Button b1(5,&ic);
  CD74HC165E_Button b2(0,&ic);
  CD74HC165E_Button b3(6,&ic);
  CD74HC165E_Button b4(7,&ic);

  // create a list and add buttons b1 to b3
  Button* givenButtons[3] = {&b2,&b3,&b4};
  // create another list with button b1 only
  Button* menuButtons[1] = {&b1};
  // create an empty list of sliders
  Slider** sliders = nullptr;
  
  // create two menus
  Menu exampleMenu1(420); //arbitrary ID
  Menu exampleMenu2(69420);
  // create a list of menus
  Menu* menus[2] = {&exampleMenu1,&exampleMenu2};

  Display d1(0,1,2,3,4,5);
  Updater u1; 
  u1.addNode(&ic);
  u1.addNode(&b1);
  u1.addNode(&b2);
  u1.addNode(&b3);
  u1.addNode(&b4);
  u1.addNode(&t1);
  manager = new Manager(
    new SteppedSlider(&m1,&p1,&t1,0),
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
}
void loop() {
  manager->update_device();
}



