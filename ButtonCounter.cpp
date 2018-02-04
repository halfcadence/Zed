#include "Arduino.h"
#include "ButtonCounter.h"

Button *myButton;

ButtonCounter::ButtonCounter(int pin)
{
  this->pin = pin;
  pinMode(this->pin, INPUT);
  
  myButton = new Button(pin, true, false, 25);
  
  counter = 0;
}
void ButtonCounter::Update() {

  Button buttonObject = *myButton;
  (*myButton).read();
  if ((*myButton).wasPressed()) {
    counter++;
    Serial.println(counter);

  }
}
int ButtonCounter::getCounter() {
  return counter;
}

