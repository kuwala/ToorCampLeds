/*
 * Inputs.h - A collection of inputs Buttons and Encoders
 * To be used as user input for a larger program.
 * Its an Inputs Manager for Ardreamo
 * by - @kuwala 2-16-2018
 *
 */

#ifndef Inputs_h
#define Inputs_h


#include "Arduino.h"
#include <Encoder.h>
#include <Bounce.h>

#include "Subject.h"
#include "Helpers.h"


// refactor into interface_manager class

#define BUT1 5
#define BUT2 6
#define BUT3 7
#define BUT4 8
#define BUT_BOUNCE 5

// Add 104 capacitors from encoder pins a and b to ground
// To do some debouncing.
#define ENCODER1A 1
#define ENCODER1B 2

#define ENCODER2A 3
#define ENCODER2B 4

class Inputs : public Subject {
   private:
    Encoder knobRight;
    long positionRight;
    Bounce button1;
    Bounce button2;
    Bounce button3;
    Bounce button4;
  public:
    Inputs();
    void begin();
    void update();
    long getKnobRightMove();
    bool isPressed(int pButton);
    void debugText();
};
#endif
