#ifndef _ClockApp_H_
#define _ClockApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class ClockApp : public Runnable {

    uint8_t h1, h2;     // Hours digits
    uint8_t m1, m2;     // Minutes digits
    uint8_t nh1, nh2;   // Next hours digits
    uint8_t nm1, nm2;   // Next minutes digits
    int8_t  h1fi, h2fi; // Hours digits frame index;
    int8_t  m1fi, m2fi; // Minutes digits frame index;
    int8_t  seconds;

    public:

        void run(unsigned long time);
        void paint(GraphicContext* gc);
        void willStart(GraphicContext* gc);
};

#endif