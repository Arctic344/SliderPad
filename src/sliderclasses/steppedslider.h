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
        int notch_to_pos(int notchNo) {
            if (notchNo < 1) {
                return 50;
            }
            int returnValue = (notchNo * 100) / (this->numberOfNotches-1);
            if (returnValue > 100) {
                Serial.println("Error in notch amount. requested notch above current notches avaliable");
                return 0;
            }
            return returnValue;
        }
        int distanceToNearestNotch(int position) {
            int distance = 100;
            for (int i = 0; i < numberOfNotches; i++) {
                if (abs(position - notch_to_pos(i)) < abs(distance)) {
                    distance = position - notch_to_pos(i);
                }
            }
            return distance;
        }
        int nearestNotch(int position) {
            int distance = 100;
            int notch = 0;
            for (int i = 0; i < numberOfNotches; i++) {
                if (abs(position - notch_to_pos(i)) < abs(distance)) {
                    distance = position - notch_to_pos(i);
                    notch = i;
                }
            }
            return notch;
        }
};