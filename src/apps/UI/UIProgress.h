#ifndef _UI_Progress_H_
#define _UI_Progress_H_

#include "../../core/Luciol/Runnable.h"


class UIProgress : public Runnable {
    float progress;

    public:
        void setProgress(float p);
        void run(GraphicContext* gc, unsigned long time);
};

#endif