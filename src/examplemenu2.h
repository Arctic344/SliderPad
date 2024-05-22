#pragma once
#include "Menu.h"
#include "Converter.h"

class Example2 : public Menu {
    public:
    Example2() : Menu(1){

    }
    public:
    void on_ButtonPress(int buttonIndex, Button* button) override{
        manager->get_strip()->updateLed(buttonIndex, 0, 255, 0);
    }

    void on_ButtonRelease(int buttonIndex, Button* button) override{
        manager->get_strip()->updateLed(buttonIndex, 0, 0, 0);
    }
    void run_menu() override{
        if (manager->get_slidersLastTouchState(0) == 0){
            manager->get_strip()->updateLed(4, 0, 200-50*manager->get_sliderPosition(0), 50*manager->get_sliderPosition(0));
            manager->get_strip()->updateLed(5, 0, 200-50*manager->get_sliderPosition(0), 50*manager->get_sliderPosition(0));
            manager->get_strip()->updateLed(6, 0, 200-50*manager->get_sliderPosition(0), 50*manager->get_sliderPosition(0));
        } else {
            manager->get_strip()->updateLed(4, 255, 50*manager->get_sliderPosition(0), 0);
            manager->get_strip()->updateLed(5, 255, 50*manager->get_sliderPosition(0), 0);
            manager->get_strip()->updateLed(6, 255, 50*manager->get_sliderPosition(0), 0);
        }
    }

    void on_MenuSelected() override{
        manager->convert_toSteppedSlider(0,5);
        manager->get_slider(0)->set_goal(3);
        manager->get_strip()->updateAll(0, 0, 0);
        manager->set_buttonReleaseTimeout(0,0);
        manager->set_buttonReleaseTimeout(1,0);
        manager->set_buttonReleaseTimeout(2,0);
    }
};