#pragma once
#include "MC14051_Potentiometer.h"
#include "motor.h"
#include "capacitivetouch.h"
#include "Arduino.h"

/**
 * @brief Abstract class dedicated to driving the SM1001NKa0x ha1 019 motorised linear potentiometer.
 * 
 * The `Slider` class provides a set of methods to control and interact with the motorised linear potentiometer.
 * It serves as a base class for implementing specific functionality for different potentiometer models.
 * 
 * @note This class is abstract and cannot be instantiated directly.
 */
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
                touch->update_nodeValue();
                if (touch->get_touchBool()) {
                    wasTouched = true;
                    Serial.println("Touch detected1, calibration interrupted");
                }

                if (wasTouched == false) {
                    motor->setSpeed(70);
                }
                for (int i = 0; i < 400; i++) {
                    touch->update_nodeValue();
                    if (touch->get_touchBool() || wasTouched == true) {
                        wasTouched = true;
                        Serial.println("Touch detected2, calibration interrupted");
                        motor->setSpeed(0);
                        break;
                    }
                    delay(1);
                } 
                if (wasTouched == false) {
                    pot->update_nodeValue();
                    calibrateHigh = pot->get_potValue();
                }

                if (wasTouched == false) {
                    motor->setSpeed(-70);
                }
                for (int i = 0; i < 400; i++) {
                    touch->update_nodeValue();
                    if (touch->get_touchBool() || wasTouched == true) {
                        wasTouched = true;
                        Serial.println("Touch detected3, calibration interrupted");
                        motor->setSpeed(0);
                        break;
                    }
                    delay(1);
                } 
                if (wasTouched == false) {
                    pot->update_nodeValue();
                    calibrateLow = pot->get_potValue();
                    motor->setSpeed(0);
                    break;
                }
                Serial.println("Calibration was interrupted");
                delay(50);
            }
                
        }
        
        bool isTouched() {
            return touch->get_touchBool();
        }

        Motor* get_motor() {
            return motor;
        }

        Capacitivetouch* get_touch() {
            return touch;
        }

        Potentiometer* get_pot() {
            return pot;
        }
        
        virtual void set_speedToTarget(int value) {
            Serial.println("ERROR: This function is not implemented for this class");
        }
        virtual void set_goal(int goal) {
            Serial.println("ERROR: This function is not implemented for this class");
        }
        virtual void remove_goal() {
            Serial.println("ERROR: This function is not implemented for this class");
        }
        virtual void set_strength(int strength) {
            Serial.println("ERROR: This function is not implemented for this class");
        }
        virtual void set_numberOfNotches(int notches) {
            Serial.println("ERROR: This function is not implemented for this class");
        }
        virtual int getNumberOfNotches() {
            Serial.println("ERROR: This function is not implemented for this class");
            return 0;
        }
        virtual bool isNoisy() {
            return 0;
        }
};