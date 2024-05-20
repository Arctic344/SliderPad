#include <Arduino.h>
#include <Slider.h>
#include <Button.h>
#include <Updater.h>
#include <Display.h>
#include <Menu.h>

class Manager {
private:
    Slider* menuSelectSlider;
    Button** menuButtons;
    int menuButtonCount;
    Updater* updater;
    int currentMenuIndex;
    Menu** menus;
    int menuCount;
    int MenuSwitchTimeout;
    int* menuButtonsLastState;
    long* lastMenuButtonPressTime;
    int menuSlidersLastPosition;
    long lastMenuSwitchTime;

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
    int* slidersLastTouchState;
    int* buttonsLastState;
    long lastScanTime;
    long timeSinceLastScan;
    long* lastbuttonPressTime;
    long* lastsliderTouchTime;
    long currentTime;
public:
    void virtual update_device() final {
        currentTime = millis();
        timeSinceLastScan = currentTime - lastScanTime;
        lastScanTime = currentTime;
        updater->update_Components();
        if (menuSelectSlider->get_position() != currentMenuIndex && currentTime - lastMenuSwitchTime > MenuSwitchTimeout) {
            lastMenuSwitchTime = currentTime;
            switchMenus();
        }
        for (int i = 0; i < menuButtonCount; i++) {
            if (menuButtons[i]->get_state() != menuButtonsLastState[i]) {
                if (menuButtons[i]->get_state() == true) {
                    lastMenuButtonPressTime[i] = currentTime;
                    // RUN EVENT: MENU BUTTON PRESSED
                }
                menuButtonsLastState[i] = menuButtons[i]->get_state();
            }
        }
    }
    void switchMenus() {
        if (millis() - lastMenuSwitchTime > MenuSwitchTimeout) {
            currentMenuIndex = menuSelectSlider->get_position();
            menus[currentMenuIndex]->draw_menu();
        }
    }
public: // constructor
    Manager(Slider* menuSelectSlider, Button** menuButtons, int menuButtonCount, Updater* updater, Menu** menus, int menuCount) {
        this->menuSelectSlider = menuSelectSlider;
        this->menuButtons = menuButtons;
        this->menuButtonCount = menuButtonCount;
        this->updater = updater;
        this->currentMenuIndex = 0;
        this->menus = menus;
        this->menuCount = menuCount;
        this->MenuSwitchTimeout = 100;
        buttonPressTimeout = new int[buttonCount];
        buttonHoldTimein = new int[buttonCount];
        buttonReleaseTimeout = new int[buttonCount];
        for (int i = 0; i < menuButtonCount; i++) {
            buttonPressTimeout[i] = 100;
            buttonHoldTimein[i] = 1000;
            buttonReleaseTimeout[i] = 100;
        }
        sliderChangeTimeout = new int[sliderCount];
        sliderTouchTimeout = new int[sliderCount];
        sliderReleaseTimeout = new int[sliderCount];


        slidersLastPosition = new int[sliderCount];
        buttonsLastState = new int[buttonCount];
        lastbuttonPressTime = new long[buttonCount];
        lastsliderTouchTime = new long[sliderCount];
        for (int i = 0; i < sliderCount; i++) {
            sliderChangeTimeout[i] = 1000;
            sliderTouchTimeout[i] = 200;
            sliderReleaseTimeout[i] = 200;
        }
        menuButtonsLastState = new int[menuButtonCount];
        lastMenuButtonPressTime = new long[menuButtonCount];
        slidersLastTouchState = new int[sliderCount];
        lastMenuSwitchTime = 0;
        lastScanTime = 0;
        timeSinceLastScan = 0;
    }
public: // This section is for setting timeouts for the buttons and sliders
    int set_buttonPressTimeout(int buttonIndex, int timeout) {
        buttonPressTimeout[buttonIndex] = timeout;
    }
    int set_buttonHoldTimein(int buttonIndex, int timeout) {
        buttonHoldTimein[buttonIndex] = timeout;
    }
    int set_buttonReleaseTimeout(int buttonIndex, int timeout) {
        buttonReleaseTimeout[buttonIndex] = timeout;
    }
    int set_sliderChangeTimeout(int sliderIndex, int timeout) {
        sliderChangeTimeout[sliderIndex] = timeout;
    }
    int set_sliderTouchTimeout(int sliderIndex, int timeout) {
        sliderTouchTimeout[sliderIndex] = timeout;
    }
    int set_sliderReleaseTimeout(int sliderIndex, int timeout) {
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