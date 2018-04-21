#ifndef _StroboscopeApp_H_
#define _StroboscopeApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class StroboscopeApp : public Runnable {
    bool on = true;
    public:
        void run(unsigned long time);
        void paint(GraphicContext* gc);
};

#endif