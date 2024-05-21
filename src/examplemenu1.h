#pragma once
#include "Menu.h"
#include "Converter.h"

class Example1 : public Menu {
    public:
    Example1() : Menu(1){

    }
    public:
    void on_ButtonPress(int buttonIndex, Button* button) override{
        manager->get_strip()->updateLed(buttonIndex, 255, 0, 0);
    }

    void on_ButtonRelease(int buttonIndex, Button* button) override{
        manager->get_strip()->updateLed(buttonIndex, 0, 0, 0);
    }

    void run_menu() override{
        if (manager->get_slidersLastTouchState(0) == 0){
            manager->get_strip()->updatePercentage(manager->get_sliderPosition(0), 0, 255, 255);
        } else {
        manager->get_strip()->updatePercentage(manager->get_sliderPosition(0), 0, 0, 255);
        }
    }


    void on_MenuSelected() override{
        manager->convert_toLinearSlider(0);
        manager->get_slider(0)->set_goal(20);
        manager->get_strip()->updateAll(0, 0, 0);
        manager->set_buttonReleaseTimeout(0,0);
        manager->set_buttonReleaseTimeout(1,0);
        manager->set_buttonReleaseTimeout(2,0);
    }
};