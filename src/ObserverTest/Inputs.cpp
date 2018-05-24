#include "Arduino.h"
#include <Bounce.h>
#include "Inputs.h"

Inputs::Inputs():
    knobRight(ENCODER2A, ENCODER2B),
    button1(BUT1, BUT_BOUNCE),
    button2(BUT2, BUT_BOUNCE),
    button3(BUT3, BUT_BOUNCE),
    button4(BUT4, BUT_BOUNCE)
{
  positionRight = -999;
}

void Inputs::begin() {
  pinMode(BUT1, INPUT_PULLUP);
  pinMode(BUT2, INPUT_PULLUP);
  pinMode(BUT3, INPUT_PULLUP);
  pinMode(BUT4, INPUT_PULLUP);
}
void Inputs::update() {

  button1.update();
  button2.update();
  button3.update();
  button4.update();

  // check which buttons are pressed and notify the observers
  if (button1.fallingEdge()) {
    notify(Event::BUT1_PRESSED);
  }
  if (button2.fallingEdge()) {
    notify(Event::BUT2_PRESSED);
  }
  if (button3.fallingEdge()) {
    notify(Event::BUT3_PRESSED);
  }
  if (button4.fallingEdge()) {
    notify(Event::BUT4_PRESSED);
  }


}



bool Inputs::isPressed(int pButton) {
  bool pressed = false;
  switch(pButton) {
    case 1:
      pressed = button1.fallingEdge();
      break;
    case 2:
      pressed = button2.fallingEdge();
      break;
    case 3:
      pressed = button3.fallingEdge();
      break;
    case 4:
      pressed = button4.fallingEdge();
      break;

    default:
      break;
  }
  return pressed;
}

long Inputs::getKnobRightMove() {
  long newRight = knobRight.read();
  long difference = newRight - positionRight;
  return difference;
}

void Inputs::debugText() {
  // Encoders
  //
  int newRight = knobRight.read();

  if (newRight != positionRight) {
    Serial.print("Right = ");
    Serial.println(newRight);
    positionRight = newRight;
  }

  // Buttons
  if (button1.fallingEdge()) {
    Serial.println("button1 down");
  }
  if (button1.risingEdge()) {
    Serial.println("button1 up");
  }
  if (button2.fallingEdge()) {
  }
  if (button2.risingEdge()) {
    Serial.println("button2 up");
  }
  if (button3.fallingEdge()) {
    Serial.println("button3 down");
  }
  if (button3.risingEdge()) {
    Serial.println("button3 up");
  }
  if (button4.fallingEdge()) {
    Serial.println("button4 down");
  }
  if (button4.risingEdge()) {
    Serial.println("button4 up");
  }
}
