#include <Arduino.h>

class IC_CD74HC165E {
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

    void update_storedValue() {
        storedValue = 0;
        // Pulse the load pin to move the data from the shift register to storage register
        digitalWrite(loadPin, HIGH);
        delayMicroseconds(2); // Adjust delay as needed
        digitalWrite(loadPin, LOW);
        // Read each bit serially
        for (int j = 0; j < noOfChainedRegisters; j++) {
            for (int i = 0; i < 8; i++) {
                digitalWrite(clockPin, HIGH);
                delayMicroseconds(1); // Adjust delay as needed
                storedValue |= static_cast<uint64_t>(digitalRead(dataPin)) << (63 - (j * 8 + i)); // Read data from data pin
                digitalWrite(clockPin, LOW);
                delayMicroseconds(1);
            }
        }
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
