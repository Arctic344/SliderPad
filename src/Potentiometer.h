#pragma once
#include <Arduino.h>
#include "Node.h"

/**
 * @class Potentiometer
 * @brief Represents a potentiometer sensor.
 * 
 * The Potentiometer class is a subclass of the Node class and is used to interface with a potentiometer sensor.
 * It provides methods to read the potentiometer value and update the node value based on the potentiometer reading.
 */
class Potentiometer : public Node {
protected:
    int pin; /**< The pin number to which the potentiometer is connected. */
    int potValue; /**< The current value of the potentiometer. */

public:
    /**
     * @brief Constructs a Potentiometer object.
     * 
     * @param pin The pin number to which the potentiometer is connected.
     */
    Potentiometer(int pin) {
        this->pin = pin;
        pinMode(pin, INPUT);
        potValue = 0; // initialize potValue to 0
    }

    /**
     * @brief Gets the current value of the potentiometer.
     * 
     * @return The current value of the potentiometer.
     */
    int get_potValue() {
        return this->potValue; 
    }

    /**
     * @brief Updates the node value based on the potentiometer reading.
     * 
     * This method reads the analog value from the potentiometer, maps it to a range of 0-100,
     * and saves the mapped value in the potValue variable.
     */
    void update_nodeValue() override {
        potValue = map(analogRead(pin), 0, 4095, 0, 100); // save the mapped potValue in potValue
    }
};