#include "SerialInputs.h"

#define HWSERIAL1 Serial1 //RX pin is pin 0
#define HWSERIAL4 Serial4 //RX pin is pin 23
#define HWSERIAL5 Serial5 // RX pin is 26

SerialInputs::SerialInputs(){

}
void SerialInputs::begin()
{
  // HWSERIAL1.begin(38400);
  // HWSERIAL4.begin(38400);
  // HWSERIAL5.begin(38400);
}

void SerialInputs::update() {
  while (Serial.available() > 0) {
    int keyPressed = Serial.parseInt();
    char state = Serial.read();

    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    if (keyPressed < NUM_KEYS) {
      Serial.println((char)keysOnSerial1[keyPressed]);
//      Keyboard.print((char)keysOnSerial1[keyPressed]);
      if (keyPressed == 0) {
        notify(Event::BUT1_PRESSED);
      }
      if (keyPressed == 1) {
        notify(Event::BUT2_PRESSED);
      }
      if (keyPressed == 2) {
        notify(Event::BUT3_PRESSED);
      }
      if (keyPressed == 3) {
        notify(Event::BUT4_PRESSED);
      }
    } else {
      Serial.println("KeyPressed is out of Bounds");
    }
    Serial.print(" - ");
    Serial.print("State (D)own or (U)p : ");
    Serial.print(state);


  }

//   while (HWSERIAL1.available() > 0) {
//     int keyPressed = HWSERIAL1.parseInt();
//     char state = HWSERIAL1.read();
//
//     Serial.print("got a number: ");
//     Serial.print(keyPressed);
//     Serial.print(" - ");
//     if (keyPressed < NUM_KEYS) {
//       Serial.println((char)keysOnSerial1[keyPressed]);
// //      Keyboard.print((char)keysOnSerial1[keyPressed]);
//       if (keyPressed == 0) {
//         notify(Event::BUT1_PRESSED);
//       }
//       if (keyPressed == 1) {
//         notify(Event::BUT2_PRESSED);
//       }
//       if (keyPressed == 2) {
//         notify(Event::BUT3_PRESSED);
//       }
//       if (keyPressed == 3) {
//         notify(Event::BUT4_PRESSED);
//       }
//     } else {
//       Serial.println("KeyPressed is out of Bounds");
//     }
//     Serial.print(" - ");
//     Serial.print("State (D)own or (U)p : ");
//     Serial.print(state);
//
//
//   }
  while (HWSERIAL4.available() > 0) {
    int keyPressed = HWSERIAL4.parseInt();
    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    Serial.println((char)keysOnSerial4[keyPressed]);
    Keyboard.print((char)keysOnSerial4[keyPressed]);
  }
  // while (HWSERIAL5.available() > 0) {
  //   int keyPressed = HWSERIAL5.parseInt();
  //   Serial.print("got a number: ");
  //   Serial.print(keyPressed);
  //   Serial.print(" - ");
  //   Serial.println((char)keysOnSerial5[keyPressed]);
  //   Keyboard.print((char)keysOnSerial5[keyPressed]);
  // }
}
