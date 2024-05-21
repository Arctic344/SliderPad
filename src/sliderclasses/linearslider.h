#pragma once
#include "../Slider.h"

class LinearSlider: public Slider{
    protected:
        int speedToTarget;
        int goal;
    public:
        LinearSlider(Motor* motor, Potentiometer* pot, Capacitivetouch* touch) {
            this->motor = motor;
            this->pot = pot;
            this->touch = touch;
            speedToTarget = 30;
            goal = -100;
        }

        void update_Device() override {
            if (goal == -100 || touch->get_touchBool()) {
                goal = -100;
                motor->setSpeed(0);
                return;
            }
            if (abs(get_position() - goal) < 3) {
                motor->setSpeed(0);
                goal = -100;
            } else if (get_position() - goal > 0) {
                motor->setSpeed(speedToTarget);
            } else {
                motor->setSpeed(speedToTarget*-1);
            }
        }

        int get_position() override {
            return pot->get_potValue();
        }

        void set_speedToTarget(int value) override {
            speedToTarget = 30+value;
        }

        void set_goal(int value)  override{
            if (value >= 0 && value <= 100) {
                goal = value;
            } else {
                // Handle invalid goal value here (e.g. throw an exception or set a default value)
            }
        }
        void remove_goal() override {
            goal = -100;
        }
        bool isNoisy() override {
            return 1;
        }
};
