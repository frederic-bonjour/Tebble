#ifndef _UI_Progress_H_
#define _UI_Progress_H_

#include "../../core/Runnable.h"


class UIProgress : public Runnable {
    float progress;

    public:
        void setProgress(float p);
        void run(GraphicContext* gc, Ambience* ambience, unsigned long time);
};

#endif