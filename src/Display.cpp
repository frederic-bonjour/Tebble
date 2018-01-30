#include <Arduino.h>
#include <NeoPixelBus.h>
#include "Display.h"
#include <math.h>

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(289, 6);
NeoTopology<RowMajorAlternatingLayout> topo(17, 17);


Display* screen = new Display();


Display::Display() {
  gc = createContext();
}


Display::~Display() {
  delete gc;
}

GraphicContext* Display::createContext() {
  return new GraphicContext(SCREEN_WIDTH, SCREEN_HEIGHT);
}

GraphicContext* Display::getContext() {
  return gc;
}

void Display::setContext(GraphicContext* newGC) {
  gc = newGC;
}


//-------


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


//------


SlideDownTransition::SlideDownTransition(Runnable* rin, Runnable* rout) : Transition(rin, rout) {
  frameIndex = 0;
  frameCount = SCREEN_HEIGHT;
}


Transition::Transition(Runnable* rin, Runnable* rout) {
  in = rin;
  out = rout;
  gcIn = screen->createContext();
  gcOut = screen->createContext();
}


void SlideDownTransition::draw(GraphicContext* gc) {

  gcOut->copy(0, 0, gc->getWidth(), gc->getHeight() - frameIndex, gc, 0, frameIndex);
  gcIn->copy(0, gc->getHeight() - frameIndex, gc->getWidth(), frameIndex, gc, 0, 0);

	if (frameIndex < frameCount) {
		frameIndex++;
	} else {
		// TODO end();
	}
}
