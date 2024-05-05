#pragma once

#include <Arduino.h>
#define DEFAULT_THRESHOLD 65000

class Capacitivetouch {
    private:
        int pinNum;
        int threshold;
        int touchValue; // Added member variable to save touchRead value
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
        
        bool readTouchBool() {
            if (this->touchValue > this->threshold) {
                return true;
            }
            return false;
        }
        void updateTouchValue() { // Renamed readTouchValue to updateTouchValue
            this->touchValue = touchRead(this->pinNum); // Save touchRead value
        }
        int get_touchValue() { // Renamed getSavedTouchValue to get_touchValue
            return this->touchValue;
        }
};