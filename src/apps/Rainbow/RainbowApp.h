#ifndef _RainbowApp_H_
#define _RainbowApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class RainbowApp : public Runnable {

    uint8_t pos = 0;

    public:
    
        void run(unsigned long time);
        void paint(GraphicContext* gc, Ambience* ambience);
};

#endif