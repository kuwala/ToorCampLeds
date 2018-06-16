// Play 3 wave files simultaneously 

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
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


Bounce button0 = Bounce(0, 15);
Bounce button2 = Bounce(2, 15);  // 15 = 15 ms debounce time

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

// Daniels Add ons
int toggleMoreAudio = 0;
#define NUM_AUDIO_FILES 6

void setup() {
  Serial.begin(9600);
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
  pinMode(13, OUTPUT); // LED on pin 13
  pinMode(0, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  delay(1000);
}

int filenumber = 0;  // while file to play

const char * filelist[NUM_AUDIO_FILES] = {
  "DAN1.WAV", "DAN2.WAV", "DAN3.WAV", "DAN4.WAV", "DAN5.WAV", "DAN6.WAV"
};

elapsedMillis blinkTime;

void loop() {
  
  if (playSdWav1.isPlaying() == false) {
    const char *filename = filelist[filenumber];
    filenumber = filenumber + 1;
    if (filenumber >= NUM_AUDIO_FILES) filenumber = 0;
    Serial.print("Start playing ");
    Serial.println(filename);
    playSdWav1.play(filename);
  
    
    delay(8); // wait for library to parse WAV info
  }
  
  // blink the LED without delays
  if (blinkTime < 250) {
    digitalWrite(13, LOW);
  } else if (blinkTime < 500) {
    digitalWrite(13, HIGH);
  } else {
    blinkTime = 0; // start blink cycle over again
  }
  
  // read pushbuttons
  button0.update();
  if (button0.fallingEdge()) {
    playSdWav1.stop();
    if(toggleMoreAudio == 0) {
      playSdWav2.play("SDTEST1.WAV");
      playSdWav3.play("SDTEST2.WAV");
      delay(16);
      toggleMoreAudio = 1;
    } else {
      toggleMoreAudio = 0;
      playSdWav2.stop();
      playSdWav3.stop();
    }
  }
  button2.update();
  if (button2.fallingEdge()) {
    playSdWav1.stop();
    filenumber = filenumber - 2;
    if (filenumber < 0) filenumber = filenumber + 4;
  }
  
  // read the knob position (analog input A2)
  //int knob = analogRead(A2);
 // float vol = (float)knob / 1280.0;
  sgtl5000_1.volume(0.5);
  //Serial.print("volume = ");
  //Serial.println(vol);
}




