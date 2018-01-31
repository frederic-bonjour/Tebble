#include <Arduino.h>
#include "Display.h"
#include "Transition.h"

extern Display* screen;


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
