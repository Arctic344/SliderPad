#pragma once
#include "Menu.h"

class Example1 : public Menu {
    private:
    public:
    Example1() {

    }
    public:
    void on_buttonPress(int buttonIndex, Button* button) {
        Serial.println("Example 1 did button press");
    }
};