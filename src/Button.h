#pragma once
#include <Arduino.h>

class Button {
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
        
        void update_state() {
            state = digitalRead(pin);
        }
};