#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <NeoPixelBrightnessBus.h>
#include <Arduino.h>

#include "Singleton.h"
#include "GraphicContext.h"


#ifdef DEVICE_LUCIOL
  #define NUM_LEDS 144
  #define SCREEN_WIDTH  2
  #define SCREEN_HEIGHT 72
#endif

#ifdef DEVICE_TEBBLE
  #define NUM_LEDS 289
  #define SCREEN_WIDTH  17
  #define SCREEN_HEIGHT 17
#endif


class Display : public Singleton<Display>
{
  friend class Singleton<Display>;

  private:

    Display();
    ~Display();
    GraphicContext* gc;
    static NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> leds;

  public:

    GraphicContext* createContext();
    void deleteContext(GraphicContext* gc);

    GraphicContext* getContext();
    void setContext(GraphicContext* newGc);

    void render();
};

#endif
