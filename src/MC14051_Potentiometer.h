#pragma once

#include <Arduino.h>
#include "IC_MC14051.h"
#include "potentiometer.h"

class MC14051_Potentiometer : public Potentiometer {
private:
    IC_MC14051* associatedMux; // the mux device this Potentiometer is connected to

public:
    MC14051_Potentiometer(int pin, IC_MC14051* associatedMux) : Potentiometer(pin) {
        this->associatedMux = associatedMux;
    }

    MC14051_Potentiometer() {
        this->associatedMux = nullptr;
        this->pin = 0;
    }
    void update_PotValue() {
        potValue = this->associatedMux->ReadMux(this->pin);;
    }
};