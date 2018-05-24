#ifndef LEDBUTTONS_H
#define LEDBUTTONS_H
#include "FastLED.h"
#include "Inputs.h"

class LEDButtons {
public:
  LEDButtons(CRGB* pLeds, Inputs* pInputs);
  void update();
private:
  CRGB* mLeds;
  Inputs* mInputs;
  CRGB mPressedColor;

};

#endif
