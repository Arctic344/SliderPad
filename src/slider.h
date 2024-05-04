#pragma once
#include "pot.h"
#include "motor.h"
#include "capacitivetouch.h"
#include "Arduino.h"

class Slider { // Class dedicated to driving the SM10001NKA0X-HA1-019 Motorised Linear Potentiometer
    private:
        Pot pot;
        Motor motor;
        Capacitivetouch touch;
        int16_t currentposition;
        bool currenttouched;
        int16_t goalPosition;
        int16_t calibrateLow;
        int16_t calibrateHigh;
    
    public:
        Slider(Pot pot, Motor motor, Capacitivetouch touch) { // regular declaration
            this->pot = pot;
            this->motor = motor;
            this->touch = touch;
        }
        Slider() { // fake declaration
            Pot p;
            Motor m;
            Capacitivetouch c;
            this->pot = p;
            this->motor = m;
            this->touch = c;
            Serial.println("Warning: A slider was not created properly, please check your code");
        }
        void calibrate() {
                  
        }

};