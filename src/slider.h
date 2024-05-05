#pragma once
#include "MC14051_Potentiometer.h"
#include "motor.h"
#include "capacitivetouch.h"
#include "Arduino.h"

class Slider { // Class dedicated to driving the SM10001NKA0X-HA1-019 Motorised Linear Potentiometer
    private:
        MC14051_Potentiometer pot;
        Motor motor;
        Capacitivetouch touch;
        int16_t currentposition;
        bool currenttouched;
        int16_t goalPosition;
        int16_t calibrateLow;
        int16_t calibrateHigh;
    
    public:
        virtual void updateSystem();
        
        void calibrate() {
            
        }

};