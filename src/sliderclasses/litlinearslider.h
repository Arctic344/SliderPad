#pragma once
#include "../Slider.h"
#include "linearslider.h"
#include "../Strip.h"

class LitLinearSlider: public LinearSlider{
    private:
        Strip* strip;
    public:
        LitLinearSlider(Motor* motor, Potentiometer* pot, Capacitivetouch* touch, Strip* strip) : LinearSlider(motor, pot, touch){
            this->strip = strip;
        }

        void update_Device() override {
            if (goal == -100 || touch->get_touchBool()) {
                goal = -100;
                motor->setSpeed(0);
                strip->updatePercentage(get_position(),0,255,0);
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
            strip->updatePercentage(get_position(),255,0,0);
        }
};
