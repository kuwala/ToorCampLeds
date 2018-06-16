#include "KeyboardPresser.h"

KeyboardPresser::KeyboardPresser() {

}

void KeyboardPresser::update() {

}
void KeyboardPresser::onNotify(Event event) {

  if (event == Event::BUT1_PRESSED) {
    Keyboard.print("w");
  }
  if (event == Event::BUT2_PRESSED) {
    Keyboard.print("s");
  }
  if (event == Event::BUT3_PRESSED) {

    Keyboard.print("a");
  }
  if (event == Event::BUT4_PRESSED) {
    Keyboard.print("d");
  }

}
