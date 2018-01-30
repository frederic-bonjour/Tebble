#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <NeoPixelBus.h>
#include <Arduino.h>

#define NUM_LEDS 289
#define SCREEN_WIDTH  17
#define SCREEN_HEIGHT 17


class Runnable {
  virtual void run() = 0;
};


// ---------


class GraphicContext {

private:
  RgbColor* pixels;
  RgbColor drawColor;
  RgbColor fillColor;
  uint8_t width, height;

public:
  GraphicContext(uint8_t w, uint8_t h);
  ~GraphicContext();

  GraphicContext* setPixel(int8_t x, int8_t y, RgbColor color);
  RgbColor getPixel(int8_t x, int8_t y);

  GraphicContext* horizontalLine(int8_t x1, int8_t x2, int8_t y);
  GraphicContext* verticalLine(int8_t x, int8_t y1, int8_t y2);

  GraphicContext* copy(int8_t srcX, int8_t srcY, int8_t width, int8_t height, GraphicContext* dstGC, int8_t dstX, int8_t dstY);

  uint8_t getWidth();
  uint8_t getHeight();
};


// ---------


class Transition {
protected:
  Runnable *in;
  Runnable *out;

  uint8_t frameIndex = 0;
  uint8_t frameCount = 0;
  GraphicContext* gcIn;
  GraphicContext* gcOut;

public:
  Transition(Runnable* rin, Runnable* rout);
  virtual void draw(GraphicContext* gc) = 0;
};


// ---------


class SlideDownTransition : public Transition {

public:
  SlideDownTransition(Runnable* rin, Runnable* rout);
  void draw(GraphicContext* gc);
};


// ---------


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
