#ifndef _Runnable_H_
#define _Runnable_H_

#include <Arduino.h>
#include "GraphicContext.h"
#include "Ambience.h"


class Runnable {

    protected:

        unsigned long lastRunMs = 0;
        
        virtual void run(GraphicContext* gc, Ambience* ambience, unsigned long time) = 0;

    public:

        void loop(GraphicContext* gc, Ambience* ambience) {
            unsigned long now = millis();
            if (now - lastRunMs > getRunInterval()) {
                run(gc, ambience, now);
                lastRunMs = now;
            }
        }

        virtual void ambienceDidChange() {};

        virtual bool isComplete() {
            return false;
        }

        virtual uint16_t getRunInterval() {
            return 1000;
        }

        virtual void handleMessage(String data) {};

        virtual void willSleep() {}
        virtual void willWakeUp(GraphicContext* gc, Ambience* ambience) {}

};

#endif