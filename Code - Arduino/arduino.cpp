// Copyright 2022 Maciej Kaszkowiak (maciej@kaszkowiak.org)
// Apache License 2.0

#include <Keypad.h>

// Map the pins to your own set-up
const int RED_LED = 4;
const int YELLOW_LED = 3;
const int GREEN_LED = 5;
byte rowPins[4] = {6, 7, 8, 9};
byte colPins[4] = {10, 11, 12, 13};

// Variables controlling the LED display
unsigned long timeOff = 0;
int ledOn = 0;

char keys[4][4] = {
  {'F','B','8','4'},
  {'E','A','7','3'},
  {'D','0','6','2'},
  {'C','9','5','1'}
};

Keypad keyboard = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

void setup() {
  Serial.begin(115200);

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

// LEDs are processed asynchronously
void lightLed(int pin) {
  digitalWrite(pin, HIGH);
  timeOff = millis() + 2000;
  ledOn = 1;
}

void loop() {
  if (ledOn && millis() > timeOff) {
    ledOn = false;
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
  }

  // Pass key input straight to the ESP-01
  char pressedKey = keyboard.getKey();
  if (pressedKey) {
    Serial.println(pressedKey);
  }

  // Process LED signals from ESP-01, ignore invalid ones
  if (Serial.available() > 0) {
    switch (Serial.read()) {
      case 'R':
        lightLed(RED_LED);
        break;
      case 'G':
        lightLed(GREEN_LED);
        break;
      case 'Y':
        lightLed(YELLOW_LED);
        break;
    }
  }
}