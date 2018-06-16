#include "AudioPlayer.h"
#include "AudioParts.h"

AudioPlayer::AudioPlayer() {

}

void AudioPlayer::begin() {
}

void AudioPlayer::update() {
}
void AudioPlayer::onNotify(Event event) {
  if (event == Event::BUT1_PRESSED) {
      playSdWav1.play("DAN1.WAV");
  }
  if (event == Event::BUT2_PRESSED) {
      playSdWav2.play("DAN2.WAV");
  }
  if (event == Event::BUT3_PRESSED) {
    playSdWav3.play("DAN3.WAV");
  }
  if (event == Event::BUT4_PRESSED) {
    playSdWav3.play("DAN4.WAV");
  }
}
