#pragma once
#include <Arduino.h>
#include "Node.h"

/**
 * @brief Represents a shift register IC (CD74HC165E).
 * 
 * This class provides functionality to interface with a CD74HC165E shift register IC.
 * It allows reading the state of multiple input pins using a minimal number of microcontroller pins.
 */
class IC_CD74HC165E : public Node {
private:
    int dataPin;                 // Serial Data Input (DS)
    int clockPin;                // Shift Register Clock Input (SH_CP)
    int loadPin;                 // Storage Register Clock Input (ST_CP)
    int noOfChainedRegisters;    // Number of chained registers
    uint64_t storedValue;        // Private variable to store the read value

public:
    /**
     * @brief Constructs an instance of the IC_CD74HC165E class with the specified parameters.
     * 
     * @param data The pin number for the Serial Data Input (DS) pin.
     * @param clock The pin number for the Shift Register Clock Input (SH_CP) pin.
     * @param load The pin number for the Storage Register Clock Input (ST_CP) pin.
     * @param noOfRegisters The number of chained registers.
     */
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

    /**
     * @brief Constructs an instance of the IC_CD74HC165E class with the specified parameters and a default of 1 chained register.
     * 
     * @param data The pin number for the Serial Data Input (DS) pin.
     * @param clock The pin number for the Shift Register Clock Input (SH_CP) pin.
     * @param load The pin number for the Storage Register Clock Input (ST_CP) pin.
     */
    IC_CD74HC165E(int data, int clock, int load) : IC_CD74HC165E(data, clock, load, 1) {
        // Default constructor with 1 chained register
    }

    /**
     * @brief Updates the stored value by reading the state of the shift register.
     * 
     * This function reads the state of the shift register and stores the value internally.
     * It should be called whenever the state of the shift register needs to be updated.
     */
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

    /**
     * @brief Gets the stored value of the shift register.
     * 
     * @return The stored value of the shift register as a 64-bit unsigned integer.
     */
    uint64_t get_storedValue() {
        return storedValue;
    }

    /**
     * @brief Gets the state of a specific bit in the stored value.
     * 
     * @param n The index of the bit to retrieve (0-63).
     * @return The state of the specified bit (true if the bit is set, false otherwise).
     */
    bool get_storedBool(int n) {
        if (n < 0 || n >= 64) {
            return false;
        }
        return (storedValue >> n) & 1;
    }
};
