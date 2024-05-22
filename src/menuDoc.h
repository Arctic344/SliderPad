#pragma once
class Slider;
class Button;
#include <Arduino.h>   
class Manager;
#include <stdint.h>
class Strip;


class Menu {
    private:
        int id;
    protected:
        Manager* manager;
    public:
        Menu(int id);
        virtual void on_setup();
        virtual void run_menu();
        virtual void draw_menu();
        virtual bool is_menuActive();
        virtual void menu_background_action();
        virtual uint8_t* get_menuIcon();

        virtual void on_SliderChange(int sliderIndex, Slider* slider);
        virtual void on_SliderRelease(int sliderIndex, Slider* slider);
        virtual void on_SliderTouch(int sliderIndex, Slider* slider);
        virtual void on_ButtonPress(int buttonIndex, Button* button);
        virtual void on_ButtonRelease(int buttonIndex, Button* button);
        virtual void on_ButtonHold(int buttonIndex, Button* button);
        virtual void on_MenuSelected();
        virtual void on_MenuDeselected();

        virtual int get_id() final;
        virtual void set_manager(Manager* manager) final;
};

//List of All Functions

// This document lists all the functions available in the class, categorized by their purpose.
// Timeout Setting Functions

    void set_buttonPressTimeout(int buttonIndex, int timeout);
    void set_buttonReleaseTimeout(int buttonIndex, int timeout);
    void set_sliderChangeTimeout(int sliderIndex, int timeout);
    void set_sliderTouchTimeout(int sliderIndex, int timeout);
    void set_sliderReleaseTimeout(int sliderIndex, int timeout);

// Information Retrieval Functions for Buttons and Sliders

    long get_timeSinceButtonPress(int buttonIndex);
    long get_timeSinceSliderTouch(int sliderIndex);
    bool get_buttonPress(int buttonIndex);
    int get_sliderPosition(int sliderIndex);
    Slider* get_slider(int sliderIndex);
    Button* get_button(int buttonIndex);
    Strip* get_strip();

// Menu and System Information Functions

    int get_menuCount();
    int get_activeMenuCount();
    int get_currentMenuIndex();
    int get_lastTimeScanned();
    int get_timeSinceLastScan();
    int get_lastButtonPressTime(int buttonIndex);
    int get_lastSliderTouchTime(int sliderIndex);
    int get_currentTime();
    int get_slidersLastTransmittedPosition(int sliderIndex);
    int get_slidersLastTouchState(int sliderIndex);
    int get_buttonsLastState(int buttonIndex);

// Conversion Functions

    void convert_toLinearSlider(int sliderIndex)
    void convert_toSteppedSlider(int sliderIndex, int notches)
    void convert_toLitLinearSlider(int sliderIndex, Strip* stripptr)
    void convert_toLitSteppedSlider(int sliderIndex, int notches, Strip* stripptr)
    void convert_toButton(int buttonIndex)
    void convert_toLedButton(int buttonIndex, Strip* stripptr)
    void convert_toLedCD74HC165E_Button(int buttonIndex, Strip* stripptr)
    void convert_toCD74HC165E_Button(int buttonIndex)
    void convert_toButton(int buttonIndex, Strip* stripptr)