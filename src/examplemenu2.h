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

    void on_MenuSelected() override{
        manager->convert_toSteppedSlider(0,5);
        manager->get_slider(0)->set_goal(3);
        manager->get_strip()->updateAll(0, 0, 0);
        manager->set_buttonReleaseTimeout(0,0);
        manager->set_buttonReleaseTimeout(1,0);
        manager->set_buttonReleaseTimeout(2,0);
    }
};