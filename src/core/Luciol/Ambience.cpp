#include "Ambience.h"
#include <NeoPixelBus.h>

bool Ambience::inverted = false;
bool Ambience::gradient = false;
RgbColor Ambience::color1;
RgbColor Ambience::color2;
RgbColor Ambience::color3;


RgbColor Ambience::getPrimaryColor()
{
  return inverted ? color2 : color1;
}


RgbColor Ambience::getSecondaryColor()
{
  return inverted ? color1 : color2;
}


RgbColor Ambience::getAuxiliaryColor()
{
  return color3;
}


bool Ambience::isGradient()
{
  return gradient;
}


void Ambience::inverse()
{
  inverted = !inverted;
}


void Ambience::updateFromString(String def) {
  int r1, g1, b1;
  int r2, g2, b2;
  char gradient;
  //sscanf(def.c_str(), "%d %d %d %d %d %d %c", &r1, &g1, &b1, &r2, &g2, &b2, &gradient);
  sscanf(def.c_str(), "%d %d %d %d %d %d", &r1, &g1, &b1, &r2, &g2, &b2);
  //Serial.printf("New ambience: (%d,%d,%d) (%d,%d,%d) %c\r\n", r1, g1, b1, r2, g2, b2, gradient);
  Serial.printf("New ambience: (%d,%d,%d) (%d,%d,%d)\r\n", r1, g1, b1, r2, g2, b2);
  color1 = RgbColor(r1, g1, b1);
  color2 = RgbColor(r2, g2, b2);
}