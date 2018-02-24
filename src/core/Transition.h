#ifndef _Transition_H_
#define _Transition_H_

#include "Luciol/Runnable.h"
#include "Luciol/GraphicContext.h"

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


class SlideDownTransition : public Transition {

public:
  SlideDownTransition(Runnable* rin, Runnable* rout);
  void draw(GraphicContext* gc);
};


#endif
