#pragma once
#include <Arduino.h>
#include "Node.h"

/**
 * @class Button
 * @brief Represents a button connected directly to a GPIO pin
 * @details The `Button` class provides functionality to interact with a button connected to a specific GPIO.
 */
class Button : public Node {
    protected:
        int pin;
        bool state;
    
    public:
        /**
         * @brief Constructs a `Button` object with the specified pin number.
         * 
         * @param buttonPin The pin number to which the button is connected.
         */
        Button(int buttonPin) {
            pin = buttonPin;
            state = false;
            pinMode(pin, INPUT);
        }
    
        /**
         * @brief Get the current state of the button.
         * 
         * @return true if the button is pressed, false otherwise.
         */
        bool get_state() {
            return state;
        }
        
        /**
         * @brief Update the state of the button based on the current pin reading.
         */
        void virtual update_nodeValue() override {
            state = digitalRead(pin);
        }

        /**
         * @brief Get the pin number to which the button is connected.
         * 
         * @return The pin number.
         */
        int get_pin() {
            return pin;
        }
};