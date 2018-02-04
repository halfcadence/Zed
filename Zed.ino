#include "AnalogSensor.h"
#include "Light.h"
#include <Button.h>
#include "ButtonCounter.h"
#include "Hue.h"

#define DEBUG
// #define DEBUG_POT
// #define DEBUG_BUTTON
// #define DEBUG_PHOTOCELL
// #define DEBUG_COLOR
// #define DEBUG_FADE

const int NUM_MODES = 3;
const long MHCID_PRIMARY = 0x188fb4;
const float MHCID_PRIMARY_HSL[3] = {.539, .76, .4};
const long MHCID_SECONDARY = 0x559933;
const float MHCID_SECONDARY_HSL[3] = {.277, .5, .4};


//pot
const int POT_1_PIN = A5;
AnalogSensor pot1 = AnalogSensor(POT_1_PIN, 2);

// button
const int CYCLE_BUTTON_PIN = 13;
ButtonCounter counter(CYCLE_BUTTON_PIN);

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
      light.setHexColor(mhcid());
      break;
    case 1:
      light.setHexColor(solid());
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
  float saturation = .5;
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
  return fade(MHCID_PRIMARY_HSL, MHCID_SECONDARY_HSL, 1);
}

// cycles between @co/@lor in @cycleSeconds
// TODO: fade by log rather than linearly
// TODO: find out why lightness spikes
long fade (const float* co, const float* lor, long cycleSeconds) {
  int cycleMillis = cycleSeconds * 1000;

  long currentMillis = millis(); // snapshot the time
  long cycleMid = cycleMillis / 2; // find midpoint of cycle
  long cycleLocation = currentMillis % cycleMillis;
  long distance = abs(cycleMillis / 2 - cycleLocation); // distance 
  float distanceP = (float) distance / cycleMid;
  float coToLor[3] = {lor[0] - co[0], lor[1] - co[1], lor[2] - co[2]}; //HSL distance from co to lor
  float intendedHSL[3] = {co[0] + coToLor[0] * distanceP, co[1] + coToLor[1] * distanceP, co[2] + coToLor[2] * distanceP};
#if(defined DEBUG && defined DEBUG_FADE)  
  Serial.print(intendedHSL[0]);
  Serial.print(" ");
  Serial.print(intendedHSL[1]);
  Serial.print(" ");
  Serial.print(intendedHSL[2]);
  Serial.print(" ");
  Serial.println();
#endif
  return Hue::hsl2hex(intendedHSL[0], intendedHSL[1], intendedHSL[2]);
}
