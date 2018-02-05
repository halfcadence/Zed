#include "Arduino.h"
#include "ButtonCounter.h"

ButtonCounter::ButtonCounter(int pin)
{
  this->pin = pin;
  pinMode(this->pin, INPUT);
  
  myButton = new Button(this->pin, true, false, 25);
  
  counter = 0;
}
void ButtonCounter::Update() {

  Button buttonObject = *myButton;
  (*myButton).read();
  if ((*myButton).wasPressed()) {
    counter++;
  }
}
int ButtonCounter::getCounter() {
  return counter;
}

