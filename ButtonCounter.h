#ifndef HEADER_BUTTON_COUNTER
  #define HEADER_BUTTON_COUNTER
  
#include <Button.h>

class ButtonCounter
{
  // Class Member Variables
  // These are initialized at startup
  int pin;
  // number of button presses
  int counter;
  
  public:
    ButtonCounter(int pin);
    void Update();
    int getCounter();
};
#endif


