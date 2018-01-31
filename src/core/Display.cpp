#include <Arduino.h>
#include <NeoPixelBus.h>
#include "Display.h"
#include "GraphicContext.h"

NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> leds(SCREEN_WIDTH * SCREEN_HEIGHT);
NeoGamma<NeoGammaTableMethod> colorGamma;
NeoTopology<RowMajorAlternatingLayout> topo(17, 17);


Display Display::display;


Display::Display() {
  gc = createContext();
}


void Display::init() {
  leds.Begin();
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
