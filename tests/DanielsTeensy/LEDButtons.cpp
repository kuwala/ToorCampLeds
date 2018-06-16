#include "LEDButtons.h"

LEDButtons::LEDButtons(CRGB* pLeds, Inputs* pInputs) {
  mLeds = pLeds;
  mInputs = pInputs;
  mPressedColor = CRGB(255,0,0);

}
void LEDButtons::update() {
  // this would be great with an observer pattern
  int button = 2;
  if(mInputs->isPressed(button) == true) {
    // light up led 1
    mLeds[1] = mPressedColor;
    Serial.println("but1 pressed from ledButtons");
  }
    // mLeds[1] = mPressedColor;

  //dim led 1
  mLeds[1].fadeToBlackBy(1);

}
