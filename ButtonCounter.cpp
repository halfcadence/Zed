#include "Arduino.h"
#include <Button.h>
#include "ButtonCounter.h"

ButtonCounter::ButtonCounter(int pin)
{
  this->pin = pin;
  pinMode(pin, INPUT);     
    
  counter = 0;
}
void ButtonCounter::increment() {
  counter++;
}
int ButtonCounter::getCounter() {
  return counter;
}

