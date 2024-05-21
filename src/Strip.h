#include <Adafruit_NeoPixel.h>
#pragma once
class Strip {
    private:
        Adafruit_NeoPixel* strip;
        uint16_t startIndex;
        uint16_t noOfLights;
    public:
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
        
        void updateLed(uint16_t index, uint8_t r, uint8_t g, uint8_t b) {
            strip->setPixelColor(startIndex + index, strip->Color(r, g, b));
        }

        void updateAll(uint8_t r, uint8_t g, uint8_t b) {
            for (int i = startIndex; i < startIndex + noOfLights; i++) {
                strip->setPixelColor(i, strip->Color(r, g, b));
            }
        }
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