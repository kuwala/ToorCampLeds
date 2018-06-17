//Master teensy 3.6 reads three serial inputs
#include "FastLED.h"
// led Parts
#define NUM_LEDS 300
#define LED_PIN 35
#define LED_BRIGHTNESS 64
CRGB leds[NUM_LEDS];
CRGB pressedColor = CRGB(150,150,150);

#define HWSERIAL1 Serial1 //RX pin is pin 0
#define HWSERIAL4 Serial4 //RX pin is pin 23
#define HWSERIAL5 Serial5 // RX pin is 26


void setup()
{
  // FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
  // leds[0] = CRGB(0,0,32);
  // FastLED.show();
  // delay(200);
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
	// FastLED.addLeds<WS2812SERIAL ,LED_PIN,RGB>(leds,NUM_LEDS);
	// LEDS.setBrightness(84);
  leds[3] = CRGB(0,128,0);
  FastLED.show();
  delay(200);
  leds[3] = CRGB(0,0,0);
  FastLED.show();

  Serial.begin(38400);
  HWSERIAL1.begin(38400);
  HWSERIAL4.begin(38400);
  HWSERIAL5.begin(38400);
  Serial.println("starting teensy");
}

int numOfKeys = 21;
byte keysOnSerial1[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
byte keysOnSerial4[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
byte keysOnSerial5[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};

byte remapping[] = {'S','D','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};

int keysToLedSegments[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};

// special segments
// 14 - backspace  16 leds
// 15 - backslash

int numSegments = 58;
int ledSegments[] = {0/*esc*/, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48,   52/*backspace*/,
  68/*backslash*/,   78, 82, 86, 90, 94, 98, 102, 106, 110, 114, 118, 122,  126/*tab*/,
  136/*capslock*/,  140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180,  184/*enter*/,
  194/*right shift*/,  210, 214, 218, 222, 226, 230, 234, 238, 242, 246,   250/*left shift*/,
   254/*right ctrl*/, 264/*alt*/, 268/*space*/,308/*alt*/,312/*ctrl*/,322/*used as length of ctrl*/};

void mapKeyToLeds(char key) {
}

void loop(){
  testInput();
  // // doInputs();
  updateLeds();
  FastLED.show();

  // Serial.println("running");
  // delay(50);
}
void testInput() {
  //Serial for testing input via laptop
  while (Serial.available() > 0) {
    int keyPressed = Serial.parseInt();
    char state = Serial.read();

    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    if (keyPressed < numOfKeys) {
      Serial.println((char)keysOnSerial1[keyPressed]);
      lightUpSegment(keyPressed);
//      Keyboard.print((char)keysOnSerial1[keyPressed]);
    } else {
      Serial.println("KeyPressed is out of Bounds");
    }
    Serial.print(" - ");
    Serial.print("State (D)own or (U)p : ");
    Serial.println(state);

  }
}
void doInputs() {
  while (HWSERIAL1.available() > 0) {
    int keyPressed = HWSERIAL1.parseInt();
    char state = HWSERIAL1.read();

    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    if (keyPressed < numOfKeys) {
      Serial.println((char)keysOnSerial1[keyPressed]);
      lightUpSegment(keyPressed);
//      Keyboard.print((char)keysOnSerial1[keyPressed]);
    } else {
      Serial.println("KeyPressed is out of Bounds");
    }
    Serial.print(" - ");
    Serial.print("State (D)own or (U)p : ");
    Serial.println(state);

  }
  while (HWSERIAL4.available() > 0) {
    int keyPressed = HWSERIAL4.parseInt();
    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    Serial.println((char)keysOnSerial4[keyPressed]);
//    Keyboard.print((char)keysOnSerial4[keyPressed]);
  }
  while (HWSERIAL5.available() > 0) {
    int keyPressed = HWSERIAL5.parseInt();
    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    Serial.println((char)keysOnSerial5[keyPressed]);
//    Keyboard.print((char)keysOnSerial5[keyPressed]);
  }
}

void updateLeds() {
  // dim
  for (unsigned int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(4);
  }
  // redraw
}

void lightUpSegment(int segment) {
    int endIndex = ledSegments[segment + 1];
    for (int i= ledSegments[segment]; i< endIndex; i++) {
      leds[i] = pressedColor;
    }
}

void clearLEDS() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
}
