#pragma once

#include <Arduino.h>


class ShiftRegister {
private:
    int dataPin;
    int clockPin;
    int latchPin;

public:
    ShiftRegister(int dataPin, int clockPin, int latchPin) {
        this->dataPin = dataPin;
        this->clockPin = clockPin;
        this->latchPin = latchPin;

        pinMode(dataPin, INPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(latchPin, OUTPUT);
    }

    byte read() {
        byte value = 0;

        digitalWrite(latchPin, LOW);
        delayMicroseconds(1); // small delay for stability
        digitalWrite(latchPin, HIGH);
        for (int i = 0; i < 8; i++) {
            value |= digitalRead(dataPin) << (7 - i);
            digitalWrite(clockPin, HIGH);
            delayMicroseconds(1); // small delay for stability
            digitalWrite(clockPin, LOW);
        }

        return value;
    }
};