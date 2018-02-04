#include "Arduino.h"
#include "AnalogSensor.h"

AnalogSensor::AnalogSensor(int pin, long delay)
{
  this->pin = pin;
  pinMode(pin, INPUT);     
    
  this->delay = delay;  
  reading = 0; 
  previousMillis = 0;
}
void AnalogSensor::Update() {
  // check to see if it's time to update
  unsigned long currentMillis = millis();
   
  if(currentMillis - previousMillis >= delay) {
    previousMillis = currentMillis;  // Remember the time
    reading = analogRead(pin);
  }
}
int AnalogSensor::getReading() {
  return reading;
}

