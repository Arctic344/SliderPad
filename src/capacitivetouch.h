#pragma once

#include <Arduino.h>
#define DEFAULT_THRESHOLD 65000

class Capacitivetouch {
    private:
        int pinNum;
        int threshold;
    public:
        Capacitivetouch(int pinNum, int threshold) {
                this->pinNum=pinNum;
                this->threshold = threshold;
            }
        Capacitivetouch(int pinNum) {
            this->pinNum=pinNum;
            this->threshold = DEFAULT_THRESHOLD;
        }
        Capacitivetouch() {
            this->pinNum = -1;
            this->threshold = DEFAULT_THRESHOLD;
        }
        bool readTouchBool() {
            if (touchRead(this->pinNum) > this->threshold) {
                return true;
            }
            return false;
        }
        int readTouchValue() {
            return touchRead(this->pinNum);
        }
};