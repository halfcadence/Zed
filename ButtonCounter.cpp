#include "Arduino.h"
// #include <Button.h>
#include "ButtonCounter.h"

// hack to create some button... the button is remade in constructor...
Button myButton = Button(13, true, false, 25);

ButtonCounter::ButtonCounter(int pin)
{
  this->pin = pin;
  myButton = Button(pin, true, false, 25);
  pinMode(pin, INPUT);
  counter = 0;
}
void ButtonCounter::Update() {
  myButton.read();
  if (myButton.wasPressed()) {
    counter++;
    // Serial.println("down");
  }
}
int ButtonCounter::getCounter() {
  return counter;
}

