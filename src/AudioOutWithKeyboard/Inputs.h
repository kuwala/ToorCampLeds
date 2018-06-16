/*
 * Inputs.h - A collection of inputs Buttons and Encoders
 * To be used as user input for a larger program.
 * Its an Inputs Manager for Ardreamo
 * by - @kuwala 2-16-2018
 *
 */

#ifndef INPUTS_H
#define INPUTS_H


#include <Arduino.h>
#include <Encoder.h>
#include <Bounce.h>

#include "Subject.h"
#include "Helpers.h"


// refactor into interface_manager class

#define BUT1 0
#define BUT2 2
#define BUT3 3
#define BUT4 4
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
