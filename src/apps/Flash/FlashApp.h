#ifndef _FlashApp_H_
#define _FlashApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class FlashApp : public Runnable {
    public:
        void paint(GraphicContext* gc, Ambience* ambience);
};

#endif