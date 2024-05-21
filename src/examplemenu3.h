#pragma once
#include "Menu.h"
#include "AdafruitIO_WiFi.h"

class Example3 : public Menu {
    private:
    public:
    Example3() : Menu(1) {

    }
    public:
    bool is_menuActive() override{
        return true;
    }
    void on_ButtonPress(int buttonIndex, Button* button) override{
        Serial.println("Example 3 did button press");
    }
};