#pragma once
#include <Arduino.h>
#include <Slider.h>
#include <Button.h>
#include <Updater.h>
#include <Display.h>
#include <Menu.h>
#include <sliderclasses/steppedslider.h>
#include "Converter.h"

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


    int* slidersLastPosition;
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

        // In the following section, i will make a readout of all the states of all the buttons and sliders

        // Serial.print("MS: ");
        // Serial.print(menuSelectSlider->get_position());
        // Serial.print("  MB: ");
        // for (int i = 0; i < menuButtonCount; i++) {
        //     Serial.print(menuButtons[i]->get_state());
        // }
        // Serial.print("  S: ");
        // for (int i = 0; i < sliderCount; i++) {
        //     Serial.print(sliders[i]->get_position());
        // }
        // Serial.print("  B: ");
        // for (int i = 0; i < buttonCount; i++) {
        //     Serial.print(buttons[i]->get_state());
        // }
        // Serial.println();

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
            activeMenus[currentMenuIndex]->on_MenuDeselected();
            currentMenuIndex = menuSelectSlider->get_position();
            activeMenus[currentMenuIndex]->on_MenuSelected();
            lastMenuSwitchTime = currentTime;
        }
        //Serial.println("Check if menu buttons have been pressed");
        // the following section checks if the menu buttons have been pressed
        for (int i = 0; i < menuButtonCount; i++) {
            if (menuButtons[i]->get_state() == true && menuButtonsLastState[i]== false && currentTime - lastMenuButtonPressTime[i] > menuButtonPressTimeout[i]) {
                    lastMenuButtonPressTime[i] = currentTime;
                    // RUN EVENT: MENU BUTTON PRESSED
                    Serial.print("Menu button pressed ");
                    Serial.println(i);
            }
            menuButtonsLastState[i] = menuButtons[i]->get_state();
        }
        // the following section checks if the sliders have been touched
        //Serial.println("Check if sliders have been touched");
        for (int i = 0; i < sliderCount; i++) {
            if (sliders[i]->isTouched() == true && slidersLastTouchState[i] == false && currentTime - lastsliderTouchTime[i] > sliderTouchTimeout[i]) {
                lastsliderTouchTime[i] = currentTime;
                // RUN EVENT: SLIDER TOUCHED
                Serial.print("Slider touched ");
                Serial.println(i);
            }
            slidersLastTouchState[i] = sliders[i]->isTouched();
        }
        // the following section checks if the sliders have been released
        //Serial.println("Check if sliders have been released");
        for (int i = 0; i < sliderCount; i++) {
            if (sliders[i]->isTouched() == false && slidersLastTouchState[i] == true && currentTime - lastsliderTouchTime[i] > sliderReleaseTimeout[i]) {
                lastsliderTouchTime[i] = currentTime;
                // RUN EVENT: SLIDER RELEASED
                Serial.print("Slider released ");
                Serial.println(i);
            }
            slidersLastTouchState[i] = sliders[i]->isTouched();
        }
        // the following section checks if the sliders have been moved
        //Serial.println("Check if sliders have been moved");
        for (int i = 0; i < sliderCount; i++) {
            if (sliders[i]->get_position() != slidersLastPosition[i] && currentTime - lastsliderTouchTime[i] > sliderChangeTimeout[i]) {
                slidersLastPosition[i] = sliders[i]->get_position();
                // RUN EVENT: SLIDER MOVED
                Serial.print("Slider moved ");
                Serial.println(i);
            }
        }
        // the following section checks if the buttons have been pressed
        //Serial.println("Check if buttons have been pressed");
        for (int i = 0; i < buttonCount; i++) {
            if (buttons[i]->get_state() == true && buttonsLastState[i] == false && currentTime - lastbuttonPressTime[i] > buttonPressTimeout[i]) {
                lastbuttonPressTime[i] = currentTime;
                // RUN EVENT: BUTTON PRESSED
                Serial.print("Button pressed ");
                Serial.println(i);
            }
        }
        // the following section checks if the buttons have been released
        //Serial.println("Check if buttons have been released");
        for (int i = 0; i < buttonCount; i++) {
            if (buttons[i]->get_state() == false && buttonsLastState[i] == true && currentTime - lastbuttonPressTime[i] > buttonReleaseTimeout[i]) {
                lastbuttonPressTime[i] = currentTime;
                // RUN EVENT: BUTTON RELEASED
                Serial.print("Button released ");
                Serial.println(i);
            }
            buttonsLastState[i] = buttons[i]->get_state();
        }

        
    }
    void virtual run_drawFunction() final {
        display->clear();
        activeMenus[currentMenuIndex]->draw_menu();
        display->drawRect(0,0,52,240,converter->RGBto565(255,255,255));
        for (int i = 0; i < amountOfActiveMenus; i++) {
            // draw corresponding menu icon in sidebar
        }
    }


public: // constructor
    Manager(SteppedSlider* menuSelectSlider, Button** menuButtons, int menuButtonCount, Updater* updater, Menu** menus, int menuCount, Slider** sliders, Button** buttons, int sliderCount, int buttonCount, Display* display) {
        this->menuSelectSlider = menuSelectSlider;
        this->menuButtons = menuButtons;
        this->menuButtonCount = menuButtonCount;
        this->updater = updater;
        this->converter = new Converter();
        this->currentMenuIndex = 0;
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
        this->buttonPressTimeout = new int[buttonCount];
        this->buttonReleaseTimeout = new int[buttonCount];
        this->sliderTouchTimeout = new int[sliderCount];
        this->sliderReleaseTimeout = new int[sliderCount];
        this->sliderChangeTimeout = new int[sliderCount];

        this->slidersLastPosition = new int[sliderCount];
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
            slidersLastPosition[i] = sliders[i]->get_position();
            slidersLastTouchState[i] = sliders[i]->isTouched();
            lastsliderTouchTime[i] = 0;
            sliderTouchTimeout[i] = 100;
            sliderReleaseTimeout[i] = 100;
            sliderChangeTimeout[i] = 100;
        }
    }
public: // This section is for setting timeouts for the buttons and sliders
    void set_buttonPressTimeout(int buttonIndex, int timeout) {
        buttonPressTimeout[buttonIndex] = timeout;
    }
    void set_buttonReleaseTimeout(int buttonIndex, int timeout) {
        buttonReleaseTimeout[buttonIndex] = timeout;
    }
    void set_sliderChangeTimeout(int sliderIndex, int timeout) {
        sliderChangeTimeout[sliderIndex] = timeout;
    }
    void set_sliderTouchTimeout(int sliderIndex, int timeout) {
        sliderTouchTimeout[sliderIndex] = timeout;
    }
    void set_sliderReleaseTimeout(int sliderIndex, int timeout) {
        sliderReleaseTimeout[sliderIndex] = timeout;
    }
public: // This section is for getting infomation about the buttons and sliders
    long get_timeSinceButtonPress(int buttonIndex) {
        return millis() - lastbuttonPressTime[buttonIndex];
    }
    long get_timeSinceSliderTouch(int sliderIndex) {
        return millis() - lastsliderTouchTime[sliderIndex];
    }
    bool get_buttonPress(int buttonIndex) {
        return buttons[buttonIndex]->get_state();
    }
    int get_sliderPosition(int sliderIndex) {
        return sliders[sliderIndex]->get_position();
    }


};