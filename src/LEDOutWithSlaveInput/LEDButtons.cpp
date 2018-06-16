#include "LEDButtons.h"

LEDButtons::LEDButtons(CRGB* pLeds, Inputs* pInputs) {
  mLeds = pLeds;
  mNumLeds = 8;
  mInputs = pInputs;
  mPressedColor = CRGB(255,0,0);

}
void LEDButtons::update() {
  // this would be great with an observer patternd
  /*
  // normal mode
  int button = 2;
  if(mInputs->isPressed(button) == true) {
    // light up led 1
    mLeds[1] = mPressedColor;
    Serial.println("but1 pressed from ledButtons");
  }
    // mLeds[1] = mPressedColor;
    */

  //dim led 1
  for (unsigned int i = 0; i < mNumLeds; i++) {
    mLeds[i].fadeToBlackBy(1);
    mLeds[i].fadeToBlackBy(16);
  }

}
void LEDButtons::onNotify(Event event) {
  if (event == Event::BUT1_PRESSED) {
    mLeds[0] = mPressedColor;
    Serial.println("but1 pressed from ledButtons");
  }
  if (event == Event::BUT2_PRESSED) {
    mLeds[1] = mPressedColor;
    Serial.println("but2 pressed from ledButtons");
  }
  if (event == Event::BUT3_PRESSED) {
    mLeds[2] = mPressedColor;
    Serial.println("but3 pressed from ledButtons");
  }
  if (event == Event::BUT4_PRESSED) {
    mLeds[3] = mPressedColor;
    Serial.println("but4 pressed from ledButtons");
  }
}
