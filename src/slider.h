#pragma once
#include "MC14051_Potentiometer.h"
#include "motor.h"
#include "capacitivetouch.h"
#include "Arduino.h"

class Slider { // Class dedicated to driving the SM10001NKA0X-HA1-019 Motorised Linear Potentiometer
    protected:
        Potentiometer* pot;
        Motor* motor;
        Capacitivetouch* touch;
        int16_t calibrateLow;
        int16_t calibrateHigh;
    
    public:
        virtual void update_Device();

        virtual int get_position();

        int get_rawPosition() {
            return pot->get_potValue();
        }
        
        void calibrate() {
            while (true) {
                bool wasTouched = false;

                touch->updateTouchValue();
                if (touch->get_touchBool()) {
                    wasTouched = true;
                }

                if (wasTouched = false) {
                    motor->setSpeed(70);
                }
                for (int i = 0; i < 400; i++) {
                    touch->updateTouchValue();
                    if (touch->get_touchBool()) {
                        wasTouched = true;
                        motor->setSpeed(0);
                    }
                    delay(1);
                } 
                if (wasTouched = false) {
                    pot->update_PotValue();
                    calibrateHigh = pot->get_potValue();
                }

                if (wasTouched = false) {
                    motor->setSpeed(-70);
                }
                for (int i = 0; i < 400; i++) {
                    touch->updateTouchValue();
                    if (touch->get_touchBool()) {
                        wasTouched = true;
                        motor->setSpeed(0);
                    }
                    delay(1);
                } 
                if (wasTouched = false) {
                    pot->update_PotValue();
                    calibrateLow = pot->get_potValue();
                    break;
                }
                delay(50);
            }
                
        }
        
        bool isTouched() {
            return touch->get_touchBool();
        }
};