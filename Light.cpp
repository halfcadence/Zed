#include "Arduino.h"
#include "Light.h"

#define COMMON_ANODE

Light::Light(int redPin, int bluePin, int greenPin)
{
  this->redPin = redPin;
  pinMode(redPin, INPUT);     

  this->bluePin = bluePin;
  pinMode(bluePin, INPUT); 
  
  this->greenPin = greenPin;
  pinMode(greenPin, INPUT);
   
  red = green = blue = 0;
}
void Light::setColor(int red, int blue, int green) {
  #ifdef COMMON_ANODE
    this->red = 255 - red;
    this->green = 255 - green;
    this->blue = 255 - blue;
  #endif
  analogWrite(redPin, this->red);
  analogWrite(greenPin, this->green);
  analogWrite(bluePin, this->blue);  
}




