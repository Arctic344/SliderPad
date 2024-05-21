#pragma once
#include "Menu.h"

class Example1 : public Menu {
    public:
    Example1() : Menu(1){

    }
    public:
    void on_ButtonPress(int buttonIndex, Button* button) override{
        Serial.println("Example 1 did button press");
    }
};