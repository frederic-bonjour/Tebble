#ifndef _GraphicContext_H_
#define _GraphicContext_H_

#include <NeoPixelBus.h>
#include <Arduino.h>

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

#endif
