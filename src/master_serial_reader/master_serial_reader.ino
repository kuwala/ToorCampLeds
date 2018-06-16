//Master teensy 3.6 reads three serial inputs

#define HWSERIAL1 Serial1 //RX pin is pin 0
#define HWSERIAL4 Serial4 //RX pin is pin 23
#define HWSERIAL5 Serial5 // RX pin is 26


void setup()
{                
  Serial.begin(38400);
  HWSERIAL1.begin(38400);
  HWSERIAL4.begin(38400);
  HWSERIAL5.begin(38400);
}

int numOfKeys = 21;
byte keysOnSerial1[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
byte keysOnSerial4[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};
byte keysOnSerial5[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U'};

int val;
String keyPressedString = "";

void loop(){

  while (HWSERIAL1.available() > 0) {
    int keyPressed = HWSERIAL1.parseInt();
    char state = HWSERIAL1.read();
    
    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    if (keyPressed < numOfKeys) {
      Serial.println((char)keysOnSerial1[keyPressed]);
//      Keyboard.print((char)keysOnSerial1[keyPressed]);
    } else {
      Serial.println("KeyPressed is out of Bounds");
    }
    Serial.print(" - ");
    Serial.print("State (D)own or (U)p : ");
    Serial.print(state); 
    
  }
  while (HWSERIAL4.available() > 0) {
    int keyPressed = HWSERIAL4.parseInt();
    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    Serial.println((char)keysOnSerial4[keyPressed]);
    Keyboard.print((char)keysOnSerial4[keyPressed]);
  }
  while (HWSERIAL5.available() > 0) {
    int keyPressed = HWSERIAL5.parseInt();
    Serial.print("got a number: ");
    Serial.print(keyPressed);
    Serial.print(" - ");
    Serial.println((char)keysOnSerial5[keyPressed]);
    Keyboard.print((char)keysOnSerial5[keyPressed]);
  }
  
  delay(10);

}

