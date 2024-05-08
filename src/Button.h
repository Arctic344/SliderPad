#pragma once
#include <Arduino.h>

class Button : public Node{
    private:
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
        
        void update_nodeValue() override {
            state = digitalRead(pin);
        }
};