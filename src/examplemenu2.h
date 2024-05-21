#pragma once
#include "Menu.h"

class Example2 : public Menu {
    private:
    public:
    Example2() : Menu(1) {

    }
    public:
    void on_ButtonPress(int buttonIndex, Button* button) override{
        Serial.println("Example 2 did button press");
    }
};