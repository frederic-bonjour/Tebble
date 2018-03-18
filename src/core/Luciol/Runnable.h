#ifndef _Runnable_H_
#define _Runnable_H_

#include <Arduino.h>
#include "GraphicContext.h"
#include "Ambience.h"


class Runnable {

    protected:

        unsigned long lastRunMs = 0;

        bool repaintRequested = false;
        void requestAnimationFrame() {
            repaintRequested = true;
        }
        
        virtual void run(unsigned long msSinceLastRun) = 0;

    public:

        void loop() {
            repaintRequested = false;
            unsigned long now = millis();
            if (now - lastRunMs > getRunInterval()) {
                run(now - lastRunMs);
                lastRunMs = now;
            }
        }

        virtual void paint(GraphicContext* gc, Ambience* ambience);

        virtual void ambienceDidChange() {};

        virtual bool shouldRepaint() {
            return repaintRequested;
        };


        virtual bool isComplete() {
            return false;
        }

        virtual uint16_t getRunInterval() {
            return 1000;
        }

        virtual void handleMessage(String data) {};

        virtual void willStop() {}
        virtual void willStart(GraphicContext* gc, Ambience* ambience) {}

};

#endif