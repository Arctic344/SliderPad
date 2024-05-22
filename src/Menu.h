#pragma once
#include "Arduino.h"
#include "Slider.h"
#include "Button.h"
#include "Display.h"
#include "Converter.h"

class Manager; // foreward declaration since i will have a loop here

/**
 * @class Menu
 * @brief A base class for menus.
 * 
 * The `Menu` class provides a base implementation for menus in a user interface. It contains common functionality and virtual functions that can be overridden by derived classes to customize the behavior of specific menus.
 * 
 * The `Menu` class is designed to be inherited from and extended to create different types of menus.
 * 
 * It can be instantiated with a unique ID that can be used to identify the menu.
 */
class Menu {
    private:
        int id;
    protected:
        Manager* manager;
    public:
        Menu(int id) {
            this->id = id;
        }
        virtual void on_setup() {
            Serial.println("Warning: MENU SETUP FUNCTION NOT DEFINED");
            return;
        }
        virtual void run_menu() {
            Serial.println("Warning: MENU RUN FUNCTION NOT DEFINED");
            return;
        }
        virtual void  draw_menu() {
            Serial.println("Warning: MENU DRAW FUNCTION NOT DEFINED");
            return;

        }
        virtual bool is_menuActive() {
            return true;
        }
        virtual void menu_background_action() {
            Serial.println("Warning: MENU BACKGROUND ACTION FUNCTION NOT DEFINED");
            return;
        }
        virtual uint8_t* get_menuIcon() {
            Serial.println("Warning: MENU BITMAP FUNCTION NOT DEFINED");
            return nullptr;
        }
    public:
        virtual void  on_SliderChange(int sliderIndex, Slider* slider) {
            Serial.println("Warning: SLIDER CHANGE FUNCTION NOT DEFINED");
            return;
        }
        virtual void  on_SliderRelease(int sliderIndex, Slider* slider) {
            Serial.println("Warning: SLIDER RELEASE FUNCTION NOT DEFINED");
            return;
        }
        virtual void  on_SliderTouch(int sliderIndex, Slider* slider) {
            Serial.println("Warning: SLIDER TOUCH FUNCTION NOT DEFINED");
            return;
        }
        virtual void  on_ButtonPress(int buttonIndex, Button* button) {
            Serial.println("Warning: BUTTON PRESS FUNCTION NOT DEFINED"); 
            return;
        }
        virtual void  on_ButtonRelease(int buttonIndex, Button* button) {
            Serial.println("Warning: BUTTON RELEASE FUNCTION NOT DEFINED");
            return;
        }
        virtual void  on_ButtonHold(int buttonIndex, Button* button) {
            Serial.println("Warning: BUTTON HOLD FUNCTION NOT DEFINED");
            return;
        }
        virtual void  on_MenuSelected() {
            Serial.println("Warning: MENU SELECTED FUNCTION NOT DEFINED");
            return;
        }
        virtual void  on_MenuDeselected() {
            Serial.println("Warning: MENU DESELECTED FUNCTION NOT DEFINED");
            return;
        }
        int get_id() {
            return id;
        }
        void set_manager(Manager* manager) {
            this->manager = manager;
        }
};