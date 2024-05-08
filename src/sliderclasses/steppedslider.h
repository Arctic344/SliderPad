#pragma once
#include "../slider.h"

class SteppedSlider: public Slider{
    private: 
        int numberOfNotches;
    public:
        SteppedSlider(Motor* motor, Potentiometer* pot, Capacitivetouch* touch, int notches) {
            this->motor = motor;
            this->pot = pot;
            this->touch = touch;
            this->numberOfNotches = notches;
        }

        void update_Device() override {
            Serial.print("pos:");
            Serial.print(pot->get_potValue());
            Serial.print("  notch:");
            Serial.print(nearestNotch(pot->get_potValue()));
            Serial.print("  distance:");
            Serial.println(distanceToNearestNotch(pot->get_potValue()));
            if (abs(distanceToNearestNotch(pot->get_potValue() > 3))) {
                motor->setSpeed(distanceToNearestNotch(pot->get_potValue()));
                
            }
            else {
                motor->setSpeed(0);
            }

        }

        int getNumberOfNotches() const {
            return numberOfNotches;
        }

        void setNumberOfNotches(int notches) {
            numberOfNotches = notches;
        }
        int get_position() override {  
            return nearestNotch(pot->get_potValue());
        }
    private:
        int distanceToNearestNotch(int position) {
            int interval = 100/(numberOfNotches-1);
            int distance = 100;
            for (int i = 0; i <= 100; i+= interval) {
                if (abs(position-i) < abs(distance)) {
                    distance = position-i;
                }
                
            }
            return distance;
        }
        int nearestNotch(int position) {
            int interval = 100/(numberOfNotches-1);
            int distance = 100;
            int notch = 0;
            for (int i = 0; i <= 100; i+= interval) {
                if (abs(position-i) < abs(distance)) {
                    distance = position-i;
                    notch = i/interval;
                }
                
            }
            return notch;
        }
};