#pragma once
#include "Adafruit_PWMServoDriver.h"

class Motor {
    private:
        Adafruit_PWMServoDriver* associatedDevice; // the PWMServoDriver device which has the motor attached
        int MotorID; // the position in which the motor is connected, it goes clockwise from 0 to 3, starting in the top left corner near the adress selector panel
        int speed; // the speed the motor is currently at, always between -4096 and 4096
        bool invert; // if the actions of the motor should be inverted or not

        void convertToAction() {
            int enablepin;
            int inA;
            int inB;
            switch (this->MotorID) {
                case 0:
                {
                    enablepin = 0; 
                    inA = 1;
                    inB = 2;
                    break;
                }
                case 1:
                {
                    enablepin = 5; 
                    inA = 4;
                    inB = 3;
                    break;
                }
                case 2:
                {
                    enablepin = 8; 
                    inA = 9;
                    inB = 10;
                    break;
                }
                case 3:
                {
                    enablepin = 13; 
                    inA = 12;
                    inB = 11;
                    break;
                }
                default:
                    Serial.println("Invalid Convert");
                    return;
            }
            if (this->speed == 10000) { // Short brake functionality where in1 and in2 are high.
                this->associatedDevice->setPin(enablepin,4095);
                this->associatedDevice->setPin(inA,4095);
                this->associatedDevice->setPin(inB,4095);
            }
            else if (this->speed == 0) { // Stop Mode
                this->associatedDevice->setPin(enablepin,4095);
                this->associatedDevice->setPin(inA,0);
                this->associatedDevice->setPin(inB,0);
            }
            else if (this->speed > 0) {
                this->associatedDevice->setPin(enablepin,this->speed); // Clockwise
                this->associatedDevice->setPin(inA,4095);
                this->associatedDevice->setPin(inB,0);
            }
            else if (this->speed < 0) {
                this->associatedDevice->setPin(enablepin,abs(this->speed)); // Anticlockwise
                this->associatedDevice->setPin(inA,0);
                this->associatedDevice->setPin(inB,4095);
            }
            
        }


    public:
        Motor(Adafruit_PWMServoDriver* PCA9685Ptr, int MotorID) { // Constructor for the Motor
            this->MotorID = MotorID;
            this->invert = false;
            if (MotorID > 3 || MotorID < 0) {
                Serial.println("Invalid MotorID");
                this->MotorID = 4;
            }
            this->associatedDevice = PCA9685Ptr;
            return; 
        }
        Motor(Adafruit_PWMServoDriver* PCA9685Ptr, int MotorID, bool invert) { // Constructor for the Motor
            this->MotorID = MotorID;
            this->invert = invert;
            if (MotorID > 3 || MotorID < 0) {
                Serial.println("Invalid MotorID");
                this->MotorID = 4;
            }
            this->associatedDevice = PCA9685Ptr;
            return; 
        }
        Motor() {
            this->MotorID = 0;
            this->associatedDevice = nullptr;
            this->speed = 0;
            this->invert = false;
        }

        void setSpeed(int speed) { // public set speed method
            if (speed > 100 || speed < -100) {
                Serial.println("Not a valid speed");
                return;
            }
            this->speed = map(speed,-100,100,-4095,4095);
            if (this->invert) {
                this->speed = speed*-1;
            }
            convertToAction();
        }

        void ShortBrakeDoubleHigh() { // public set speed method
            this->speed = 10000; // secret code for short break functionality.
            convertToAction();
        }
        

};