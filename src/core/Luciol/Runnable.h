#ifndef _Runnable_H_
#define _Runnable_H_

#include <Arduino.h>
#include "GraphicContext.h"
#include "Ambience.h"


class Runnable {

    protected:

        unsigned long lastRunMs = 0;
        unsigned long lastPaintMs = 0;

        bool repaintRequested = false;
        void requestAnimationFrame() {
            repaintRequested = true;
        }
        
        virtual void run(unsigned long msSinceLastRun) {
            requestAnimationFrame();
        };

        virtual void runTransient(unsigned long msSinceLastRun, float progress) {
            run(msSinceLastRun);
        };

    public:

        void loop() {
            repaintRequested = false;
            unsigned long now = millis();
            if (now - lastRunMs > getRunInterval()) {
                run(now - lastPaintMs);
                lastRunMs = now;
            }
        }

        void loopTransient(float progress) {
            repaintRequested = false;
            unsigned long now = millis();
            if (now - lastRunMs > getRunInterval()) {
                runTransient(now - lastPaintMs, progress);
                lastRunMs = now;
            }
        }

        void doPaint(GraphicContext* gc, Ambience* ambience) {
            paint(gc, ambience);
            lastPaintMs = millis();
        };

        virtual void paint(GraphicContext* gc, Ambience* ambience) = 0;

        virtual void ambienceDidChange(GraphicContext* gc, Ambience* ambience) {
            gc->setFillColor(ambience->getSecondaryColor());
            gc->setDrawColor(ambience->getPrimaryColor());
        };

        virtual bool shouldRepaint() {
            return repaintRequested;
        };


        virtual bool isComplete() {
            return false;
        }

        virtual uint16_t getRunInterval() {
            return 16;
        }

        virtual void messageReceived(String data) {};

        virtual void willStop() {};

        virtual void willStart(GraphicContext* gc, Ambience* ambience) {
            gc->setFillColor(ambience->getSecondaryColor());
            gc->setDrawColor(ambience->getPrimaryColor());
        };

};

#endif