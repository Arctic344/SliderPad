#pragma once
#include "Arduino.h"
#include "Slider.h"
#include "Button.h"
#include "Display.h"
#include "Converter.h"

class Menu {
    private:
        int id;
    public:
        Menu(int id) {
            this->id = id;
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
        virtual uint8_t* get_menuIcon() {
            Serial.println("Warning: MENU BITMAP FUNCTION NOT DEFINED");
            return nullptr;
        }
    public:
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
};