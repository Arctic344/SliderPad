
#pragma once
#include <Arduino.h>

/**
 * @brief A class for the MC14051 Multiplexer.
 * 
 * The `IC_MC14051` class provides a convenient way to interface with the MC14051 Multiplexer.
 * It allows you to read analog values from different channels of the multiplexer.
 */
class IC_MC14051 {
    private:
        int outputPin; ///< The pin connected to the output of the multiplexer.
        int A, B, C; ///< The pins connected to the control inputs of the multiplexer.
    
    public:
        /**
         * @brief Constructs a new IC_MC14051 object.
         * 
         * @param outputPin The pin connected to the output of the multiplexer.
         * @param A The pin connected to the A control input of the multiplexer.
         * @param B The pin connected to the B control input of the multiplexer.
         * @param C The pin connected to the C control input of the multiplexer.
         */
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

        /**
         * @brief Reads the value from the specified pin of the multiplexer.
         * 
         * @param pinToRead The pin number to read from the multiplexer (0-7).
         * @return The value read from the multiplexer, mapped to a range of 0-100.
         *         Returns 0 if an invalid pin number is specified.
         */
        int ReadMux(int pinToRead) {
            if (pinToRead > 7 || pinToRead < 0) {
                Serial.println("Invalid mux channel specified");
                return 0;
            }
            digitalWrite(this->A, pinToRead & 0b001);
            digitalWrite(this->B, (pinToRead & 0b010) >> 1);
            digitalWrite(this->C, (pinToRead & 0b100) >> 2);
            delayMicroseconds(1); // PLEASE REPLACE WITH MEASURED TIME CONSTANT FROM MEASURED INDUCTANCE AND CAPACITANCE
            return map(analogRead(this->outputPin), 0, 4096, 0, 100);
        }
};