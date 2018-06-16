//assumes pins are connected to 3.3V pullups on breakout board and button pulls pin low

#define HWSERIAL Serial1  //tx is on pin 1

int delayBetweenSends = 10;  //delay 3 seconds between sends for troubleshooting

void setup()
{
  Serial.begin(38400);
  HWSERIAL.begin(38400);
}

const int numberOfSensors = 21;
byte analogPins[] = {A0,A1,A2,A3,A4,A5,A6,A7,A8,A9,A12,A13,A14,A15,A16,A17,A18,A19,A20,A21,A22};

int sensorValue[numberOfSensors];
int sensorThreshold[numberOfSensors] = {200,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100};

// Button state: 0 up, 1 down
int buttonState[numberOfSensors] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int lastButtonState[numberOfSensors] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int val;

void loop(){
  for (int i = 0; i < numberOfSensors; i++){
    sensorValue[i] = analogRead(analogPins[i]);
    delay(1);
  }

  for (int i = 0; i < numberOfSensors; i++)
  {
    Serial.print("pin ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(sensorValue[i]);
  }

  for (int i = 0; i < numberOfSensors; i++)
  {
    if(sensorValue[i] < sensorThreshold[i])
    {

      // set currentState to down
      buttonState[i] = 1;
    } else {
      // set currentState to Up
      buttonState[i] = 0;
    }

    // if state changed send change
    if(buttonState[i] != lastButtonState[i]) {
      if(lastButtonState[i] == 1 ){
        // was down now released
        Serial.print("pin ");
        Serial.print(i);
        Serial.println(" has been released");
        HWSERIAL.print(i);
        HWSERIAL.print('U');
        //HWSERIAL.print(',');
      } else {
        // was up now down
         Serial.print("pin ");
         Serial.print(i);
         Serial.println(" has been pressed ");
         HWSERIAL.print(i);
         HWSERIAL.print('D');
        // HWSERIAL.print(',');

      }
    }

    // move current buttonState to lastButtonState
    for (int i = 0; i < numberOfSensors; i++ ) {
      lastButtonState[i] = buttonState[i];
    }

  }
  delay(delayBetweenSends);

}
