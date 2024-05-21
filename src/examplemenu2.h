#pragma once
#include "Menu.h"

class Example2 : public Menu {
    private:
    public:
    Example2() {

    }
    public:
    void on_buttonPress(int buttonIndex, Button* button) {
        Serial.println("Example 2 did button press");
    }
};