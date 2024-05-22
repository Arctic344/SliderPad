#pragma once
#include "../slider.h"

/**
 * @brief A slider that has notches, hence it is only happy being in 0-n positions.
 * The amount of positions can be set.
 */
class SteppedSlider: public Slider{
    protected: 
        int numberOfNotches;
        int strength;
        int speedToTarget;
        int goal;
    public:
        SteppedSlider(Motor* motor, Potentiometer* pot, Capacitivetouch* touch, int notches) {
            this->motor = motor;
            this->pot = pot;
            this->touch = touch;
            this->numberOfNotches = notches;
            this->strength = 19;
            this->speedToTarget = 30;
            this->goal = -100;
        }

        void update_Device() override {
            #ifdef DEBUG
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
            #endif
            if (touch->get_touchBool()){
                goal = -100;
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
                #ifdef DEBUG
                Serial.println("1notch");
                #endif
            }
            else if (goal == -100) {
                if (abs(distanceToNearestNotch(pot->get_potValue())) < 3) {
                    motor->setSpeed(0);
                    #ifdef DEBUG
                    Serial.println("0");
                    #endif
                }
                else if (touch->get_touchBool()) {
                    motor->setSpeed(touchedTransferFunction());
                    #ifdef DEBUG
                    Serial.println(touchedTransferFunction());
                    #endif
                }
                else {
                    motor->setSpeed(untouchedTransferFunction());
                    #ifdef DEBUG
                    Serial.println(untouchedTransferFunction());
                    #endif
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
                #ifdef DEBUG
                Serial.println("goal decision");
                #endif
            }
            

        }

        int getNumberOfNotches() const {
            return numberOfNotches;
        }
        void set_strength(int strength) override {
            this->strength = 15.88+strength;
        }
        void set_speedToTarget(int speed) override {
            this->speedToTarget = 30+speed;
        }
        /**
         * Sets the number of notches for the stepped slider.
         * 
         * @param notches The number of notches to set. Must be greater than 0 and less than or equal to 10.
         *                Note: It is recommended to keep the number of notches below 10 for optimal performance.
         */
        void set_numberOfNotches(int notches) override {
            if (notches < 1) {
                return;
            }
            if (notches > 10) {
                return; 
            }
            if (notches == 1) {
                goal = -100;
                numberOfNotches = 1;
                return;
            }
            int interval = 100/(notches-1);
            goal = (nearestNotch(pot->get_potValue())*interval);
            if (this->goal > 100) {
                goal = 100;
            }
            #ifdef DEBUG
            Serial.print("set goal to:");
            Serial.println(nearestNotch(pot->get_potValue())*interval);
            #endif
            numberOfNotches = notches;
            #ifdef DEBUG
            Serial.print("Set notches to:");
            Serial.println(numberOfNotches);
            #endif
        }
        int get_position() override {  
            if (goal == -100) {
                return nearestNotch(pot->get_potValue());
            }
            return nearestNotch(goal);
        }
        void set_goal(int goal) override {
            if (goal > numberOfNotches) {
                return;
            }
            int interval = 100/(numberOfNotches-1);
            this->goal = interval*goal;
        }
        void remove_goal() override {
            this->goal = -100;
        }
    protected:
        
        int distanceToNearestNotch(int position) {
            if (numberOfNotches == 1) {
                return 50-position;
            }
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
            if (numberOfNotches == 1) {
                return 0;
            }
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
        int touchedTransferFunction() {
            if (this->distanceToNearestNotch(pot->get_potValue()) > 0) {
                return round(0.165f * this->getNumberOfNotches()*this->distanceToNearestNotch(pot->get_potValue()) + this->strength);
            } 
            else {
                return round(-1 * (abs(0.165f * this->getNumberOfNotches()* this->distanceToNearestNotch(pot->get_potValue())) + this->strength));
            }
        }
        int untouchedTransferFunction() {
             if (this->distanceToNearestNotch(pot->get_potValue()) > 0) {
                return this->speedToTarget;
            } 
            else {
                return this->speedToTarget*-1;
            }
        }
};