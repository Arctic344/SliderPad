
#pragma once
#include <Arduino.h>

class IC_MC14051 {
    private:
        int outputPin;
        int A,B,C;
    
    public:
        IC_MC14051(int outputPin, int A, int B, int C) {
            this->outputPin = outputPin;
            this->A = A;
            this->B = B;
            this->C = C;
            pinMode(this->outputPin, INPUT);
            pinMode(this->A, OUTPUT);
            pinMode(this->B, OUTPUT);
            pinMode(this->C, OUTPUT);
        }

        int ReadMux(int pinToRead) {
            if (pinToRead > 7 || pinToRead < 0) {
                Serial.println("Invalid mux channel specified");
                return 0;
            }
            digitalWrite(this->A, pinToRead& 0b001);
            digitalWrite(this->B, (pinToRead& 0b010) >> 1);
            digitalWrite(this->C, (pinToRead& 0b100) >> 2);
            delayMicroseconds(1); // PLEASE REPLACE WITH MEASURED TIME CONSTANT FROM MEASURED INDUCTABNCE AND CAPACITANCE
            return map(analogRead(this->outputPin),0,4096,0,100);

        }
};