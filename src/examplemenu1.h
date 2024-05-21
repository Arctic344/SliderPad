#pragma once
#include "Menu.h"

class Example1 : public Menu {
    public:
    Example1() : Menu(1){

    }
    public:
    void on_ButtonPress(int buttonIndex, Button* button) override{
        manager->get_strip()->updateLed(buttonIndex, 255, 0, 0);
    }
    void on_MenuSelected() override{
        manager->get_strip()->updateAll(0, 0, 0);
        manager->set_buttonReleaseTimeout(0,0);
        manager->set_buttonReleaseTimeout(1,0);
        manager->set_buttonReleaseTimeout(2,0);
    }
};