#include <Arduino.h>
#include <Stepper.h>

// change this to the number of steps on your motor
#define STEPS 4096

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(STEPS, 8, 9);

void setup() {
  // set the speed of the motor to 30 RPMs
  stepper.setSpeed(30);
}

void loop() {
  stepper.step();
}