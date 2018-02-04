#include <Button.h>
#include "AnalogSensor.h"
#include "Light.h"

#define DEBUG
// #define DEBUG_POT
// #define DEBUG_BUTTON
#define DEBUG_PHOTOCELL

//pot
const int pot1Pin = A5;
AnalogSensor pot1 = AnalogSensor(pot1Pin, 2);

// button
const int buttonPin = 13;
int buttonPushCounter = 0;
Button myButton = Button(buttonPin, true, false, 25);

// photocell
const int photocellPin = A4;
AnalogSensor photocell = AnalogSensor(photocellPin, 1000);

// rgbled
const int redPin = 11;
const int bluePin = 10;
const int greenPin = 9;
Light light = Light(redPin, bluePin, greenPin);

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

/*
// the loop routine runs over and over again forever:
void loop() {
  pot1.Update();
#if(defined DEBUG && defined DEBUG_POT)
  Serial.println(pot1.getReading());
#endif

  myButton.read();
#if(defined DEBUG && defined DEBUG_BUTTON)
  if (myButton.wasReleased()) {
    Serial.println("pressed");
  }
#endif

  photocell.Update();
#if(defined DEBUG && defined DEBUG_PHOTOCELL)
  Serial.println(photocell.getReading());
#endif
  delay(1);
}
*/
void loop() {
  light.setColor(255, 0, 0);  // red
  delay(1000);
  light.setColor(0, 255, 0);  // green
  delay(1000);
  light.setColor(0, 0, 255);  // blue
  delay(1000);
  light.setColor(255, 255, 0);  // yellow
  delay(1000);  
  light.setColor(80, 0, 80);  // purple
  delay(1000);
  light.setColor(0, 255, 255);  // aqua
  delay(1000);
}

