#ifndef _Ambience_H_
#define _Ambience_H_

#include <Arduino.h>
#include <NeoPixelBus.h>

class Ambience
{
  private:
    bool gradient;
    String name;
    RgbColor color1;
    RgbColor color2;
    RgbColor color3;
    bool inverted = false;

  public:

    Ambience(String name, RgbColor c1, RgbColor c2, bool g);
    Ambience(String, RgbColor c1, RgbColor c2, RgbColor c3);

    String getName();
    RgbColor getPrimaryColor();
    RgbColor getSecondaryColor();
    RgbColor getAuxiliaryColor();

    bool isGradient();
    void inverse();
    bool isInverted() { return inverted; };

    static Ambience* createFromString(String ambDef);
};

#endif