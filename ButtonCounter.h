#ifndef HEADER_BUTTON_COUNTER
  #define HEADER_BUTTON_COUNTER
class ButtonCounter
{
  // Class Member Variables
  // These are initialized at startup
  int pin;
 
  // number of button presses
  int counter;
  
  public:
    ButtonCounter(int pin);
    void increment();
    int getCounter();
};
#endif


