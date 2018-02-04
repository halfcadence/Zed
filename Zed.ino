#include "AnalogSensor.h"
#include "Light.h"
#include "ButtonCounter.h"
#include "Hue.h"

#define DEBUG
// #define DEBUG_POT
// #define DEBUG_BUTTON
// #define DEBUG_PHOTOCELL
// #define DEBUG_COLOR
 #define DEBUG_FADE

const int NUM_MODES = 3;
const long MHCID_PRIMARY = 0x188fb4;
const float MHCID_PRIMARY_HSL[3] = {.539, .76, .4};
const long MHCID_SECONDARY = 0x559933;
const float MHCID_SECONDARY_HSL[3] = {.277, .5, .4};


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
      //light.setHexColor(solid());
      light.setHexColor(mhcid());
      break;
    case 1:
      light.setHexColor(mhcid());
      break;
    case 2:
      light.setHexColor(MHCID_SECONDARY);
      break;
    default:
      Serial.println("invalid mode selected, defaulting to mode 0");
      break;
  }

  delay(5);
}

long solid() {
  float hue = 1;
  float saturation = 1;
  float lightness = 1;

  // find hue from pot1
  pot1.Update();
  hue = (float) pot1.getReading() / 1023;

  // find lightness from photocell
  photocell.Update();
  // constrain reading from 500 to 1000
#if(defined DEBUG && defined DEBUG_PHOTOCELL)
  Serial.println(photocell.getReading());
#endif
  int constrainedReading = constrain(photocell.getReading(), 500, 900);
  //map to 20% to 70% lightness
  constrainedReading = map(constrainedReading, 500, 900, 70, 15);
  lightness = (float) constrainedReading / 100;
#if(defined DEBUG && defined DEBUG_COLOR)
  Serial.print(hue);
  Serial.print(" ");
  Serial.print(saturation);
  Serial.print(" ");
  Serial.print(lightness);
  Serial.println(" ");
#endif
  return Hue::hsl2hex(hue, saturation, lightness);
  
}

long mhcid() {
  // Serial.println(millis());
  return fade(MHCID_PRIMARY, MHCID_SECONDARY, 5);
}

// cycles between @colors in @cycleSeconds
long fade (long co, long lor, long cycleSeconds) {
  const int NUM_STEPS = 256;
  int cycleMillis = cycleSeconds * 1000;
  long timePerStep = max( cycleMillis / NUM_STEPS, 10); // step must be at least 10 millis long
#if(defined DEBUG && defined DEBUG_FADE)
  Serial.println(millis() % cycleMillis);

  // based on step calculate color as % hsb diff from color 1 to color 2
#endif
  return MHCID_PRIMARY;
  // could use DP for this part if needed optimization

  
}
