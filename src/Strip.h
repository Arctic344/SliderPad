#include <Adafruit_NeoPixel.h>
#pragma once
/**
 * @brief Represents a substrip for an Adafruit_NeoPixel strip.
 * 
 * The `Strip` class provides a way to control a subset of LEDs on an Adafruit_NeoPixel strip.
 * It allows you to update individual LEDs, update all LEDs at once, and update a percentage of LEDs.
 */
class Strip {
    private:
        Adafruit_NeoPixel* strip;   ///< Pointer to the Adafruit_NeoPixel strip object.
        uint16_t startIndex;        ///< Index of the first LED in the substrip.
        uint16_t noOfLights;         ///< Number of LEDs in the substrip.
    public:
        /**
         * @brief Constructs a `Strip` object.
         * 
         * @param strip Pointer to the Adafruit_NeoPixel strip object.
         * @param startIndex Index of the first LED in the substrip.
         * @param noOfLights Number of LEDs in the substrip.
         */
        Strip(Adafruit_NeoPixel* strip, uint16_t startIndex, uint16_t noOfLights) {
            this->strip = strip;
            this->startIndex = startIndex;
            if (strip->numPixels() < startIndex + noOfLights) {
                this->noOfLights = noOfLights;
            } else {
                this->noOfLights = strip->numPixels() - startIndex;
            }
            this->noOfLights = noOfLights;
        }
        
        /**
         * @brief Updates the color of a specific LED in the substrip.
         * 
         * @param index Index of the LED to update.
         * @param r Red color component (0-255).
         * @param g Green color component (0-255).
         * @param b Blue color component (0-255).
         */
        void updateLed(uint16_t index, uint8_t r, uint8_t g, uint8_t b) {
            strip->setPixelColor(startIndex + index, strip->Color(r, g, b));
        }

        /**
         * @brief Updates the color of all LEDs in the substrip.
         * 
         * @param r Red color component (0-255).
         * @param g Green color component (0-255).
         * @param b Blue color component (0-255).
         */
        void updateAll(uint8_t r, uint8_t g, uint8_t b) {
            for (int i = startIndex; i < startIndex + noOfLights; i++) {
                strip->setPixelColor(i, strip->Color(r, g, b));
            }
        }

        /**
         * @brief Updates the color of a percentage of LEDs in the substrip.
         * 
         * @param percentage Percentage of LEDs to light up (0-100).
         * @param r Red color component (0-255).
         * @param g Green color component (0-255).
         * @param b Blue color component (0-255).
         */
        void updatePercentage(uint8_t percentage, uint8_t r, uint8_t g, uint8_t b) {
            uint16_t noOfLightsToLight = (percentage * noOfLights) / 100;
            for (int i = startIndex; i < startIndex + noOfLightsToLight; i++) {
                strip->setPixelColor(i, strip->Color(r, g, b));
            }
            for (int i = startIndex + noOfLightsToLight; i < startIndex + noOfLights; i++) {
                strip->setPixelColor(i, strip->Color(0, 0, 0));
            }
        }
};