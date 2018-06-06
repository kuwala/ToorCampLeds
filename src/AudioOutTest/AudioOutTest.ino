#include <Arduino.h>
#include "Inputs.h"
#include "LEDButtons.h"
/* Hardware Notes
Teensy 3.2 with an Audio Shield
8LED NEOPIXEL strip on pin 14
internal pull_up buttons on pins 5,6,7,8
*/

// inputs
Inputs inputs = Inputs();

// audio
// AudioButtons audioButtons = AudioButtons(inputs);

// led Parts
#define NUM_LEDS 8
#define LED_PIN 14
#define LED_BRIGHTNESS 64
CRGB leds[NUM_LEDS];
unsigned long timer = 0;
unsigned int timeStep = 1000;

// led View objects
LEDButtons ledButtons = LEDButtons(leds, &inputs);



void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  leds[3] = CRGB(0,128,0);
  FastLED.show();
  delay(200);
  leds[3] = CRGB(0,0,0);

  inputs.begin();
  inputs.addObserver(&ledButtons);
  Serial.begin(9600);

}

void loop() {
  //update all the parts

  inputs.update();
  ledButtons.update();
  // audioButtons.update();
  // inputs.debugText();
  // debuging
  // if(millis() - timer > timeStep) {
  //   Serial.println("<3 heartBeat <3");
  //   timer = millis();
  // }


  FastLED.show();
}
