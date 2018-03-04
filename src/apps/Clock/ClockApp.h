#ifndef _ClockApp_H_
#define _ClockApp_H_

#include "../../core/Luciol/Runnable.h"
#include "../../core/Luciol/Ambience.h"
#include "../../core/Luciol/PropertiesAnimator.h"


class ClockApp : public Runnable {

    PropertiesAnimator pa1in;
    PropertiesAnimator pa1out;

    PropertiesAnimator pa2in;
    PropertiesAnimator pa2out;

    PropertiesAnimator pa3in;
    PropertiesAnimator pa3out;

    PropertiesAnimator pa4in;
    PropertiesAnimator pa4out;

    unsigned long wakeUpTime;

    byte tick();

    uint8_t hours;
    uint8_t minutes;
    String strHours;
    String strMinutes;

    void updateStrings();


    public:
        
        ClockApp();

        uint16_t getRunInterval() {
            return 50;
        }

        void run(GraphicContext* gc, Ambience* ambience, unsigned long time);
        void wakeUp(GraphicContext* gc, Ambience* ambience);
};

#endif