/* Hardware Notes
Teensy 3.2 with an Audio Shield
8LED NEOPIXEL strip on pin 1 (pin 8 did not work)
internal pull_up buttons on pins 0,2,3,4
*/
#include <Arduino.h>

/////////////////////////////////////////////////////////////
// Audio Parts
/////////////////////////////////////////////////////////////

// GUItool: begin automatically generated code
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

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

#define NUM_AUDIO_FILES 63

// const char * fileList[NUM_AUDIO_FILES] = {
//   "01.wav", "2.wav", "3.wav", "4.wav", "5.wav", "6.wav", "7.wav"
// };
const char * fileList[NUM_AUDIO_FILES] = {
  "01.wav", "02.wav", "03.wav", "04.wav", "05.wav", "06.wav", "07.wav", "08.wav", "09.wav",
  "10.wav", "11.wav", "12.wav", "13.wav", "14.wav", "15.wav", "16.wav", "17.wav", "18.wav",
  "19.wav", "20.wav", "21.wav", "22.wav", "23.wav", "24.wav", "25.wav", "26.wav", "27.wav",
  "28.wav", "29.wav", "30.wav", "31.wav", "32.wav", "33.wav", "34.wav", "35.wav", "36.wav",
  "37.wav", "38.wav", "39.wav", "40.wav", "41.wav", "42.wav", "43.wav", "44.wav", "45.wav",
  "46.wav", "47.wav", "48.wav", "49.wav", "50.wav", "51.wav", "52.wav", "53.wav", "54.wav",
  "55.wav", "56.wav", "57.wav", "58.wav", "59.wav", "60.wav", "61.wav", "62.wav", "63.wav" };

// const char * fileList[NUM_AUDIO_FILES] = {
//   "DAN1.WAV", "DAN2.WAV", "DAN3.WAV", "DAN4.WAV", "DAN5.WAV", "DAN6.WAV"
// };
#define HWSERIAL1 Serial1

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


void setup() {
  setupAudio();
  Serial.begin(38400); // for testing
  Serial1.begin(38400);
  playSdWav1.play(fileList[0]);

}

void loop() {
  // check for serial input
  while(HWSERIAL1.available() > 0) {
    int keyPressed = HWSERIAL1.parseInt();
    char state = HWSERIAL1.read();
    playSound(keyPressed);
  }

  while(Serial.available() > 0) {
    int keyPressed = Serial.parseInt();
    char state = Serial.read();
    playSound(keyPressed);
  }

}
void playSound(int fileNumber) {
  if (fileNumber < NUM_AUDIO_FILES) {
    const char *fileName = fileList[fileNumber];
    // polyphonic of 3
    int playerNumber = fileNumber % 3;
    switch(playerNumber) {
      case 0:
        playSdWav1.play(fileName);
      break;
      case 1:
        playSdWav2.play(fileName);
      break;
      case 2:
        playSdWav3.play(fileName);
      break;
    }
    delay(4);
  } else {
    Serial.println("fileNumber Out of bounds.");
  }
}
