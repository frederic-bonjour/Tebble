#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <NeoPixelBus.h>
#include <Arduino.h>
#include "GraphicContext.h"

#define NUM_LEDS 289
#define SCREEN_WIDTH  17
#define SCREEN_HEIGHT 17


class Display
{
  private:
    GraphicContext* gc;

  public:
    Display();
    ~Display();

    GraphicContext* createContext();
    void deleteContext(GraphicContext* gc);

    GraphicContext* getContext();
    void setContext(GraphicContext* newGc);

    void render();
};



#endif
