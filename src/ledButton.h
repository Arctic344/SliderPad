#include <Adafruit_NeoPixel.h>
#include "Button.h" 
#include "Strip.h"

/**
 * @brief Represents an LED button that extends the Button class.
 * 
 * The LedButton class is used to control an LED strip based on the state of a button.
 * It inherits from the Button class and adds functionality to update the LED strip based on the button state.
 */
class LedButton : public Button {
    private:
        Strip* ledStrip;
    
    public:
        /**
         * @brief Constructs a LedButton object with the specified button pin and LED strip.
         * 
         * @param buttonPin The pin number of the button.
         * @param strip A pointer to the LED strip object.
         */
        LedButton(int buttonPin, Strip* strip) : Button(buttonPin) {
            ledStrip = strip;
        }
        
        /**
         * @brief Updates the node value of the LedButton.
         * 
         * This function overrides the update_nodeValue() function of the Button class.
         * It reads the state of the button and updates the LED strip accordingly.
         * If the button is pressed, the LED strip is set to red (255, 0, 0).
         * If the button is not pressed, the LED strip is turned off (0, 0, 0).
         */
        void update_nodeValue() override {
            state = digitalRead(pin);
            if (state) {
                ledStrip->updateAll(255, 0, 0);
            } else {
                ledStrip->updateAll(0, 0, 0);
            }
        }
};