#ifndef HEADER_LIGHT
  #define HEADER_LIGHT
class Light
{
  
  // Class Member Variables
  // These are initialized at startup
  int redPin;
  int greenPin;
  int bluePin;
 
  // These maintain the current colors
  int red;
  int blue;
  int green;
  
  public:
    Light(int redPin, int greenPin, int bluePin);
    void setColor(int red,int green,int blue);
    void setHexColor(long hex);
  private:
    void writePins();
};
#endif


