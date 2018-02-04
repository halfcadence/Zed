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

void Light::writePins() {
#ifdef COMMON_ANODE
  analogWrite(redPin, 255 - this->red);
  analogWrite(greenPin, 255 - this->green);
  analogWrite(bluePin, 255 - this->blue);
#else
  analogWrite(redPin, this->red);
  analogWrite(greenPin, this->green);
  analogWrite(bluePin, this->blue);
#endif
}

void Light::setColor(int red, int blue, int green) {
  this->red = red;
  this->green = green;
  this->blue = blue;
  
  this->writePins();
}

void Light::setHexColor(long hex) {
  this->red = ((hex >> 16) & 0xFF);  // Extract the RR byte
  this->green = ((hex >> 8) & 0xFF);   // Extract the GG byte
  this->blue = ((hex) & 0xFF);

  this->writePins();
}



