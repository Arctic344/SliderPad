#include <Adafruit_NeoPixel.h>
#include "CD74HC165E_Button.h"
#include "Strip.h"

/**
 * @brief Represents a button with an associated LED strip controlled by a CD74HC165E shift register.
 * 
 * This class extends the CD74HC165E_Button class and adds functionality to control an LED strip based on the button state.
 */
class LedCD74HC165E_Button : public CD74HC165E_Button {
    private:
        Strip* ledStrip; /**< Pointer to the associated LED strip object. */
    
    public:
        /**
         * @brief Constructs a LedCD74HC165E_Button object with the specified button pin, LED strip, and associated CD74HC165E device.
         * 
         * @param buttonPin The pin number to which the button is connected on the Shift register.
         * @param strip Pointer to the LED strip object.
         * @param associatedDevice Pointer to the associated CD74HC165E device object.
         */
        LedCD74HC165E_Button(int buttonPin, Strip* strip, IC_CD74HC165E* associatedDevice) : CD74HC165E_Button(buttonPin, associatedDevice) {
            ledStrip = strip;
        }
        
        /**
         * @brief Updates the button state and controls the LED strip accordingly.
         * 
         * This method overrides the update_nodeValue() method of the base class.
         * It retrieves the current state of the button from the associated CD74HC165E device
         * and updates the LED strip based on the button state.
         */
        void update_nodeValue() override {
            state = associatedDevice->get_storedBool(this->pin);
            if (state) {
                ledStrip->updateAll(255, 0, 0); // Turn on the LED strip with red color
            } else {
                ledStrip->updateAll(0, 0, 0); // Turn off the LED strip
            }
        }
};