#pragma once
#include "Menu.h"
#include "Converter.h"
#include "Manager.h" // Include the header file for the Manager class

class Example4 : public Menu {
    public:
    Example4() : Menu(1){

    }
    public:
    void on_ButtonPress(int buttonIndex, Button* button) override{
        manager->get_sliderPosition(0);
    }
};