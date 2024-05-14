#include <Adafruit_NeoPixel.h>
#include "Button.h" // Assuming Button class is defined in Button.h
#include "Strip.h"

class LedButton : public Button {
    private:
        Strip* ledStrip;
    
    public:
        LedButton(int buttonPin, Strip* strip) : Button(buttonPin) {
            ledStrip = strip;
        }
        
        void update_nodeValue() override {
            state = digitalRead(pin);
            if (state) {
                ledStrip->updateAll(255, 0, 0);
            } else {
                ledStrip->updateAll(0, 0, 0);
            }
        }
};