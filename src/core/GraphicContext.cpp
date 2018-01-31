#include <Arduino.h>
#include <NeoPixelBus.h>
#include "GraphicContext.h"
#include <math.h>

GraphicContext::GraphicContext(uint8_t w, uint8_t h) {
  pixels = new RgbColor[w * h];
  width = w;
  height = h;
}


GraphicContext::~GraphicContext() {
  delete pixels;
}


uint8_t GraphicContext::getWidth() {
  return width;
}


uint8_t GraphicContext::getHeight() {
  return height;
}


GraphicContext* GraphicContext::setPixel(int8_t x, int8_t y, RgbColor color) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return this;
  }
  pixels[x + y * width] = color;
  return this;
}


RgbColor GraphicContext::getPixel(int8_t x, int8_t y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return RgbColor(0, 0, 0);
  }
  return pixels[x + y * width];
}


GraphicContext* GraphicContext::horizontalLine(int8_t x1, int8_t x2, int8_t y) {
  for (int8_t x=x1 ; x<=x2 ; x++) {
		this->setPixel(x, y, drawColor);
	}
  return this;
}


GraphicContext* GraphicContext::verticalLine(int8_t x, int8_t y1, int8_t y2) {
  for (int8_t y=y1 ; y<=y2 ; y++) {
    this->setPixel(x, y, drawColor);
  }
  return this;
}


GraphicContext* GraphicContext::copy(int8_t srcX, int8_t srcY, int8_t width, int8_t height, GraphicContext* dstGC, int8_t dstX, int8_t dstY) {
  for (int8_t x=0 ; x<width ; x++) {
  		for (int8_t y=0 ; y<height ; y++) {
  			dstGC->setPixel(dstX + x, dstY + y, getPixel(srcX + x, srcY + y));
  		}
  	}
  return this;
}
