#pragma once
#include <Arduino.h>

class Button : public Node{
    protected:
        int pin;
        bool state;
    
    public:
        Button(int buttonPin) {
            pin = buttonPin;
            state = false;
            pinMode(pin, INPUT);
        }
    
        bool get_state() {
            return state;
        }
        
        void virtual update_nodeValue() override {
            state = digitalRead(pin);
        }

        int get_pin() {
            return pin;
        }
};