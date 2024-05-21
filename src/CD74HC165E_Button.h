#pragma once
#include <Arduino.h>
#include "Button.h"
#include "IC_CD74HC165E.h"

class CD74HC165E_Button : public Button {
    protected:
        IC_CD74HC165E* associatedDevice; // Additional pointer to IC_CD74HC165E object
    
    public:
        CD74HC165E_Button(int buttonPin, IC_CD74HC165E* associatedDevice) : Button(buttonPin) {
            pin = buttonPin;
            state = false;
            this->associatedDevice = associatedDevice;
        }  
        void update_nodeValue() override {
            state = associatedDevice->get_storedBool(this->pin);
        }

        IC_CD74HC165E* get_associatedDevice() {
            return associatedDevice;
        }
};