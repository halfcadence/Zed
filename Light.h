#ifndef HEADER_LIGHT
  #define HEADER_LIGHT
class Light
{
  
  // Class Member Variables
  // These are initialized at startup
  int redPin;
  int bluePin;
  int greenPin;
 
  // These maintain the current colors
  int red;
  int blue;
  int green;
  
  public:
    Light(int redPin, int bluePin, int greenPin);
    void setColor(int red,int blue,int green);
};
#endif


