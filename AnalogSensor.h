#ifndef HEADER_ANALOGSENSOR
  #define HEADER_ANALOGSENSOR
class AnalogSensor
{
  // Class Member Variables
  // These are initialized at startup
  int pin;
  long delay;     // delay between each read
 
  // These maintain the current state
  int reading; 
  unsigned long previousMillis;   // will store time of last update
  
  public:
    AnalogSensor(int pin, long delay);
    void Update();
    int getReading();
};
#endif

