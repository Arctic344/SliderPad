#pragma once
#include "Menu.h"
#include "AdafruitIO_WiFi.h"


class Example3 : public Menu {
    private:
        AdafruitIO_WiFi io;
        AdafruitIO_Feed *SliderPadTestValue;
    public:
    Example3() : Menu(1), io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS) {
    }
    public:
    void on_setup() override{
        AdafruitIO_Feed *SliderPadTestValue = io.feed("SliderPadTestValue");
        Serial.println("Example 3 setup");
        Serial.print("Connecting to Adafruit IO");
        io.connect();
        while (io.status() < AIO_CONNECTED) {
            Serial.print(".");
            delay(500);
        }
    }


    bool is_menuActive() override{
        return (io.status() < AIO_CONNECTED);
    }
    void on_ButtonPress(int buttonIndex, Button* button) override{
        io.run();
        SliderPadTestValue->save(1);
    }
    void run_menu() override{
        io.run();
    }

};