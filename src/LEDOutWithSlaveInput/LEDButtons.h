#ifndef LEDBUTTONS_H
#define LEDBUTTONS_H
#include "FastLED.h"
#include "Inputs.h"
#include "Observer.h"
#include "Helpers.h"

class LEDButtons : public Observer {
public:
  LEDButtons(CRGB* pLeds, Inputs* pInputs);
  LEDButtons(CRGB* pLeds);
  void update();
  void onNotify(Event event);
private:
  CRGB* mLeds;
  unsigned int mNumLeds;
  Inputs* mInputs;
  CRGB mPressedColor;

};

#endif
