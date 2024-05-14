#include <Adafruit_NeoPixel.h>
#include "CD74HC165E_Button.h"
#include "Strip.h"

class LedCD74HC165E_Button : public CD74HC165E_Button {
    private:
        Strip* ledStrip;
    
    public:
        LedCD74HC165E_Button(int buttonPin, Strip* strip, IC_CD74HC165E* associatedDevice) : CD74HC165E_Button(buttonPin, associatedDevice) {
            ledStrip = strip;
        }
        
        void update_nodeValue() override {
            state = associatedDevice->get_storedBool(this->pin);
            if (state) {
                ledStrip->updateAll(255, 0, 0);
            } else {
                ledStrip->updateAll(0, 0, 0);
            }
        }
};