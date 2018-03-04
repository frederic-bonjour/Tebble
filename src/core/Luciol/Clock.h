#ifndef _Clock_H_
#define _Clock_H_

#include <Arduino.h>

class Clock {

    public:
        static void init();
        static void sync();
        static int getHours(); 
        static int getMinutes(); 
        static int getSeconds(); 

};

#endif
