#ifndef _GraphicContext_H_
#define _GraphicContext_H_

#include <NeoPixelBus.h>
#include <Arduino.h>
#include <map>

#include "fonts/Font.h"


class GraphicContext {

  private:

    uint8_t width, height;

    RgbColor* pixels;
    RgbColor  drawColor;
    RgbColor  fillColor;
    Font*     font;
    uint8_t drawChar(int8_t x, int8_t y, char c);

  public:

    GraphicContext(uint8_t w, uint8_t h);
    ~GraphicContext();

    GraphicContext* setPixel(int8_t x, int8_t y, RgbColor color);
    RgbColor getPixel(int8_t x, int8_t y);
    GraphicContext* plot(int8_t x, int8_t y);

    GraphicContext* horizontalLine(int8_t y);
    GraphicContext* horizontalLine(int8_t x1, int8_t x2, int8_t y);
    GraphicContext* verticalLine(int8_t x);
    GraphicContext* verticalLine(int8_t x, int8_t y1, int8_t y2);
    
    GraphicContext* setFillColor(RgbColor color);
    GraphicContext* setDrawColor(RgbColor color);
    GraphicContext* setColor(RgbColor color);
    GraphicContext* setFont(String fontName);
    
    GraphicContext* fill();
    GraphicContext* clear();
    GraphicContext* text(int8_t x, int8_t y, String text);
    uint16_t getTextWidth(String text);

    GraphicContext* rectangle(int8_t x, int8_t y, int8_t w, int8_t h);

    GraphicContext* verticalGradient(RgbColor from, RgbColor to);

    GraphicContext* copy(int8_t srcX, int8_t srcY, int8_t width, int8_t height, GraphicContext* dstGC, int8_t dstX, int8_t dstY);

    uint8_t getWidth();
    uint8_t getHeight();
};

#endif
