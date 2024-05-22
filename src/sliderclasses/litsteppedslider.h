#pragma once
#include "steppedslider.h"
#include "../Strip.h"

class LitSteppedSlider: public SteppedSlider{
    private: 
        Strip* ledstrip;
    public:
        LitSteppedSlider(Motor* motor, Potentiometer* pot, Capacitivetouch* touch, int notches, Strip* ledstrip) : SteppedSlider(motor, pot, touch, notches) {
            this->ledstrip = ledstrip;
        }

        void update_Device() override {
            Serial.print("notch no:");
            Serial.print(numberOfNotches);
            Serial.print("   -pos:");
            Serial.print(pot->get_potValue());
            Serial.print("  notch:");
            Serial.print(nearestNotch(pot->get_potValue()));
            Serial.print("  distance:");
            Serial.print(distanceToNearestNotch(pot->get_potValue()));
            Serial.print("  goal:");
            Serial.print(goal);
            Serial.print("   force:");
            if (touch->get_touchBool()){
                goal = -100;
                ledstrip->updatePercentage(pot->get_potValue(),0,255,0);
            } else {
                ledstrip->updatePercentage(pot->get_potValue(),255,0,0);
            }
            if (numberOfNotches == 1) {
                goal = -100;
                if (abs(50-pot->get_potValue()) > 3) {
                    if (pot->get_potValue() > 50) {
                        motor->setSpeed(speedToTarget);
                    } else {
                        motor->setSpeed(speedToTarget*-1);
                    }
                } else {
                    motor->setSpeed(0);
                
                }
                Serial.println("1notch");
            }
            else if (goal == -100) {
                if (abs(distanceToNearestNotch(pot->get_potValue())) < 3) {
                    motor->setSpeed(0);
                    Serial.println("0");
                }
                else if (touch->get_touchBool()) {
                    motor->setSpeed(touchedTransferFunction());
                    Serial.println(touchedTransferFunction());
                }
                else {
                    motor->setSpeed(untouchedTransferFunction());
                    Serial.println(untouchedTransferFunction());
                }
            }
            else {
                if (abs(goal-pot->get_potValue()) < 3) {
                    remove_goal();
                } else {
                    if (goal-pot->get_potValue() > 0) {
                        motor->setSpeed(speedToTarget*-1);
                    } else {
                        motor->setSpeed(speedToTarget);
                    }
                }
                Serial.println("goal decision");
            }
            

        }

};