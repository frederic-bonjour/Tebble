#include "App.h"
#include "Ambience.h"

App::App()
{}


Ambience* App::getAmbience()
{
   return (ambience != NULL && ambience->getPrimaryColor() != 0) ? ambience : defaultAmbience;
}


RgbColor App::getPrimaryAmbienceColor()
{
  return getAmbience()->getPrimaryColor();
}


RgbColor App::getSecondaryAmbienceColor()
{
  return getAmbience()->getSecondaryColor();
}


void App::setAmbience(Ambience* a)
{
  ambience = a;
  ambienceChanged();
}


void App::ambienceChanged()
{}

void App::loop()
{
  run(millis());
}


void App::run(unsigned long ms)
{}


void App::focus()
{}


bool App::isComplete()
{
  return complete;
}


void App::setSpeed(uint8_t s)
{
  speed = s;
}


String App::getName()
{
  return "App";
}