#pragma once

#include <iostream>
#include "Adafruit_PWMServoDriver.h"

class Motor {
    private:
        Adafruit_PWMServoDriver* associatedDevice; // the PWMServoDriver device which has the motor attached
        int MotorID; // the position in which the motor is connected, it goes clockwise from 0 to 3, starting in the top left corner near the adress selector panel
        int speed; // the speed the motor is currently at, always between -4096 and 4096


        void convertToAction() {
            int enablepin;
            int inA;
            int inB;
            switch (this->MotorID) {
                case 0:
                    int enablepin = 0; 
                    int inA = 1;
                    int inB = 2;
                case 1:
                    int enablepin = 5; 
                    int inA = 4;
                    int inB = 3;
                case 2:
                    int enablepin = 8; 
                    int inA = 9;
                    int inB = 10;
                case 3:
                    int enablepin = 13; 
                    int inA = 12;
                    int inB = 11;
                default:
                    Serial.println("Invalid Convert");
                    return;
            }
            if (this->speed == 0) {
                this->associatedDevice->setPin(enablepin,4095);
                this->associatedDevice->setPin(inA,0);
                this->associatedDevice->setPin(inB,0);
            }
            else if (this->speed > 0) {
                this->associatedDevice->setPin(enablepin,this->speed);
                this->associatedDevice->setPin(inA,4095);
                this->associatedDevice->setPin(inB,0);
            }
            else if (this->speed < 0) {
                this->associatedDevice->setPin(enablepin,abs(this->speed));
                this->associatedDevice->setPin(inA,0);
                this->associatedDevice->setPin(inB,4095);
            }
            
        }


    public:
        Motor(Adafruit_PWMServoDriver* PCA9685Ptr, int MotorID) { // Constructor for the Motor
            this->MotorID = MotorID;
            if (MotorID > 3 || MotorID < 0) {
                Serial.println("Invalid MotorID");
                this->MotorID = 4;
            }
            this->associatedDevice = PCA9685Ptr;
            return; 
        }
        Motor() {
            this->MotorID = 0;
            this->associatedDevice == nullptr;
            this->speed = 0;
        }

        void setSpeed(int speed) { // public set speed method
            if (speed > 4095 || speed < -4096) {
                Serial.println("Not a valid speed");
                return;
            }
            this->speed = speed;
            convertToAction();
        }
        

};