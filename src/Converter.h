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


class Converter {
public:
    Slider* convertToCenteredSlider(Slider* s) {
        Slider* returnpointer = new CenteredSlider(s->get_motor(), s->get_pot(), s->get_touch());
        delete s;
        return returnpointer;
    }
    Slider* convertToLinearSlider(Slider* s) {
        Slider* returnpointer = new LinearSlider(s->get_motor(), s->get_pot(), s->get_touch());
        delete s;
        return returnpointer;
    }
    Slider* convertToLitLinearSlider(Slider* s, Strip* strip) {
        Slider* returnpointer = new LitLinearSlider(s->get_motor(), s->get_pot(), s->get_touch(),strip);
        delete s;
        return returnpointer;
    }
    Slider* convertToSteppedSlider(Slider* s, int notches) {
        Slider* returnpointer = new SteppedSlider(s->get_motor(), s->get_pot(), s->get_touch(),notches);
        delete s;
        return returnpointer;
    }
    Slider* convertToLitSteppedSlider(Slider* s, int notches, Strip* strip) {
        Slider* returnpointer = new LitSteppedSlider(s->get_motor(), s->get_pot(), s->get_touch(),notches,strip);
        delete s;
        return returnpointer;
    }
    Button* convertToLedButton(Button* b, Strip* strip) {
        Button* returnpointer = new LedButton(b->get_pin(),strip);
        delete b;
        return returnpointer;
    }
    Button* convertToLedCD74HC165E_Button(CD74HC165E_Button* b, Strip* strip) {
        Button* returnpointer = new LedCD74HC165E_Button(b->get_pin(),strip,b->get_associatedDevice());
        delete b;
        return returnpointer;
    }
    Button* convertToButton(Button* b) {
        Button* returnpointer = new Button(b->get_pin());
        delete b;
        return returnpointer;
    }
    Button* convertToCD74HC165E_Button(LedCD74HC165E_Button* b) {
        CD74HC165E_Button* returnpointer = new CD74HC165E_Button(b->get_pin(),b->get_associatedDevice());
        delete b;
        return returnpointer;
    }
};