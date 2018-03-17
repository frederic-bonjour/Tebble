#ifndef _ClockApp_H_
#define _ClockApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"
#include "../../core/Luciol/PropertiesAnimator.h"


class ClockApp : public Runnable {

    uint8_t h1, h2;     // Hours digits
    uint8_t m1, m2;     // Minutes digits
    uint8_t nh1, nh2;   // Next hours digits
    uint8_t nm1, nm2;   // Next minutes digits
    int8_t  h1fi, h2fi; // Hours digits frame index;
    int8_t  m1fi, m2fi; // Minutes digits frame index;

    public:

        uint16_t getRunInterval() {
            return 50;
        }

        void run(GraphicContext* gc, Ambience* ambience, unsigned long time);
        void willStart(GraphicContext* gc, Ambience* ambience);
};

#endif