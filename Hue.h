#ifndef HEADER_HUE
  #define HEADER_HUE
class Hue
{
 public:
  static void hsl2rgb (float h, float s, float l, int rgb[]);
  static long hsl2hex(float h, float s, float l);
 private:
  // Disallow creating an instance of this object
  Hue() {}
  
  static float hue2rgb (float p, float q, float t);
};

#endif
