#pragma once
#include <Arduino.h>
#include "Button.h"
#include "IC_CD74HC165E.h"

class CD74HC165E_Button : public Button {
    private:
        int pin;
        bool state;
        IC_CD74HC165E* associatedDevice; // Additional pointer to IC_CD74HC165E object
    
    public:
        CD74HC165E_Button(int buttonPin, IC_CD74HC165E* associatedDevice) : Button(buttonPin) {
            pin = buttonPin;
            state = false;
            pinMode(pin, INPUT);
            this->associatedDevice = associatedDevice;
        }
    
        bool get_state() {
            return state;
        }
        
        void update_nodeValue() override {
            state = associatedDevice->get_storedBool(this->pin);
        }
};