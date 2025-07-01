#ifndef PID_h
#define PID_h

#include <Arduino.h>
#include <cmath>

enum class PIDType {
    LineFollower,
    CompassFollower
};

class PID {
    public:
       /*
        * Class Constructor
        */
        PID(PIDType pidType); //add more param once figured out

        void usePID();

        void resetPID();

        bool bothOnWhite();

       /*
        * Setters and Getters
        */
       void setKP(int KP) { this->KP = KP; }
       void setKI(int KI) { this->KI = KI; };
       void setKD(int KD) { this->KD = KD; };

       int getKP() { return this->KP; }
       int getKI() { return this->KI; }
       int getKD() { return this->KD; }


    private:
        int KP;
        int KD;
        int KI;
};

#endif