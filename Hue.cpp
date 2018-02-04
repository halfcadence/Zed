#include "Arduino.h"
#include "Hue.h"

void Hue::hsl2rgb (float h, float s, float l, int rgb[]) {
  // Variables for conversion
  float q = 0;
  float t = 0;
  int r, g, b = 0;
  if (s == 0) {
    r = g = b = l;  //achromatic
  } else {
    if (l < 0.5) {
      q = l * (1 + s);
    } else {
      q = l + s - l * s;
    }
    float p = 2 * l - q;
    r = hue2rgb(p, q, h + 0.33) * 255;
    g = hue2rgb(p, q, h) * 255;
    b = hue2rgb(p, q, h - 0.33) * 255;
  }
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
}

long Hue::hsl2hex (float h, float s, float l) {
  int rgb[3];
  hsl2rgb(h,s,l, rgb);
  long r = rgb[0];
  long g = rgb[1];
  long b = rgb[2];
  return ((r << 16) | (g << 8) | b);
}

float Hue::hue2rgb (float p, float q, float t) {
  if(t < 0) {t += 1;}
  if(t > 1) {t -= 1;}
  if(t < 0.17) {return p + (q - p) * 6 * t;}
  if(t < 0.5) {return q;}
  if(t < 0.67) {return p + (q - p) * (0.67 - t) * 6;}
  return p;
}
