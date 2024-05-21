#pragma once
#include "Menu.h"

class Example3 : public Menu {
    private:
    public:
    Example3() : Menu(1) {

    }
    public:
    bool is_menuActive() override{
        if (millis()%10000 < 5000) {
            return true;
        }
        else {
            return false;
        }
    }
    void on_ButtonPress(int buttonIndex, Button* button) override{
        Serial.println("Example 3 did button press");
    }
};