/* * * * * * * * * *
Master teensy 3.6 reads three serial inputs
Hardware:
Connect LEDstrip to pin 35
* * * * * * * * * */

#include "FastLED.h"
// led Parts
#define NUM_LEDS 344
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
  // leds[3] = CRGB(0,128,0);
  // FastLED.show();
  // delay(200);
  // leds[3] = CRGB(0,0,0);
  // FastLED.show();

  Serial.begin(38400);
  HWSERIAL1.begin(38400);
  HWSERIAL4.begin(38400);
  HWSERIAL5.begin(38400);
  Serial.println("starting teensy");
}

const int numOfKeys = 21; // per section
// byte keysOnSerial1[] = {'A','B','C','2','1',(byte)27/*ESC*/,'G','~','I','J','4','5','M','N','O','P','Q','R','S','T','U'};
// byte keysOnSerial4[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
// byte keysOnSerial5[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
// maps buttons pressed onto ledSegments

// int ledSegmentsOnSerial1[] = {0, 1, 2, 3, 2, 0, 6, 1, 8, 8, 5, 6, 26, 25, 14, 15, 16, 17, 18, 19, 4};
// byte keysOnSerial1[] = {0, 1, 2, '2', '1', (byte)27/*ESC*/, 6, '~', 8, '7', '4', '5', 'w', 'e', 14, 15, 16, 17, 18, 19, '3'};
//
// int ledSegmentsOnSerial4[] = {19, 1, 2, 20, 22, 5, 11, 21, 8, 9, 10, 7, 12, 23, 24, 15, 16, 10, 18, 19, 9};
// int keysOnSerial4[]        = {'o', 1, 2, 'i', 'y', 5, '0', 'u', 8, 9, 10, '6', 12, 't', 'r', 15, 16, '9', 18, 19, '8'};
//
// int ledSegmentsOnSerial5[] = {0, 1, 2, 12, 17, 5, 6, 7, 8, 9, 10, 11, 16, 13, 14, 15, 15, 17, 14, 18, 13};
// int keysOnSerial5[]        = {0, 1, 2, '-', '[', 5, 6, 7, 8, 9, 10, 11, ']', 13, 14, 15, '\\', 17, (byte)8/*backspace*/, 'p', '='};

byte keysOnSerial1[] = {'L'/*lctrl*/, 'C'/*caps*/, 'T'/*tab*/, '2', '1', (byte)27/*esc*/, 'q', '~', 'z', '7', '4', '5', 'w', 'e', 's', 'd', 'x', 'A'/*lalt*/, 'a', 'S'/*leftshit*/, '3'};
int ledSegmentsOnSerial1[] = { 54, 29, 28, 3, 2, 0, 27, 1, 52, 8, 5, 6, 26, 25, 31, 32, 51, 55, 30, 53, 4 };

byte keysOnSerial4[] = {'o', 'b', 'h', 'i', 'y', 'k', '0', 'u', 'm', 'j', 'v', '6', 'c', 't', 'r', 'f', 'g', '9', 'n', ' ', '8'};
int ledSegmentsOnSerial4 [] = { 19, 48, 35, 20, 22, 37, 11, 21, 46, 36, 49, 7, 50, 23, 24, 33, 34, 10, 47, 56, 9 };

// byte keysOnSerial5[] = { '?', '/', '?',  '-', '[', '\'', '.', '?', 'l', 'A'/*ralt*/, ',', ']', 'S'/*rshift*/, (byte)13/*enter*/, 'C'/*rctrl*/, '\\', ';', (byte)8/*backspace*/, 'p', '=' };
// int ledSegmentsOnSerial5 [] = { 0, 45, 2, 12, 17, 42, 46, 38, 60, 47, 16, 44, 43, 61, 15, 39, 14, 18, 13 };

byte keysOnSerial5[]        = {0, '/', 2, '-', '[', '\'', '.', 'l', 'A'/*ralt*/, ',', '?', '?', ']', 'S'/*rshift*/, 'E'/*enter*/, 'C'/*rctrl*/, '\\', ';', (byte)8/*backspace*/, 'p', '='};
int ledSegmentsOnSerial5[] = {0, 43, 2, 12, 17, 40, 44, 38, 57, 45, 10, 11, 16, 42, 41, 58, 15, 39, 14, 18, 13};

int numSegments = 60;
int ledSegments[] = {0/*esc*/, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52,   56/*backspace*/,
  72/*backslash*/,   82, 86, 90, 94, 98, 102, 106, 110, 114, 118, 122, 126,  130/*tab*/,
  140/*capslock*/,  150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190,  194/*enter*/,
  204/*right shift*/,  220, 224, 228, 232, 236, 240, 244, 248, 252, 256,   260/*left shift*/,
   276/*right ctrl*/, 286/*alt*/, 290/*space*/, 330/*alt*/, 334/*ctrl*/, 344/*used as length of ctrl*/};


void loop(){
  // testAllAudioTriggers();
  testInput();
  doInputs();
  updateLeds();
  FastLED.show();
}
void testAllAudioTriggers() {
  for (size_t i = 0; i < 58; i++) {
    sendAudioTrigger(i);
    Serial.println("sending audio Trigger");
    delay(1000);
  }
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
    } else {
      Serial.println("KeyPressed is out of Bounds");
    }
      lightUpSegment(keyPressed);

    Serial.print(" - ");
    Serial.print("State (D)own or (U)p : ");
    Serial.println(state);

  }
}
void sendAudioTrigger(int segment) {
  if (segment < numSegments) {
    Serial5.print(segment);
    Serial5.print('D');
  } else {
    Serial.println("sendAudioTrigger out of bounds");
  }

}
void doInputs() {
  while (HWSERIAL1.available() > 0) {
    int keyPressed = HWSERIAL1.parseInt();
    char state = HWSERIAL1.read();

    Serial.print("keyPressed Serial1: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    if (keyPressed < numOfKeys) {

      Serial.print((char)keysOnSerial1[keyPressed]);
      // Keyboard.print((char)keysOnSerial1[keyPressed]);
      int segment = ledSegmentsOnSerial1[keyPressed];
      lightUpSegment(segment);
      sendAudioTrigger(segment);

    } else {
      Serial.print("KeyPressed is out of Bounds");
    }


    Serial.print(" - ");
    Serial.print("State : ");
    Serial.println(state);

  }
  while (HWSERIAL4.available() > 0) {
    int keyPressed = HWSERIAL4.parseInt();
    char state = HWSERIAL4.read();


    Serial.print("keyPressed Serial4: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    if (keyPressed < numOfKeys) {
      Serial.print((char)keysOnSerial4[keyPressed]);
      // Keyboard.print((char)keysOnSerial4[keyIndex]);
      int segment = ledSegmentsOnSerial4[keyPressed];
      lightUpSegment(segment);
      sendAudioTrigger(segment);
    } else {
      Serial.print("KeyIndex is out of Bounds");
    }


    Serial.print(" - ");
    Serial.print("State : ");
    Serial.println(state);
  }
  while (HWSERIAL5.available() > 0) {
    int keyPressed = HWSERIAL5.parseInt();
    char state = HWSERIAL5.read();


    Serial.print("keyPressed Serial5: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    if (keyPressed < numOfKeys) {
      Serial.print((char)keysOnSerial5[keyPressed]);
      // Keyboard.print((char)keysOnSerial5[keyIndex]);
      int segment = ledSegmentsOnSerial5[keyPressed];
      lightUpSegment(segment);
      sendAudioTrigger(segment);
    } else {
      Serial.print("KeyIndex is out of Bounds");
    }


    Serial.print(" - ");
    Serial.print("State : ");
    Serial.println(state);
  }
}

void updateLeds() {
  // dim
  for (unsigned int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(10);
  }
  // redraw
}

void lightUpSegment(int segment) {
    if(segment < numSegments-1) {
      int endIndex = ledSegments[segment + 1];
      for (int i= ledSegments[segment]; i< endIndex; i++) {
        leds[i] = pressedColor;
      }
    } else {
      Serial.println("lightUpSegment out of bounds");
    }
}

void clearLEDS() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0,0,0);
  }
}
