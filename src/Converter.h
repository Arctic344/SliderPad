#pragma once
#include "sliderclasses/centeredslider.h"
#include "sliderclasses/linearslider.h"
#include "sliderclasses/litlinearslider.h"
#include "sliderclasses/steppedslider.h"
#include "sliderclasses/litsteppedslider.h"
#include "Button.h"
#include "ledButton.h"
#include "ledCD74HC165E_Button.h"
#include "Strip.h"


/**
 * @brief A converter that converts different objects into compatible other objects during runtime.
 * 
 * The `Converter` class provides static methods to convert objects of one type to another type.
 * It is designed to convert `Slider` and `Button` objects into different types of sliders and buttons,
 * based on the provided parameters.
 * 
 * The converted objects are dynamically allocated and the original objects are deleted.
 * 
 * Usage example:
 * ```
 * Slider* slider = new Slider();
 * Slider* centeredSlider = Converter::convertToCenteredSlider(slider);
 * ```
 */
class Converter {
public:
    Converter() {
    }
    static Slider* convertToCenteredSlider(Slider* s) {
        Slider* returnpointer = new CenteredSlider(s->get_motor(), s->get_pot(), s->get_touch());
        delete s;
        return returnpointer;
    }
    static Slider* convertToLinearSlider(Slider* s) {
        Slider* returnpointer = new LinearSlider(s->get_motor(), s->get_pot(), s->get_touch());
        delete s;
        return returnpointer;
    }
    static Slider* convertToLitLinearSlider(Slider* s, Strip* strip) {
        Slider* returnpointer = new LitLinearSlider(s->get_motor(), s->get_pot(), s->get_touch(),strip);
        delete s;
        return returnpointer;
    }
    static Slider* convertToSteppedSlider(Slider* s, int notches) {
        Slider* returnpointer = new SteppedSlider(s->get_motor(), s->get_pot(), s->get_touch(),notches);
        delete s;
        return returnpointer;
    }
    static Slider* convertToLitSteppedSlider(Slider* s, int notches, Strip* strip) {
        Slider* returnpointer = new LitSteppedSlider(s->get_motor(), s->get_pot(), s->get_touch(),notches,strip);
        delete s;
        return returnpointer;
    }
    static Button* convertToLedButton(Button* b, Strip* strip) {
        Button* returnpointer = new LedButton(b->get_pin(),strip);
        delete b;
        return returnpointer;
    }
    static Button* convertToLedCD74HC165E_Button(CD74HC165E_Button* b, Strip* strip) {
        Button* returnpointer = new LedCD74HC165E_Button(b->get_pin(),strip,b->get_associatedDevice());
        delete b;
        return returnpointer;
    }
    static Button* convertToButton(Button* b) {
        Button* returnpointer = new Button(b->get_pin());
        delete b;
        return returnpointer;
    }
    static Button* convertToCD74HC165E_Button(LedCD74HC165E_Button* b) {
        CD74HC165E_Button* returnpointer = new CD74HC165E_Button(b->get_pin(),b->get_associatedDevice());
        delete b;
        return returnpointer;
    }   
    /**
     * Converts RGB color values to 16-bit RGB565 format.
     *
     * @param red The red component of the RGB color (0-255).
     * @param green The green component of the RGB color (0-255).
     * @param blue The blue component of the RGB color (0-255).
     * @return The 16-bit RGB565 color value. 
     */
    static uint16_t RGBto565(uint8_t red, uint8_t green, uint8_t blue) {
        // Mask and shift the red component to 5 bits
        uint16_t r = (red >> 3) & 0x1F;
        // Mask and shift the green component to 6 bits
        uint16_t g = (green >> 2) & 0x3F;
        // Mask and shift the blue component to 5 bits
        uint16_t b = (blue >> 3) & 0x1F;

        // Combine the components into a single 16-bit value
        uint16_t rgb565 = (r << 11) | (g << 5) | b;

        return rgb565;
    }
};