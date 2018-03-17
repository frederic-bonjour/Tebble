#ifndef _TimerApp_H_
#define _TimerApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"


class TimerApp : public Runnable {

    uint8_t m1, m2;     // Minutes digits
    uint8_t s1, s2;     // Seconds digits
    uint8_t nm1, nm2;   // Next minutes digits
    uint8_t ns1, ns2;   // Next hours digits
    int8_t  m1fi, m2fi; // Minutes digits frame index;
    int8_t  s1fi, s2fi; // Seconds digits frame index;

    unsigned int startTime;
    uint16_t duration = 60;
    int16_t  remaining;
    bool     stopped;

    void reset(uint16_t duration);
    void reset();

    public:

        uint16_t getRunInterval() {
            return 50;
        }

        void run(GraphicContext* gc, Ambience* ambience, unsigned long time);
        void willStart(GraphicContext* gc, Ambience* ambience);

        void handleMessage(String data);
};

#endif