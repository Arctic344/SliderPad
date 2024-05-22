#pragma once

#include <Arduino.h>
#include "IC_MC14051.h"
#include "Potentiometer.h"

/**
 * @brief Represents a potentiometer connected to an MC14051 multiplexer.
 * 
 * This class inherits from the Potentiometer class and provides additional functionality
 * specific to the MC14051 multiplexer.
 */
class MC14051_Potentiometer : public Potentiometer {
private:
    IC_MC14051* associatedMux; // the mux device this Potentiometer is connected to

public:
    /**
     * @brief Constructs an MC14051_Potentiometer object.
     * 
     * @param pin The pin number to which the potentiometer is connected on the multiplexer.
     * @param associatedMux A pointer to the associated MC14051 multiplexer.
     */
    MC14051_Potentiometer(int pin, IC_MC14051* associatedMux) : Potentiometer(pin) {
        this->associatedMux = associatedMux;
    }

    /**
     * @brief Updates the node value of the potentiometer.
     * 
     * This function reads the value of the potentiometer from the associated MC14051 multiplexer
     * and updates the `potValue` member variable.
     */
    void update_nodeValue() override {
        potValue = this->associatedMux->ReadMux(this->pin);
    }
};
