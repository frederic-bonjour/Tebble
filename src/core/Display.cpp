#include <Arduino.h>
#include <NeoPixelBus.h>
#include "Display.h"
#include "GraphicContext.h"

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
