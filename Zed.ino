#include "AnalogSensor.h"
#include "Light.h"
#include "ButtonCounter.h"
#define DEBUG
// #define DEBUG_POT
// #define DEBUG_BUTTON
#define DEBUG_PHOTOCELL

const int NUM_MODES = 3;
//pot
const int POT_1_PIN = A5;
AnalogSensor pot1 = AnalogSensor(POT_1_PIN, 2);

// button
const int BUTTON_PIN = 13;
ButtonCounter counter = ButtonCounter(BUTTON_PIN);

// photocell
const int PHOTOCELL_PIN = A4;
AnalogSensor photocell = AnalogSensor(PHOTOCELL_PIN, 1000);

// rgbled
const int RED_PIN = 11;
const int BLUE_PIN = 10;
const int GREEN_PIN = 9;
Light light = Light(RED_PIN, BLUE_PIN, GREEN_PIN);

void setup() {
  Serial.begin(9600);
}

/*
// the loop routine runs over and over again forever:
void loop() {
  pot1.Update();
#if(defined DEBUG && defined DEBUG_POT)
  Serial.println(pot1.getReading());
#endif

  myButton.read();
#if(defined DEBUG && defined DEBUG_BUTTON)
  if (myButton.wasReleased()) {
    Serial.println("pressed");
  }
#endif

  photocell.Update();
#if(defined DEBUG && defined DEBUG_PHOTOCELL)
  Serial.println(photocell.getReading());
#endif
  delay(1);

  // set color
  light.setColor(255, 0, 0);  // red
}
*/
// check button presses
  // based on press, calculate color for each mode...
    // solid mode: select color, detect lightness
    // panic mode: panic!
    // mhci+d mode: vary between blue and green
void loop() {
  counter.Update();

  int mode = counter.getCounter() % NUM_MODES;
  
  switch (mode) {
    case 0:
      light.setHexColor(solid());
      break;
    case 1:
      Serial.println("mode 1");
      break;
    case 2:
      Serial.println("mode 2");
      break;
    default:
      Serial.println("invalid mode selected, defaulting to mode 0");
      break;
  }


  delay(1);
}

long solid() {
  pot1.Update();
  Serial.println(pot1.getReading());
  return 0xff0000;
}

