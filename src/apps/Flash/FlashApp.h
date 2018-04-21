#ifndef _FlashApp_H_
#define _FlashApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class FlashApp : public Runnable {
    //float opacity;
    public:
        //void run(unsigned long msSinceLastRun);
        void paint(GraphicContext* gc);
};

#endif