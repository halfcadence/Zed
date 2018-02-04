#include "Arduino.h"
#include "ButtonCounter.h"

Button myButton = Button(12, true, false, 25);

ButtonCounter::ButtonCounter(int pin)
{
  Serial.println(pin);

  this->pin = pin;
  myButton.changePin(this->pin);
  pinMode(this->pin, INPUT);
  counter = 0;
}
void ButtonCounter::Update() {

  myButton.read();
  if (myButton.wasPressed()) {
    counter++;
    Serial.println(counter);

  }
}
int ButtonCounter::getCounter() {
  return counter;
}

