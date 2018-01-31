#ifndef _Gradient_H_
#define _Gradient_H_

#include "../../core/Runnable.h"
#include "../../core/Ambience.h"


class GradientApp : public Runnable {

    public:
        void run(GraphicContext* gc, Ambience* ambience, unsigned long time);
};

#endif