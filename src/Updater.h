#include "Button.h"
#include "Potentiometer.h"
#include "Capacitivetouch.h"
#include "IC_CD74HC165E.h"

class Updater {
private:
    Button** buttons;
    Potentiometer** potentiometers;
    Capacitivetouch** capacitivetouches;
    IC_CD74HC165E** ic_cd74hc165es;
    int buttonCount;
    int potentiometerCount;
    int capacitivetouchCount;
    int ic_cd74hc165eCount;

public:
    Updater() {
        buttons = nullptr;
        potentiometers = nullptr;
        capacitivetouches = nullptr;
        ic_cd74hc165es = nullptr;
        buttonCount = 0;
        potentiometerCount = 0;
        capacitivetouchCount = 0;
        ic_cd74hc165eCount = 0;
    }

    ~Updater() {
        delete[] buttons;
        delete[] potentiometers;
        delete[] capacitivetouches;
        delete[] ic_cd74hc165es;
    }

    void addButton(Button* button) {
        Button** newButtons = new Button*[buttonCount + 1];
        for (int i = 0; i < buttonCount; i++) {
            newButtons[i] = buttons[i];
        }
        newButtons[buttonCount] = button;
        delete[] buttons;
        buttons = newButtons;
        buttonCount++;
    }

    void addPotentiometer(Potentiometer* potentiometer) {
        Potentiometer** newPotentiometers = new Potentiometer*[potentiometerCount + 1];
        for (int i = 0; i < potentiometerCount; i++) {
            newPotentiometers[i] = potentiometers[i];
        }
        newPotentiometers[potentiometerCount] = potentiometer;
        delete[] potentiometers;
        potentiometers = newPotentiometers;
        potentiometerCount++;
    }

    void addCapacitiveTouch(Capacitivetouch* capacitivetouch) {
        Capacitivetouch** newCapacitivetouches = new Capacitivetouch*[capacitivetouchCount + 1];
        for (int i = 0; i < capacitivetouchCount; i++) {
            newCapacitivetouches[i] = capacitivetouches[i];
        }
        newCapacitivetouches[capacitivetouchCount] = capacitivetouch;
        delete[] capacitivetouches;
        capacitivetouches = newCapacitivetouches;
        capacitivetouchCount++;
    }
    
    void addIC_CD74HC165E(IC_CD74HC165E* ic_cd74hc165e) {
        IC_CD74HC165E** newIC_CD74HC165Es = new IC_CD74HC165E*[ic_cd74hc165eCount + 1];
        for (int i = 0; i < ic_cd74hc165eCount; i++) {
            newIC_CD74HC165Es[i] = ic_cd74hc165es[i];
        }
        newIC_CD74HC165Es[ic_cd74hc165eCount] = ic_cd74hc165e;
        delete[] ic_cd74hc165es;
        ic_cd74hc165es = newIC_CD74HC165Es;
        ic_cd74hc165eCount++;
    }
    
    void update_Components() {
        for (int i = 0; i < ic_cd74hc165eCount; i++) {
            ic_cd74hc165es[i]->update_storedValue();
        }
        for (int i = 0; i < buttonCount; i++) {
            buttons[i]->update_state();
        }
        for (int i = 0; i < potentiometerCount; i++) {
            potentiometers[i]->update_PotValue();
        }
        for (int i = 0; i < capacitivetouchCount; i++) {
            capacitivetouches[i]->updateTouchValue();
        }

    }
};