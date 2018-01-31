#include "Ambience.h"
#include <NeoPixelBus.h>

Ambience::Ambience(String _name, RgbColor c1, RgbColor c2, bool g)
{
  name = _name;
  color1 = c1;
  color2 = c2;
  color3 = 0;
  gradient = g;
}


Ambience::Ambience(String _name, RgbColor c1, RgbColor c2, RgbColor c3)
{
  name = _name;
  color1 = c1;
  color2 = c2;
  color3 = c3;
  gradient = true;
}


RgbColor Ambience::getPrimaryColor()
{
  return color1;
}


RgbColor Ambience::getSecondaryColor()
{
  return color2;
}


RgbColor Ambience::getAuxiliaryColor()
{
  return color3;
}


String Ambience::getName()
{
  return name;
}


bool Ambience::isGradient()
{
  return gradient;
}

Ambience* Ambience::createFromString(String def) {
  char name[30];
  int r1, g1, b1;
  int r2, g2, b2;
  char gradient;
  sscanf(def.c_str(), "%s %d %d %d %d %d %d %c", name, &r1, &g1, &b1, &r2, &g2, &b2, &gradient);
  Serial.printf("New ambience: %s (%d,%d,%d) (%d,%d,%d) %c\r\n", name, r1, g1, b1, r2, g2, b2, gradient);
  Ambience* amb = new Ambience(String(name), RgbColor(r1, g1, b1), RgbColor(r2, g2, b2), gradient == 'T');
  return amb;
}