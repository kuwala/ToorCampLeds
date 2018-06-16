#include <Arduino.h>
// #include <WS2812Serial.h>
// #define USE_WS2812SERIAL
// #include <FastLED.h>
#include <Adafruit_NeoPixel.h>

#include "Inputs.h"
// #include "LEDButtons.h"
#include "AudioPlayer.h"
#include "KeyboardPresser.h"

#define PIN 1
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);


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
#define NUM_LEDS 8
#define LED_PIN 1
#define LED_BRIGHTNESS 64
// CRGB leds[NUM_LEDS];
unsigned long timer = 0;
unsigned int timeStep = 1000;

// led View objects
// LEDButtons ledButtons = LEDButtons(leds, &inputs);
// Audio
AudioPlayer audioPlayer = AudioPlayer();
// Keyboard
KeyboardPresser keyboard = KeyboardPresser();

// testing
unsigned long testTimer = 0;
int testTimeStep = 10;
int colorCounter = 0;


void setup() {
  // FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
	// FastLED.addLeds<WS2812SERIAL ,LED_PIN,RGB>(leds,NUM_LEDS);
	// // LEDS.setBrightness(84);
  // leds[3] = CRGB(0,128,0);
  // FastLED.show();
  // delay(200);
  // leds[3] = CRGB(0,0,0);
  //
  strip.begin();
  strip.show();
  inputs.begin();
  // inputs.addObserver(&ledButtons);
  inputs.addObserver(&audioPlayer);
  inputs.addObserver(&keyboard);
  // audioPlayer.begin();
  Serial.begin(9600);
  setupAudio();

}

void loop() {
  //update all the parts

  inputs.update();
  // ledButtons.update();
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

  // FastLED.show();
  // Some example procedures showing how to display to the pixels:
// colorWipe(strip.Color(255, 0, 0), 50); // Red
// colorWipe(strip.Color(0, 255, 0), 50); // Green
// colorWipe(strip.Color(0, 0, 255), 50); // Blue
// //colorWipe(strip.Color(0, 0, 0, 255), 50); // White RGBW
// // Send a theater pixel chase in...
// theaterChase(strip.Color(127, 127, 127), 50); // White
// theaterChase(strip.Color(127, 0, 0), 50); // Red
// theaterChase(strip.Color(0, 0, 127), 50); // Blue
//
// rainbow(20);
// rainbowCycle(20);
// theaterChaseRainbow(50);
if (millis() - testTimer > testTimeStep) {
  testTimer = millis();
  colorCounter ++;
  if (colorCounter > 255) {
    colorCounter = 0;
  }
  strip.show();
}
for (int i = 0; i < 16; i++) {
  uint32_t c = strip.Color(colorCounter,colorCounter,colorCounter);
  strip.setPixelColor(i, c);
}
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
