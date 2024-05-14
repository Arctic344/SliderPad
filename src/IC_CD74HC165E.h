#pragma once
#include <Arduino.h>
#include "Node.h"

class IC_CD74HC165E : public Node {
private:
    int dataPin;                 // Serial Data Input (DS)
    int clockPin;                // Shift Register Clock Input (SH_CP)
    int loadPin;                 // Storage Register Clock Input (ST_CP)
    int noOfChainedRegisters;    // Number of chained registers
    uint64_t storedValue;        // Private variable to store the read value

public:
    IC_CD74HC165E(int data, int clock, int load, int noOfRegisters) {
        dataPin = data;
        clockPin = clock;
        loadPin = load;
        noOfChainedRegisters = noOfRegisters;

        pinMode(dataPin, INPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(loadPin, OUTPUT);

        digitalWrite(loadPin, LOW);  // Set load pin LOW initially
    }

    IC_CD74HC165E(int data, int clock, int load) : IC_CD74HC165E(data, clock, load, 1) {
        // Default constructor with 1 chained register
    }

    void update_nodeValue() override {
        uint64_t data = 0;  
        digitalWrite(loadPin, LOW); // Pull latch low to start the data transfer
        delayMicroseconds(5); // Small delay
        digitalWrite(loadPin, HIGH); // Release latch to update shift register outputs
        for (int i = 0; i < (8*noOfChainedRegisters); ++i) {
            // Shift in each bit from the CD74HC165E
            digitalWrite(clockPin, HIGH); // Clock in the next bit
            delayMicroseconds(5); // Small delay
            bool bitValue = digitalRead(dataPin); // Read the bit from DATA_PIN
            data |= (bitValue << (7 - i)); // Store the bit in the data byte
            digitalWrite(clockPin, LOW); // Clock down
            delayMicroseconds(5); // Small delay
        }
        storedValue = data; // Store the read value
    }

    uint64_t get_storedValue() {
        return storedValue;
    }

    bool get_storedBool(int n) {
        if (n < 0 || n >= 64) {
            return false;
        }
        return (storedValue >> n) & 1;
    }
};
