#pragma once

#include <Arduino.h>
#include "IC_MC14051.h"
#include "Potentiometer.h"

class MC14051_Potentiometer : public Potentiometer {
private:
    IC_MC14051* associatedMux; // the mux device this Potentiometer is connected to

public:
    MC14051_Potentiometer(int pin, IC_MC14051* associatedMux) : Potentiometer(pin) {
        this->associatedMux = associatedMux;
    }
    void update_nodeValue() override {
        potValue = this->associatedMux->ReadMux(this->pin);
    }
}; 