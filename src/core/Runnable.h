#ifndef _Runnable_H_
#define _Runnable_H_

#include <Arduino.h>
#include "GraphicContext.h"
#include "Ambience.h"


class Runnable {
    protected:
        virtual void run(GraphicContext* gc, Ambience* ambience, unsigned long time) = 0;

    public:
        void loop(GraphicContext* gc, Ambience* ambience) {
            run(gc, ambience, millis());
        }
};

#endif