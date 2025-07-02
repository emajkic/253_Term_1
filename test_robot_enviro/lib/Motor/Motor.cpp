#include <Arduino.h>
#include "Constants.h"
#include "Motor.h"
#include "PinSetup.h"

/*
* Class constructor
*/
Motor::Motor(int pinA, int pinB) { //Should we rename these to pinCCW and pinCW s.t. know which is which
    this->pinA = pinA; 
    this->pinB = pinB;

    ledcSetup(pwmChannel1, 500, 12); // (pwmchannel to use,  frequency in Hz, number of bits) NOTE: frequency affect speed range
    ledcAttachPin(pinA, pwmChannel1);
    ledcAttachPin(pinB, pwmChannel1);
}

/*
* Stop motor, ie. set speed to 0
*/
void Motor::stop() {
    ledcWrite(pwmChannel1, 0); 
    ledcWrite(pwmChannel1, 0); 
}

/*
* Set speed of motor 
* 
* @param speed   speed to set the motor; int. between 0-4095
*/
void Motor::setSpeed(int speed) {
    ledcWrite(pwmChannel1, speed); 
    ledcWrite(pwmChannel1, speed); 
    this->speed = speed;
}

/*
* Get speed of motor 
*
* @return the current speed of the motor 
*/
int Motor::getSpeed() {
    return this->speed; 
}