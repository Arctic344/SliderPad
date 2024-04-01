#pragma once

#include <Arduino.h>
#include "mux.h"

class Pot {
    private:
        int PinConnectPoint; // the place where this potentiometer connects to the mux (pins x0 to x7, in int)
        Mux* associatedMux; // the mux device this Potentiometer is connected to
    public:
        Pot(int PinConnectPoint, Mux* associatedMux) {
            this->associatedMux = associatedMux;
            this->PinConnectPoint = PinConnectPoint;
        }
        Pot() {
            this->associatedMux = nullptr;
            this->PinConnectPoint = 0;
        }

        int readPot() {
            return this->associatedMux->ReadMux(this->PinConnectPoint); // returns the reading for the mux
        }
};