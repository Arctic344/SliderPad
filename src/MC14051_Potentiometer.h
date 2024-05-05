#pragma once

#include <Arduino.h>
#include "IC_MC14051.h"
#include "potentiometer.h"

class MC14051_Potentiometer : public Potentiometer {
private:
    int PinConnectPoint; // the place where this potentiometer connects to the mux (pins x0 to x7, in int)
    IC_MC14051* associatedMux; // the mux device this Potentiometer is connected to
    int potValue; // variable to save the readPot value

public:
    MC14051_Potentiometer(int PinConnectPoint, IC_MC14051* associatedMux) {
        this->associatedMux = associatedMux;
        this->PinConnectPoint = PinConnectPoint;
    }

    MC14051_Potentiometer() {
        this->associatedMux = nullptr;
        this->PinConnectPoint = 0;
    }
    void update_PotValue() {
        potValue = this->associatedMux->ReadMux(this->PinConnectPoint);;
    }

    int get_potValue() {
        return potValue;
    }
};