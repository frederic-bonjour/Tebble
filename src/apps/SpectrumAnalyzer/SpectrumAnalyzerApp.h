#ifndef _SpectrumAnalyzerApp_H_
#define _SpectrumAnalyzerApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class SpectrumAnalyzerApp : public Runnable {

    unsigned values[7];
    bool newValues = false;

    public:

        void run(unsigned long time);
        void paint(GraphicContext* gc);
        void handleMessage(String data);
};

#endif