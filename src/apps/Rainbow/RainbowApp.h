#ifndef _RainbowApp_H_
#define _RainbowApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


enum RainbowAppMode { PLAIN, SIDES, UNIQUE };


class RainbowApp : public Runnable {

    uint8_t pos = 0;
    RainbowAppMode mode = PLAIN;

    public:
    
        void run(unsigned long time);
        void paint(GraphicContext* gc, Ambience* ambience);

        void paintPlain(GraphicContext* gc, Ambience* ambience);
        void paintSides(GraphicContext* gc, Ambience* ambience);
        void paintUnique(GraphicContext* gc, Ambience* ambience);

        void handleMessage(String data);
};

#endif