#include <Arduino.h>

class Potentiometer {
protected:
    int pin;
    int potValue; // private variable to store the readPot value

public:
    Potentiometer() {
        pin = -1; // this will throw an error
        potValue = 0; // initialize potValue to 0
    }

    Potentiometer(int pin) {
        this->pin = pin;
        pinMode(pin, INPUT);
        potValue = 0; // initialize potValue to 0
    }

    int get_potValue() {
        return this->potValue; 
    }

    void update_PotValue() {
        potValue = map(analogRead(pin), 0, 4095, 0, 100); // save the mapped potValue in potValue
    }
};