#ifndef _Gradient_H_
#define _Gradient_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class GradientApp : public Runnable {

    public:
        void paint(GraphicContext* gc, Ambience* ambience);
};

#endif