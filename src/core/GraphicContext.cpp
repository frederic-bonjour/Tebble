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


GraphicContext* GraphicContext::plot(int8_t x, int8_t y) {
  return setPixel(x, y, drawColor);
}


RgbColor GraphicContext::getPixel(int8_t x, int8_t y) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    return RgbColor(0, 0, 0);
  }
  return pixels[x + y * width];
}


GraphicContext* GraphicContext::horizontalLine(int8_t y) {
  for (int8_t x=0 ; x<width; x++) {
		this->setPixel(x, y, drawColor);
	}
  return this;
}


GraphicContext* GraphicContext::horizontalLine(int8_t x1, int8_t x2, int8_t y) {
  for (int8_t x=x1 ; x<=x2 ; x++) {
		this->setPixel(x, y, drawColor);
	}
  return this;
}


GraphicContext* GraphicContext::verticalLine(int8_t x) {
  for (int8_t y=0 ; y<height ; y++) {
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


GraphicContext* GraphicContext::rectangle(int8_t x, int8_t y, int8_t w, int8_t h) {
  for (int8_t i=x; i < x+w; i++) {
    this->plot(i, y)->plot(i, y+h);
  }
  for (int8_t i=y; i < y+h; i++) {
    this->plot(x, i)->plot(x+w, i);
  }
  return this;
}


GraphicContext* GraphicContext::setFillColor(RgbColor color) {
  fillColor = color;
  return this;
}


GraphicContext* GraphicContext::setDrawColor(RgbColor color) {
  drawColor = color;
  return this;
}


GraphicContext* GraphicContext::fill() {
  for (int8_t y=0 ; y<height ; y++) {
    for (int8_t x=0 ; x<width ; x++) {
      this->setPixel(x, y, fillColor);
    }
  }
  return this;
}


GraphicContext* GraphicContext::clear() {
  RgbColor clearColor(0, 0, 0);
  for (int8_t y=0 ; y<height ; y++) {
    for (int8_t x=0 ; x<width ; x++) {
      this->setPixel(x, y, clearColor);
    }
  }
  return this;
}


GraphicContext* GraphicContext::verticalGradient(RgbColor from, RgbColor to) {
  double step = 1.0 / height;
  float progress = 0;
  for (uint8_t y=0; y<height; y++) {
      setDrawColor(RgbColor::LinearBlend(from, to, progress));
      horizontalLine(y);
      progress += step;
  }
}


GraphicContext* GraphicContext::copy(int8_t srcX, int8_t srcY, int8_t width, int8_t height, GraphicContext* dstGC, int8_t dstX, int8_t dstY) {
  for (int8_t x=0 ; x<width ; x++) {
  		for (int8_t y=0 ; y<height ; y++) {
  			dstGC->setPixel(dstX + x, dstY + y, getPixel(srcX + x, srcY + y));
  		}
  	}
  return this;
}
