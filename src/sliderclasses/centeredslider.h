#pragma once
#include "../Slider.h"

class CenteredSlider: public Slider{
    private:
        int speedToTarget;
    public:
        CenteredSlider(Motor* motor, Potentiometer* pot, Capacitivetouch* touch) {
            this->motor = motor;
            this->pot = pot;
            this->touch = touch;
            speedToTarget = 30;
        }

        void update_Device() override {
            if (abs(pot->get_potValue() - 50) < 3) {
                motor->setSpeed(0);
            } else if (pot->get_potValue() - 50 > 0) {
                motor->setSpeed(speedToTarget+0.1*abs(pot->get_potValue() - 50));
            } else {
                motor->setSpeed((speedToTarget+0.1*abs(pot->get_potValue() - 50))*-1);
            }
        }
        int get_position() override {
            return 50-pot->get_potValue();
        }

        void set_speedToTarget(int value) override {
            speedToTarget = 30+value;
        }
};
