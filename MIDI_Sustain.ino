const int pedalPin = 2;    // the pin that the pushbutton is attached to

int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the pedal pin as a input:
  pinMode(pedalPin, INPUT);

  // initialize MIDI serial communication:
  Serial.begin(31250);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(pedalPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      sendNote(0xB0, 0x40, 0x7F);
    }
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      sendNote(0xB0, 0x40, 0x00);
    }
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;

  // poor man's debounce
  delay(20);
}


void sendNote(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

