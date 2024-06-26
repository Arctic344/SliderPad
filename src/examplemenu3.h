#pragma once
#include "Menu.h"
#include "AdafruitIO_WiFi.h"
#include "Secrets.h"
#include <Arduino.h>
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *SliderPadTestValue = io.feed("SliderPadTestValue");

class Example3 : public Menu {
    private:
    public:
    Example3() : Menu(1) {
    }
    public:
    void on_setup() override{
        Serial.println("Example 3 setup");
        Serial.print("Connecting to Adafruit IO");
        io.connect();
        while (io.status() < AIO_CONNECTED) {
            Serial.print(".");
            delay(500);
        }
        Serial.println("Connected");
        delay(10000);
    }


    bool is_menuActive() override{
        return (io.status() < AIO_CONNECTED);
    }
    void on_ButtonPress(int buttonIndex, Button* button) override{
        io.run();
        SliderPadTestValue->save(manager->get_slider(0)->get_position());
    }
    void run_menu() override{
        io.run();
    }
    void on_MenuSelected() override{
        manager->convert_toLinearSlider(0);
        manager->get_slider(0)->set_goal(0);
        manager->get_strip()->updateAll(0, 0, 0);
        manager->set_buttonReleaseTimeout(0,0);
        manager->set_buttonReleaseTimeout(1,0);
        manager->set_buttonReleaseTimeout(2,0);
        manager->set_sliderChangeTimeout(0, 1000);
    }

};