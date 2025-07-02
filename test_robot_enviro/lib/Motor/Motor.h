#ifndef Motor_h
#define Motor_h

#include <Arduino.h>
#include <cmath>

class Motor {
    public:
       /*
       * Class constructor
       */
       Motor(int pinA, int pinB);

       /*
       * Stop motor, ie. set speed to 0
       */
       void stop();

       /*
       * Set speed of motor 
       * 
       * @param speed   speed to set the motor; int. between 0-4095
       */
       void setSpeed(int speed);

       /*
       * Get speed of motor 
       *
       * @return the current speed of the motor 
       */
       int getSpeed();
       
    private:
        int pinA; //should we rename this to pinCW and pin CCW????
        int pinB;
        int speed;
};

#endif