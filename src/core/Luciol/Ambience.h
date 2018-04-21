#ifndef _Ambience_H_
#define _Ambience_H_

#include <Arduino.h>
#include <NeoPixelBus.h>

class Ambience
{
  private:
    Ambience();

    static bool gradient;
    static RgbColor color1;
    static RgbColor color2;
    static RgbColor color3;
    static bool inverted;

  public:

    static RgbColor getPrimaryColor();
    static RgbColor getSecondaryColor();
    static RgbColor getAuxiliaryColor();
    static bool isGradient();
    static void inverse();
    static void updateFromString(String ambDef);
};

#endif