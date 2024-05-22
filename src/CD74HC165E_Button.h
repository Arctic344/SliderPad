#pragma once
#include <Arduino.h>
#include "Button.h"
#include "IC_CD74HC165E.h"

/**
 * @class CD74HC165E_Button
 * @brief A class to represent a button connected to a CD74HC165E shift register.
 * 
 * This class extends the Button class and provides additional functionality to work with the CD74HC165E shift register.
 */
class CD74HC165E_Button : public Button {
    protected:
        IC_CD74HC165E* associatedDevice; // Additional pointer to IC_CD74HC165E object
    
    public:
        /**
         * @brief Constructs a CD74HC165E_Button object.
         * 
         * @param buttonPin The pin number to which the button is connected on the Shift register
         * @param associatedDevice A pointer to the IC_CD74HC165E object associated with the button.
         */
        CD74HC165E_Button(int buttonPin, IC_CD74HC165E* associatedDevice) : Button(buttonPin) {
            pin = buttonPin;
            state = false;
            this->associatedDevice = associatedDevice;
        }  

        /**
         * @brief Updates the state of the button based on the value stored in the associated CD74HC165E shift register.
         */
        void update_nodeValue() override {
            state = associatedDevice->get_storedBool(this->pin);
        }

        /**
         * @brief Gets the associated CD74HC165E shift register object.
         * 
         * @return A pointer to the associated IC_CD74HC165E object.
         */
        IC_CD74HC165E* get_associatedDevice() {
            return associatedDevice;
        }
};