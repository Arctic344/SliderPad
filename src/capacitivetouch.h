#pragma once

#include <Arduino.h>
#define DEFAULT_THRESHOLD 65000

class Capacitivetouch {
    private:
        int pinNum;
        int threshold;
        int touchValue; 
    public:
        Capacitivetouch(int pinNum, int threshold) {
            this->pinNum = pinNum;
            this->threshold = threshold;
            this->touchValue = 0; // Initialize touchValue
        }
        Capacitivetouch(int pinNum) {
            this->pinNum = pinNum;
            this->threshold = DEFAULT_THRESHOLD;
            this->touchValue = 0; // Initialize touchValue
        }
        Capacitivetouch() {
            this->pinNum = -1;
            this->threshold = DEFAULT_THRESHOLD;
            this->touchValue = 0; // Initialize touchValue
        }
        
        bool get_touchBool() {
            if (this->touchValue > this->threshold) {
                return true;
            }
            return false;
        }
        void updateTouchValue() { 
            this->touchValue = touchRead(this->pinNum); 
        }
        int get_touchValue() { 
            return this->touchValue;
        }
};