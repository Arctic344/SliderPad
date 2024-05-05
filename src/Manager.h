#include <Arduino.h>
#include <Slider.h>
#include <Button.h>

class Manager {
private:
    Slider** sliders; // Dynamic array to store sliders
    Button** buttons; // Dynamic array to store buttons
    int sliderCount; // Number of sliders in the array
    int buttonCount; // Number of buttons in the array

public:
    Manager() {
        sliders = nullptr;
        buttons = nullptr;
        sliderCount = 0;
        buttonCount = 0;
    }

    ~Manager() {
        delete[] sliders;
        delete[] buttons;
    }

    void add_slider(Slider* slider) {
        Slider** temp = new Slider*[sliderCount + 1];
        for (int i = 0; i < sliderCount; i++) {
            temp[i] = sliders[i];
        }
        temp[sliderCount] = slider;
        delete[] sliders;
        sliders = temp;
        sliderCount++;
    }

    void add_button(Button* button) {
        Button** temp = new Button*[buttonCount + 1];
        for (int i = 0; i < buttonCount; i++) {
            temp[i] = buttons[i];
        }
        temp[buttonCount] = button;
        delete[] buttons;
        buttons = temp;
        buttonCount++;
    }

    void () {

    }
};