#include "Arduino.h"
#include "Slider.h"
#include "Button.h"
#include "Display.h"
#include "Converter.h"
#pragma once

class Menu {
    private:
        Slider** sliders;
        Button** buttons;
        int buttonCount;
        int sliderCount;
        Display* display;
        int* buttonPressTimeout;
        int* buttonHoldTimein;
        int* buttonReleaseTimeout;
        int* sliderTouchTimeout;
        int* sliderReleaseTimeout;
        int* sliderChangeTimeout;
        int* slidersLastPosition;
        int* buttonsLastState;
        long lastScanTime;
        long* lastbuttonPressTime;
        long* lastsliderTouchTime;
    public:
        Menu(Slider** sliders, int sliderCount, Button** buttons, int buttonCount, Display* display) {
            this->sliders = sliders;
            this->sliderCount = sliderCount;
            this->buttons = buttons;
            this->buttonCount = buttonCount;
            this->display = display;
            buttonPressTimeout = new int[buttonCount];
            buttonHoldTimein = new int[buttonCount];
            buttonReleaseTimeout = new int[buttonCount];
            sliderTouchTimeout = new int[sliderCount];
            sliderReleaseTimeout = new int[sliderCount];
            sliderChangeTimeout = new int[sliderCount];
            slidersLastPosition = new int[sliderCount];
            buttonsLastState = new int[buttonCount];
            for (int i = 0; i < buttonCount; i++) {
                buttonPressTimeout[i] = 100;
                buttonHoldTimein[i] = 1000;
                buttonReleaseTimeout[i] = 100;
            }
            for (int i = 0; i < sliderCount; i++) {
                sliderTouchTimeout[i] = 200;
                sliderReleaseTimeout[i] = 200;
                sliderChangeTimeout[i] = 1000;
            }
        }
        void virtual scanEvents() final {     
        }
        
        void virtual run_menu() {
            Serial.println("Warning: MENU RUN FUNCTION NOT DEFINED");
            return;
        }
        void virtual draw_menu() {
            Serial.println("Warning: MENU DRAW FUNCTION NOT DEFINED");
            return;
        }
        
        bool virtual is_menuActive() {
            return true;
        }
        void virtual menu_background_action() {
            Serial.println("Warning: MENU BACKGROUND ACTION FUNCTION NOT DEFINED");
            return;
        }
    protected:
        void virtual on_SliderChange(int sliderIndex, Slider* slider) {
            return;
        }
        void virtual on_SliderRelease(int sliderIndex, Slider* slider) {
            return;
        }
        void virtual on_SliderTouch(int sliderIndex, Slider* slider) {
            return;
        }
        void virtual on_ButtonPress(int buttonIndex, Button* button) {
            return;
        }
        void virtual on_ButtonRelease(int buttonIndex, Button* button) {
            return;
        }
        void virtual on_ButtonHold(int buttonIndex, Button* button) {
            return;
        }
        void virtual on_MenuSelected() {
            Serial.println("Warning: MENU SELECTED FUNCTION NOT DEFINED");
            return;
        }
        void virtual on_MenuDeselected() {
            Serial.println("Warning: MENU DESELECTED FUNCTION NOT DEFINED");
            return;
        }
    protected:
        bool get_ButtonState(int buttonIndex) {
            return buttons[buttonIndex]->get_state();
        }
        int get_SliderRawPosition(int sliderIndex) {
            return sliders[sliderIndex]->get_rawPosition();
        }
        int get_SliderPosition(int sliderIndex) {
            return sliders[sliderIndex]->get_position();
        }
        void set_ButtonPressTimeout(int buttonIndex, int timeout) {
            buttonPressTimeout[buttonIndex] = timeout;
        }
       

};