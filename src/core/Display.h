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
    static Display display;

    Display();
    ~Display();
    GraphicContext* gc;

  public:

    static Display &get() noexcept {
        return display;
    }

    GraphicContext* createContext();
    void deleteContext(GraphicContext* gc);

    GraphicContext* getContext();
    void setContext(GraphicContext* newGc);

    void init();
    void render();
};



#endif
