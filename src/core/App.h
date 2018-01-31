#ifndef _App_H_
#define _App_H_

#include <Arduino.h>
#include <NeoPixelBus.h>

#include "core.h"
#include "Ambience.h"


class App : Runnable
{
  protected:

  	unsigned long previousMillis = 0;
  	bool complete = false;
    Ambience *ambience = NULL;
    Ambience *defaultAmbience;
    uint8_t speed = 30;

    Ambience *getAmbience();

    RgbColor getPrimaryAmbienceColor();
    RgbColor getSecondaryAmbienceColor();

    virtual void run(unsigned long ms);

  public:

    App();

    void setAmbience(Ambience* a);
    virtual void ambienceChanged();

    void loop();

    virtual void focus();

    virtual bool isComplete();

    virtual String getName();
    void setSpeed(uint8_t s);
};

#endif