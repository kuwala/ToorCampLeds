#include <Arduino.h>
#include "Inputs.h"
#include "LEDButtons.h"
// MileStone 1 - A Light up keyboard with sounds and lights per key

// inputs
// Inputs needs a generic interface, or it can store the input model inside it
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


// using a simplified MVC pattern

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  leds[3] = CRGB(0,128,0);
  FastLED.show();
  delay(200);
  leds[3] = CRGB(0,0,0);

  inputs.begin();
  Serial.begin(9600);

}

void loop() {
  //update all the parts

  inputs.update();
  ledButtons.update();
  // audioButtons.update();
  inputs.debugText();
  // debuging
  // if(millis() - timer > timeStep) {
  //   Serial.println("<3 heartBeat <3");
  //   timer = millis();
  // }


  FastLED.show();
}
