#ifndef _GraphicContext_H_
#define _GraphicContext_H_

#include <NeoPixelBus.h>
#include <Arduino.h>
#include <map>

#include "fonts/Font.h"


class GraphicContext {

  protected:

    uint16_t width, height;

    RgbColor* pixels;
    RgbColor  drawColor;
    RgbColor  fillColor;
    
    NeoGamma<NeoGammaTableMethod> gamma;;

    #ifdef DEVICE_TEBBLE
      Font*     font;
    #endif

  public:

    GraphicContext(uint16_t w, uint16_t h);
    ~GraphicContext();

    GraphicContext* setPixel(int16_t x, int16_t y, RgbColor color);
    RgbColor getPixel(int16_t x, int16_t y);
    GraphicContext* plot(int16_t x, int16_t y);

    GraphicContext* horizontalLine(int16_t y);
    GraphicContext* horizontalLine(int16_t y, RgbColor color);
    GraphicContext* horizontalLine(int16_t x1, int16_t x2, int16_t y);
    GraphicContext* verticalLine(int16_t x);
    GraphicContext* verticalLine(int16_t x, RgbColor color);
    GraphicContext* verticalLine(int16_t x, int16_t y1, int16_t y2);
    
    GraphicContext* setFillColor(RgbColor color);
    GraphicContext* setDrawColor(RgbColor color);
    GraphicContext* setColor(RgbColor color);
    
    GraphicContext* fill();
    GraphicContext* clear();

    #ifdef DEVICE_TEBBLE
      uint16_t        drawChar(int16_t x, int16_t y, char c);
      GraphicContext* setFont(String fontName);
      GraphicContext* text(int16_t x, int16_t y, String text);
      uint16_t getTextWidth(String text);

      uint8_t getBitMaskMaxWidth(uint8_t* mask, uint8_t h);
      GraphicContext* drawBitMask(int16_t x, int16_t y, uint8_t* mask, uint8_t w, uint8_t h);
    #endif

    #ifdef DEVICE_LUCIOL
      GraphicContext* setPixel(int16_t y, RgbColor color);
      GraphicContext* setBlockPixel(int16_t y, RgbColor color);
    #endif

    GraphicContext* rectangle(int16_t x, int16_t y, int16_t w, int16_t h);

    GraphicContext* verticalGradient(RgbColor from, RgbColor to);

    GraphicContext* copy(int16_t srcX, int16_t srcY, int16_t width, int16_t height, GraphicContext* dstGC, int16_t dstX, int16_t dstY);

    uint16_t getWidth();
    uint16_t getHeight();
};

#endif
