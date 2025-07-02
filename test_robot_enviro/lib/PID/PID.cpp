#include <Arduino.h>
#include "Constants.h"
#include "PinSetup.h"
#include "Motor.h"
#include "PID.h"

PID::PID(PIDType pidType, Motor leftMotor, Motor rightMotor) : leftMotor(leftMotor), rightMotor(rightMotor) { //Should we rename these to pinCCW and pinCW s.t. know which is which
    switch (pidType)
    {
    case PIDType::LineFollower:
        this->KP = KP_LINE_FOLLOWER;
        this->KI = KI_LINE_FOLLOWER;
        this->KD = KD_LINE_FOLLOWER;
        break;
    case PIDType::CompassFollower:
        this->KP = KP_COMPASS_FOLLOWER;
        this->KI = KI_COMPASS_FOLLOWER;
        this->KD = KD_COMPASS_FOLLOWER;        
        break;
    default:
        break;
    } 

    this->error = 0;
    this->lastError = 0;

    pinMode(LEFT_QRD_PIN, INPUT);
    pinMode(RIGHT_QRD_PIN, INPUT);
}

void PID::usePID() {
    
    
}

void PID::getError() {
    int leftReading = digitalRead(LEFT_QRD_PIN);
    int rightReading = digitalRead(RIGHT_QRD_PIN);

    if (leftReading == BLACK && rightReading == BLACK) { //Threshold set by hardware (comparator)
        this->error = 0;
    } else if (leftReading == BLACK && rightReading == WHITE) {
        this->error = 1;
    } else if (leftReading == WHITE && rightReading == BLACK) {
        this->error = -1;
    } else if (leftReading == WHITE && rightReading == WHITE) {
        if (lastError > 0) {
            this->error = 5;
        } else if (lastError <= 0) { //CHECK THIS -> WHAT IF LASTERR = 0
            this->error = -5;
        } 
    }
}