#pragma once
#include "../Slider.h"

/**
         * @brief A slider that always tries to go to the center with force.
         * 
         * The CenteredSlider class is a subclass of the Slider class. It represents a slider that is designed to always try to go to the center position with force.
         * The return value of the slider is the offset it has from the center position.
         * 
         * @param motor A pointer to the Motor object used by the slider.
         * @param pot A pointer to the Potentiometer object used by the slider.
         * @param touch A pointer to the Capacitivetouch object used by the slider.
         */
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
