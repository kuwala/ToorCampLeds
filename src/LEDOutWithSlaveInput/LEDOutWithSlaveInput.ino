#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include "Inputs.h"
#include "SerialInputs.h"
#include "LEDButtons.h"
// #include "AudioPlayer.h"
#include "KeyboardPresser.h"

/* Hardware Notes
Teensy 3.2 with an Audio Shield
8LED NEOPIXEL strip on pin 1 (pin 8 did not work)
internal pull_up buttons on pins 0,2,3,4
*/


// inputs
// Inputs inputs = Inputs();
SerialInputs inputs = SerialInputs();

// led Parts
#define NUM_LEDS 300
#define LED_PIN 1
#define LED_BRIGHTNESS 64
CRGB leds[NUM_LEDS];
unsigned long timer = 0;
unsigned int timeStep = 1000;

// led View objects
LEDButtons ledButtons = LEDButtons(leds);
// Audio
// AudioPlayer audioPlayer = AudioPlayer();
// Keyboard
KeyboardPresser keyboard = KeyboardPresser();



void setup() {
  // FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
	FastLED.addLeds<WS2812SERIAL ,LED_PIN,RGB>(leds,NUM_LEDS);
	// LEDS.setBrightness(84);
  leds[3] = CRGB(0,128,0);
  FastLED.show();
  delay(200);
  leds[3] = CRGB(0,0,0);

  Serial.begin(38400);
  Serial4.begin(38400);

  inputs.begin();
  inputs.addObserver(&ledButtons);
  // inputs.addObserver(&audioPlayer);
  inputs.addObserver(&keyboard);
  // audioPlayer.begin();
  // setupAudio();

}

void loop() {
  //update all the parts
  // Serial.println("looping");
  // delay(10);

  inputs.update();
  ledButtons.update();
  // audioButtons.update();
  // inputs.debugText();
  // debuging
  // if(millis() - timer > timeStep) {
  //   Serial.println("<3 heartBeat <3");
  //   timer = millis();
  // }

  // if (playSdWav1.isPlaying() == false) {
  //   const char *filename = filelist[filenumber];
  //   filenumber = filenumber + 1;
  //   if (filenumber >= NUM_AUDIO_FILES) filenumber = 0;
  //   Serial.print("Start playing ");
  //   Serial.println(filename);
  //   playSdWav1.play(filename);
  //
  //
  //   delay(8); // wait for library to parse WAV info
  // }

  // leds[3] = CRGB(random(127),random(127),0);
  FastLED.show();
}
