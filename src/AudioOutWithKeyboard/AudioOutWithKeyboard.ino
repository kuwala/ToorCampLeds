#include <Arduino.h>
#include <WS2812Serial.h>
#define USE_WS2812SERIAL
#include <FastLED.h>
#include "Inputs.h"
#include "LEDButtons.h"
#include "AudioPlayer.h"
#include "KeyboardPresser.h"



/* Hardware Notes
Teensy 3.2 with an Audio Shield
8LED NEOPIXEL strip on pin 1 (pin 8 did not work)
internal pull_up buttons on pins 0,2,3,4
*/

/////////////////////////////////////////////////////////////
// Audio Parts
/////////////////////////////////////////////////////////////
#include "AudioParts.h"

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

AudioPlaySdWav           playSdWav1;     //xy=96,690
AudioPlaySdWav           playSdWav2;     //xy=97,758
AudioPlaySdWav           playSdWav3;     //xy=98,817
AudioMixer4              mixer1;         //xy=313,695
AudioMixer4              mixer2;         //xy=313,775
AudioOutputI2S           i2s2;           //xy=466,771
AudioOutputAnalog        dac1;           //xy=509,203
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 2);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord5(playSdWav3, 0, mixer1, 1);
AudioConnection          patchCord6(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord8(mixer1, 0, i2s2, 0);
AudioConnection          patchCord9(mixer2, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=478,826
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Daniels Add ons
int toggleMoreAudio = 0;
#define NUM_AUDIO_FILES 6

int filenumber = 0;  // while file to play
const char * filelist[NUM_AUDIO_FILES] = {
  "DAN1.WAV", "DAN2.WAV", "DAN3.WAV", "DAN4.WAV", "DAN5.WAV", "DAN6.WAV"
};

void setupAudio() {
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
}
/////////////////////////////////////////////////////////////
// GUItool: end automatically generated code
/////////////////////////////////////////////////////////////



// End of Audio GUI

// inputs
Inputs inputs = Inputs();

// led Parts
#define NUM_LEDS 300
#define LED_PIN 1
#define LED_BRIGHTNESS 64
CRGB leds[NUM_LEDS];
unsigned long timer = 0;
unsigned int timeStep = 1000;

// led View objects
LEDButtons ledButtons = LEDButtons(leds, &inputs);
// Audio
AudioPlayer audioPlayer = AudioPlayer();
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

  inputs.begin();
  inputs.addObserver(&ledButtons);
  inputs.addObserver(&audioPlayer);
  inputs.addObserver(&keyboard);
  // audioPlayer.begin();
  Serial.begin(9600);
  setupAudio();

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

  FastLED.show();
}
