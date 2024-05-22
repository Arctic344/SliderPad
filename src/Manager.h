#pragma once
#include <Arduino.h>
#include <Slider.h>
#include <Button.h>
#include <Updater.h>
#include <Display.h>
#include <Menu.h>
#include <sliderclasses/steppedslider.h>
#include "Converter.h"
#include "Adafruit_NeoPixel.h"
#include "Strip.h"

/**
 * @brief Updates the device by performing various tasks such as timing, updating components, and handling input events.
 * 
 * This function is responsible for updating the device by performing the following tasks:
 * - Setting up the timing by calculating the current time and the time since the last scan.
 * - Updating all components, including the menu select slider and sliders.
 * - Reading the states of all buttons and sliders.
 * - Updating the list of active menus and changing the system if new menus are active.
 * - Checking if the menu select slider value has changed and changing the menus accordingly.
 * - Checking if menu buttons have been pressed or released and triggering the corresponding events.
 * - Running the active menu's logic.
 * - Checking if sliders have been touched, released, or moved and triggering the corresponding events.
 * - Checking if buttons have been pressed and triggering the corresponding events.
 * 
 */
class Manager {
private:
    SteppedSlider* menuSelectSlider;
    Button** menuButtons;
    int menuButtonCount;
    Updater* updater;
    Converter* converter;
    int currentMenuIndex;
    Menu** menus;
    Menu** activeMenus;
    int menuCount;
    int amountOfActiveMenus;
    int MenuSwitchTimeout;
    int* menuButtonsLastState;
    long* lastMenuButtonPressTime;
    int* menuButtonPressTimeout;
    int menuSlidersLastPosition;
    long lastMenuSwitchTime;
    Strip* menuStrip;
    Strip* strip;

    Slider** sliders;
    Button** buttons;
    int buttonCount;
    int sliderCount;
    Display* display;

    int* buttonPressTimeout;
    int* buttonReleaseTimeout;
    int* sliderTouchTimeout;
    int* sliderReleaseTimeout;
    int* sliderChangeTimeout;


    int* slidersLastTransmittedPosition;
    int* slidersLastTouchState;
    int* buttonsLastState;
    long lastScanTime;
    long timeSinceLastScan;
    long* lastbuttonPressTime;
    long* lastsliderTouchTime;
    long currentTime;
public:
    void update_device() {
        // the follow section sets up the timing
        //Serial.println("Current time");
        this->currentTime = millis();
        //Serial.println("Got current time");
        timeSinceLastScan = currentTime - lastScanTime;
        lastScanTime = currentTime;
        // the following section updates all components
        //Serial.println("Update components");
        updater->update_Components();
        menuSelectSlider->update_Device();
        for (int i = 0; i < sliderCount; i++) {
            sliders[i]->update_Device();
        }


        // In the following section, i will make a readout of all the states of all the buttons and sliders
        #ifdef DEBUG
        Serial.print("MS: ");
        Serial.print(menuSelectSlider->get_position());
        Serial.print("  MB: ");
        for (int i = 0; i < menuButtonCount; i++) {
            Serial.print(menuButtons[i]->get_state());
        }
        Serial.print("  S: ");
        for (int i = 0; i < sliderCount; i++) {
            Serial.print(sliders[i]->get_position());
        }
        Serial.print("  B: ");
        for (int i = 0; i < buttonCount; i++) {
            Serial.print(buttons[i]->get_state());
        }
        Serial.println();
        #endif
        // the following updates the list of menus that are active and changes system if new menus are active
        //Serial.println("Update active menu list");
        int previousAmountOfActiveMenus = amountOfActiveMenus;
        amountOfActiveMenus = 0;
        delete[] activeMenus;
        activeMenus = new Menu*[menuCount];
        for (int i = 0; i < menuCount; i++) {
            if (menus[i]->is_menuActive() == true) {
                activeMenus[i] = menus[i];
                amountOfActiveMenus++;
            }
        }
        //Serial.println("Check if amount of active menus has changed");
        if (previousAmountOfActiveMenus != amountOfActiveMenus) {
            Serial.print("Amount of active menus changed from ");
            Serial.print(previousAmountOfActiveMenus);
            Serial.print(" to ");
            Serial.println(amountOfActiveMenus);
            menuSelectSlider->set_numberOfNotches(amountOfActiveMenus);
        }
        // the following section checks if the menu select slider value has changed and changes the menus if it has
        //Serial.println("Check if menu slider has changed");
        if (menuSelectSlider->get_position() != currentMenuIndex && currentTime - lastMenuSwitchTime > MenuSwitchTimeout) {
            lastMenuSwitchTime = currentTime;
            try {
                activeMenus[currentMenuIndex]->on_MenuDeselected();
            } catch (const std::exception& e) {
                Serial.print("Error on Menu Deselect of activeMenu with ID: ");
                Serial.print(activeMenus[currentMenuIndex] -> get_id());
                Serial.print(" Error: ");
                Serial.println(e.what());
            }
            currentMenuIndex = menuSelectSlider->get_position();
            try {
                activeMenus[currentMenuIndex]->on_MenuSelected();
            } catch (const std::exception& e) {
                Serial.print("Error on Menu Select of activeMenu with ID: ");
                Serial.print(activeMenus[currentMenuIndex] -> get_id());
                Serial.print(" Error: ");
                Serial.println(e.what());
            }
            lastMenuSwitchTime = currentTime;
        }
        //Serial.println("Check if menu buttons have been pressed");
        // the following section checks if the menu buttons have been pressed
        for (int i = 0; i < menuButtonCount; i++) {
            if (menuButtons[i]->get_state() == true && menuButtonsLastState[i]== false && currentTime - lastMenuButtonPressTime[i] > menuButtonPressTimeout[i]) {
                    lastMenuButtonPressTime[i] = currentTime;
                    // RUN EVENT: MENU BUTTON PRESSED
                    Serial.print("Manager button pressed ");
                    Serial.println(i);
                    menuStrip->updateAll(255,255,255);
            }
        }
        // the following section checks if menu buttons have been released
        for (int i = 0; i < menuButtonCount; i++) {
            if (menuButtons[i]->get_state() == false && menuButtonsLastState[i] == true) {
                // RUN EVENT: MENU BUTTON RELEASED
                Serial.print("Manager button released ");
                Serial.println(i);
                menuStrip->updateAll(0,0,0);
            }
            menuButtonsLastState[i] = menuButtons[i]->get_state();
        }

        activeMenus[currentMenuIndex]->run_menu();
        // the following section checks if the sliders have been touched
        //Serial.println("Check if sliders have been touched");
        for (int i = 0; i < sliderCount; i++) {
            if (sliders[i]->isTouched() == true && slidersLastTouchState[i] == false && currentTime - lastsliderTouchTime[i] > sliderTouchTimeout[i]) {
                lastsliderTouchTime[i] = currentTime;
                // RUN EVENT: SLIDER TOUCHED
                try {
                    activeMenus[currentMenuIndex]->on_SliderTouch(i, sliders[i]);
                } catch (const std::exception& e) {
                    Serial.print("Error on Slider Touch of activeMenu with ID: ");
                    Serial.print(activeMenus[currentMenuIndex] -> get_id());
                    Serial.print(" Error: ");
                    Serial.println(e.what());
                }
            }
        }
        // the following section checks if the sliders have been released
        //Serial.println("Check if sliders have been released");
        for (int i = 0; i < sliderCount; i++) {
            if (sliders[i]->isTouched() == false && slidersLastTouchState[i] == true && currentTime - lastsliderTouchTime[i] > sliderReleaseTimeout[i]) {
                lastsliderTouchTime[i] = currentTime;
                try {
                    activeMenus[currentMenuIndex]->on_SliderRelease(i, sliders[i]);
                } catch (const std::exception& e) {
                    Serial.print("Error on Slider Release of activeMenu with ID: ");
                    Serial.print(activeMenus[currentMenuIndex] -> get_id());
                    Serial.print(" Error: ");
                    Serial.println(e.what());
                }
                // RUN EVENT: SLIDER RELEASED
            }
            slidersLastTouchState[i] = sliders[i]->isTouched();
        }
        // the following section checks if the sliders have been moved
        //Serial.println("Check if sliders have been moved");
        for (int i = 0; i < sliderCount; i++) {
            if (sliders[i]->isNoisy()) {
                if (abs(sliders[i]->get_position() - slidersLastTransmittedPosition[i]) > 2 && currentTime - lastsliderTouchTime[i] > sliderChangeTimeout[i]) {
                    slidersLastTransmittedPosition[i] = sliders[i]->get_position();
                    // RUN EVENT: SLIDER MOVED
                    try {
                        activeMenus[currentMenuIndex]->on_SliderChange(i, sliders[i]);
                    } catch (const std::exception& e) {
                        Serial.print("Error on Slider Change of activeMenu with ID: ");
                        Serial.print(activeMenus[currentMenuIndex] -> get_id());
                        Serial.print(" Error: ");
                        Serial.println(e.what());
                    }
                }
            }
            else {
                if (sliders[i]->get_position() != slidersLastTransmittedPosition[i] && currentTime - lastsliderTouchTime[i] > sliderChangeTimeout[i]) {
                slidersLastTransmittedPosition[i] = sliders[i]->get_position();
                // RUN EVENT: SLIDER MOVED
                try {
                        activeMenus[currentMenuIndex]->on_SliderChange(i, sliders[i]);
                    } catch (const std::exception& e) {
                        Serial.print("Error on Slider Change of activeMenu with ID: ");
                        Serial.print(activeMenus[currentMenuIndex] -> get_id());
                        Serial.print(" Error: ");
                        Serial.println(e.what());
                    }
                }
            }
        }
        // the following section checks if the buttons have been pressed
        //Serial.println("Check if buttons have been pressed");
        for (int i = 0; i < buttonCount; i++) {
            if (buttons[i]->get_state() == true && buttonsLastState[i] == false && currentTime - lastbuttonPressTime[i] > buttonPressTimeout[i]) {
                lastbuttonPressTime[i] = currentTime;
                // RUN EVENT: BUTTON PRESSED
                try {
                    activeMenus[currentMenuIndex]->on_ButtonPress(i, buttons[i]);
                } catch (const std::exception& e) {
                    Serial.print("Error on Button Press of activeMenu with ID: ");
                    Serial.print(activeMenus[currentMenuIndex] -> get_id());
                    Serial.print(" Error: ");
                    Serial.println(e.what());
                }
            }
        }
        // the following section checks if the buttons have been released
        //Serial.println("Check if buttons have been released");
        for (int i = 0; i < buttonCount; i++) {
            if (buttons[i]->get_state() == false && buttonsLastState[i] == true && currentTime - lastbuttonPressTime[i] > buttonReleaseTimeout[i]) {
                lastbuttonPressTime[i] = currentTime;
                // RUN EVENT: BUTTON RELEASED
                try {
                    activeMenus[currentMenuIndex]->on_ButtonRelease(i, buttons[i]);
                } catch (const std::exception& e) {
                    Serial.print("Error on Button Release of activeMenu with ID: ");
                    Serial.print(activeMenus[currentMenuIndex] -> get_id());
                    Serial.print(" Error: ");
                    Serial.println(e.what());
                }
            }
            buttonsLastState[i] = buttons[i]->get_state();
        }

        
    }
    void virtual run_drawFunction() final {
        display->clear();
        activeMenus[currentMenuIndex]->draw_menu();
        display->drawRect(0,0,52,240,converter->RGBto565(255,255,255));
        for (int i = 0; i < amountOfActiveMenus; i++) {
            try {
                display->drawBitmap(0, i*60, activeMenus[i]->get_menuIcon(), 52, 60);
            } catch (const std::exception& e) {
                Serial.print("Error on Bitmap draw of activeMenu with ID: ");
                Serial.print(activeMenus[i] -> get_id());
                Serial.print(" Error: ");
                Serial.println(e.what());
            // draw corresponding menu icon in sidebar
            }
        }
    }


public: // constructor
    Manager(SteppedSlider* menuSelectSlider, Button** menuButtons, int menuButtonCount, Updater* updater, Menu** menus, int menuCount, Slider** sliders,  int sliderCount, Button** buttons, int buttonCount, Strip* menuStrip, Strip* strip, Display* display) {
        this->menuSelectSlider = menuSelectSlider;
        this->menuButtons = menuButtons;
        this->menuButtonCount = menuButtonCount;
        this->updater = updater;
        this->converter = new Converter();
        this->currentMenuIndex = 1;
        this->menus = menus;
        this->menuCount = menuCount;
        this->MenuSwitchTimeout = 200;
        this->menuButtonsLastState = new int[menuButtonCount];
        this->lastMenuButtonPressTime = new long[menuButtonCount];
        this->menuButtonPressTimeout = new int[menuButtonCount];
        this->menuSlidersLastPosition = menuSelectSlider->get_position();
        this->lastMenuSwitchTime = 0;
        this->activeMenus = new Menu*[menuCount];
        this->amountOfActiveMenus = 0;
        this->sliders = sliders;
        this->buttons = buttons;
        this->buttonCount = buttonCount;
        this->sliderCount = sliderCount;
        this->display = display;
        this->menuStrip = menuStrip;
        this->strip = strip;
        this->buttonPressTimeout = new int[buttonCount];
        this->buttonReleaseTimeout = new int[buttonCount];
        this->sliderTouchTimeout = new int[sliderCount];
        this->sliderReleaseTimeout = new int[sliderCount];
        this->sliderChangeTimeout = new int[sliderCount];

        this->slidersLastTransmittedPosition = new int[sliderCount];
        this->slidersLastTouchState = new int[sliderCount];
        this->buttonsLastState = new int[buttonCount];
        this->lastScanTime = millis();
        this->timeSinceLastScan = 0;
        this->lastbuttonPressTime = new long[buttonCount];
        this->lastsliderTouchTime = new long[sliderCount];
        this->currentTime = millis();

        for (int i = 0; i < menuButtonCount; i++) {
            menuButtonsLastState[i] = false;
            lastMenuButtonPressTime[i] = 0;
            menuButtonPressTimeout[i] = 100;
        }
        for (int i = 0; i < buttonCount; i++) {
            buttonsLastState[i] = false;
            lastbuttonPressTime[i] = 0;
            buttonPressTimeout[i] = 100;
            buttonReleaseTimeout[i] = 100;
        }
        for (int i = 0; i < sliderCount; i++) {
            slidersLastTransmittedPosition[i] = sliders[i]->get_position();
            slidersLastTouchState[i] = sliders[i]->isTouched();
            lastsliderTouchTime[i] = 0;
            sliderTouchTimeout[i] = 100;
            sliderReleaseTimeout[i] = 100;
            sliderChangeTimeout[i] = 100;
        }
        for (int i = 0; i < menuCount; i++) {
            menus[i]->set_manager(this);
            menus[i]->on_setup();
        }
    }
public: // This section is for setting timeouts for the buttons and sliders
    void set_buttonPressTimeout(int buttonIndex, int timeout) {
        if (buttonIndex < buttonCount && buttonIndex >= 0) {
            buttonPressTimeout[buttonIndex] = timeout;
        } else {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void set_buttonReleaseTimeout(int buttonIndex, int timeout) {
        if (buttonIndex < buttonCount && buttonIndex >= 0) {
            buttonReleaseTimeout[buttonIndex] = timeout;
        } else {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void set_sliderChangeTimeout(int sliderIndex, int timeout) {
        if (sliderIndex < sliderCount && sliderIndex >= 0) {
            sliderChangeTimeout[sliderIndex] = timeout;
        } else {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void set_sliderTouchTimeout(int sliderIndex, int timeout) {
        if (sliderIndex < sliderCount && sliderIndex >= 0) {
            sliderTouchTimeout[sliderIndex] = timeout;
        } else {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void set_sliderReleaseTimeout(int sliderIndex, int timeout) {
        if (sliderIndex < sliderCount && sliderIndex >= 0) {
            sliderReleaseTimeout[sliderIndex] = timeout;
        } else {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
public: // This section is for getting infomation about the buttons and sliders
    long get_timeSinceButtonPress(int buttonIndex) {
    try {
        return millis() - lastbuttonPressTime[buttonIndex];
    } catch (...) {
        Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        return -1; // or any suitable default value indicating an error
    }
}
    long get_timeSinceSliderTouch(int sliderIndex) {
        try {
            return millis() - lastsliderTouchTime[sliderIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return -1; // or any suitable default value indicating an error
        }
    }
    bool get_buttonPress(int buttonIndex) {
        try {
            return buttons[buttonIndex]->get_state();
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return false; // or any suitable default value indicating an error
        }
    }
    int get_sliderPosition(int sliderIndex) {
        try {
            return sliders[sliderIndex]->get_position();
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return -1; // or any suitable default value indicating an error
        }
    }
    Slider* get_slider(int sliderIndex) {
        try {
            return sliders[sliderIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return nullptr; // or any suitable default value indicating an error
        }
    }
    Button* get_button(int buttonIndex) {
        try {
            return buttons[buttonIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return nullptr; // or any suitable default value indicating an error
        }
    }
    Strip* get_strip() {
        try {
            return strip;
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return nullptr; // or any suitable default value indicating an error
        }
    }
    int get_menuCount() {
        return menuCount;
    }
    int get_activeMenuCount() {
        return amountOfActiveMenus;
    }
    int get_currentMenuIndex() {
        return currentMenuIndex;
    }
    int get_lastTimeScanned() {
        return lastScanTime;
    }
    int get_timeSinceLastScan() {
        return timeSinceLastScan;
    }
    int get_lastButtonPressTime(int buttonIndex) {
        try {
            return lastbuttonPressTime[buttonIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return -1; // or any suitable default value indicating an error
        }
    }
    int get_lastSliderTouchTime(int sliderIndex) {
        try {
            return lastsliderTouchTime[sliderIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return -1; // or any suitable default value indicating an error
        }
    }
    int get_currentTime() {
        return currentTime;
    }
    int get_slidersLastTransmittedPosition(int sliderIndex) {
        try {
            return slidersLastTransmittedPosition[sliderIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return -1; // or any suitable default value indicating an error
        }
    }
    int get_slidersLastTouchState(int sliderIndex) {
        try {
            return slidersLastTouchState[sliderIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return -1; // or any suitable default value indicating an error
        }
    }
    int get_buttonsLastState(int buttonIndex) {
        try {
            return buttonsLastState[buttonIndex];
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
            return -1; // or any suitable default value indicating an error
        }
    }
    void convert_toLinearSlider(int sliderIndex) {
        try {
            sliders[sliderIndex] = Converter::convertToLinearSlider(sliders[sliderIndex]);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void convert_toSteppedSlider(int sliderIndex, int notches) {
        try {
            sliders[sliderIndex] = Converter::convertToSteppedSlider(sliders[sliderIndex], notches);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    } 
    void convert_toLitLinearSlider(int sliderIndex, Strip* stripptr) {
        try {
            sliders[sliderIndex] = Converter::convertToLitLinearSlider(sliders[sliderIndex], stripptr);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void convert_toLitSteppedSlider(int sliderIndex, int notches, Strip* stripptr) {
        try {
            sliders[sliderIndex] = Converter::convertToLitSteppedSlider(sliders[sliderIndex], notches, stripptr);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void convert_toButton(int buttonIndex) {
        try {
            buttons[buttonIndex] = Converter::convertToButton(buttons[buttonIndex]);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void convert_toLedButton(int buttonIndex, Strip* stripptr) {
        try {
            buttons[buttonIndex] = Converter::convertToLedButton(buttons[buttonIndex], stripptr);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void convert_toLedCD74HC165E_Button(int buttonIndex, Strip* stripptr) {
        try {
            buttons[buttonIndex] = Converter::convertToLedCD74HC165E_Button((CD74HC165E_Button*)buttons[buttonIndex], stripptr);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void convert_toCD74HC165E_Button(int buttonIndex) {
        try {
            buttons[buttonIndex] = Converter::convertToCD74HC165E_Button((LedCD74HC165E_Button*)buttons[buttonIndex]);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
    void convert_toButton(int buttonIndex, Strip* stripptr) {
        try {
            buttons[buttonIndex] = Converter::convertToButton(buttons[buttonIndex]);
        } catch (...) {
            Serial.println("ERROR: Action not possible: check indexes, likely out of range");
        }
    }
};