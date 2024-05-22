#pragma once
#include "Node.h"
#include <Arduino.h>
#define DEFAULT_THRESHOLD 65000

/**
 * @class Capacitivetouch
 * @brief Represents a capacitive touch sensing GPIO pin
 * 
 * The Capacitivetouch class provides functionality to interface with a capacitive touch capable GPIO
 * It allows reading the touch value and determining if the touch value exceeds a specified threshold.
 */
class Capacitivetouch : public Node {
    private:
        int pinNum;         // The pin number of the touch sensor
        int threshold;      // The threshold value for touch detection
        int touchValue;     // The current touch value
        
    public:
        /**
         * @brief Constructs a Capacitivetouch object with the specified pin number and threshold.
         * @param pinNum The pin number of the touch sensor.
         * @param threshold The threshold value for touch detection.
         */
        Capacitivetouch(int pinNum, int threshold) {
            this->pinNum = pinNum;
            this->threshold = threshold;
            this->touchValue = 0; // Initialize touchValue
        }
        
        /**
         * @brief Constructs a Capacitivetouch object with the specified pin number and default threshold.
         * @param pinNum The pin number of the touch sensor.
         */
        Capacitivetouch(int pinNum) {
            this->pinNum = pinNum;
            this->threshold = DEFAULT_THRESHOLD;
            this->touchValue = 0; // Initialize touchValue
        }
        
        /**
         * @brief Constructs a Capacitivetouch object with default pin number and threshold.
         */
        Capacitivetouch() {
            this->pinNum = -1;
            this->threshold = DEFAULT_THRESHOLD;
            this->touchValue = 0; // Initialize touchValue
        }
        
        /**
         * @brief Checks if the touch value is above the threshold.
         * @return True if the touch value is above the threshold, false otherwise.
         */
        bool get_touchBool() {
            if (this->touchValue > this->threshold) {
                return true;
            }
            return false;
        }
        
        /**
         * @brief Updates the touch value by reading the touch sensor.
         *        This function is overridden from the Node class.
         */
        void update_nodeValue() override { 
            this->touchValue = touchRead(this->pinNum); 
        }
        
        /**
         * @brief Gets the current touch value.
         * @return The current touch value.
         */
        int get_touchValue() { 
            return this->touchValue;
        }
};