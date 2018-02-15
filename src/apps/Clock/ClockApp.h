#ifndef _ClockApp_H_
#define _ClockApp_H_

#include "../../core/Runnable.h"
#include "../../core/Ambience.h"


class ClockApp : public Runnable {

    public:
        void run(GraphicContext* gc, Ambience* ambience, unsigned long time);
};

#endif