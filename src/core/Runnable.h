#ifndef _Runnable_H_
#define _Runnable_H_

#include <Arduino.h>
#include "GraphicContext.h"
#include "Ambience.h"


class Runnable {

    friend class TaskManager;

    protected:

        unsigned long lastRunMs = 0;
        virtual void run(GraphicContext* gc, Ambience* ambience, unsigned long time) = 0;
        
        virtual uint16_t getRunInterval() {
            return 1000;
        }

        virtual void sleep() {}
        virtual void wakeUp(GraphicContext* gc, Ambience* ambience) {}

    public:

        void loop(GraphicContext* gc, Ambience* ambience) {
            unsigned long now = millis();
            if (now - lastRunMs > getRunInterval()) {
                run(gc, ambience, now);
                lastRunMs = now;
            }
        }
};

#endif